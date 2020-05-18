#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<11> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 144
rgb_color colors[LED_COUNT];

typedef enum {
  STATE_OFF,
  STATE_ON
} e_state;

typedef enum {
  MODE_MANUAL,
  MODE_CYCLE,
  MODE_RAINBOW,
  MODE_SHIMMER,
  MODE_WALK,
  MODE_COLLISION,  
  MODE_EXPLOSION,
  MODE_END
} e_mode;

typedef struct{
  uint8_t mode;
  char red,green,blue; // manual
  uint8_t lum; // for cycle & rainbow
  uint8_t speed; // for cycle & rainbow
} s_conf;

static s_conf config;
bool state = STATE_ON;

bool changed = true; // refresh strip
// system timer, incremented by one every time through the main loop
unsigned int loopCount = 0;
unsigned int seed = 0;

void setup()
{
  config.mode = MODE_RAINBOW;
  config.lum = 24;
  config.speed = 10;
  config.red=10;
  config.green=20;
  Serial.begin(9600);
  for(int i=0; i<LED_COUNT; i++) {
  colors[i] = (rgb_color){config.red, config.green, config.blue};
  ledStrip.write(colors, LED_COUNT);}
}

// Converts a color from HSV to RGB.
// h is hue, as a number between 0 and 360.
// s is the saturation, as a number between 0 and 255.
// v is the value, as a number between 0 and 255.
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
    uint8_t f = (h % 60) * 255 / 60;
    uint8_t p = (255 - s) * (uint16_t)v / 255;
    uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t r = 0, g = 0, b = 0;
    switch((h / 60) % 6){
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }
    return (rgb_color){r, g, b};
}

void loop()
{
  manageSerialInput();
  if( state == STATE_OFF) {
    static int count;
    bool allBlack=true;
    for(int i=0; i<LED_COUNT; i++) {
      if(colors[i].red != 0 || colors[i].green != 0 || colors[i].blue != 0) {
        allBlack = false;
        break;
      }
    }      
    if(allBlack)
      return;
    if(++count%25==0) {
      for(int i=0; i<LED_COUNT; i++) {
        fade(&colors[i].red, 5);
        fade(&colors[i].green, 5);
        fade(&colors[i].blue, 5); 
      }
      changed = true;
      delay(10);      
    } 
  }
  else {
    if(config.mode == MODE_MANUAL){
      for(int i=0; i<LED_COUNT; i++)
        colors[i] = (rgb_color){config.red, config.green, config.blue};
    }
    else if(config.mode == MODE_RAINBOW) {
      rainbow();
    }
    else if(config.mode == MODE_CYCLE) {
      cycle();
    }
    else if(config.mode == MODE_SHIMMER) {
      if(++loopCount % 6 == 0) {
        seed = random(30000);
      }
      randomSeed(seed);
      shimmer(false);
      delay(33);
      changed=true;
    }
    else if(config.mode == MODE_WALK) {
      if(++loopCount % 6 == 0) {
        seed = random(30000);
      }
      randomSeed(seed);
      randomColorWalk(!loopCount, false);
      delay(33);
      changed=true;
    }
    else if(config.mode == MODE_COLLISION) {
    
      if(!collision())
        loopCount++;
      else
        loopCount=0;
      delay(33);
      changed=true;
    }
    else if(config.mode == MODE_EXPLOSION) {
      colorExplosion(millis()%1000>100);
      delay(33);
      changed=true;
    }  
  }
    
  if(changed == true) {
    // updates strip only when necessary or this will fuck up the incoming serial connection
    PololuLedStripBase::interruptFriendly = false;
    ledStrip.write(colors, LED_COUNT);
    PololuLedStripBase::interruptFriendly = true;
    changed = false;
  }
}

void manageSerialInput()
{
  uint8_t start1, start2;
  uint16_t i;
  
  if(Serial.available()) {
    WaitForPrefix();
    while(!Serial.available());
    uint8_t command = Serial.read();
    switch(command) { 
      case 'P': // Power
        state = !state;
        changed=true;
        break;
      case 'M': // Mode
        state = STATE_ON;
        config.mode++;
        if(config.mode == MODE_END)
          config.mode = MODE_CYCLE;
        loopCount=0;
        break;
      case 'C': // Color
        state = STATE_ON;
        config.mode = MODE_MANUAL;
        while(!Serial.available());
        config.red = Serial.read();
        while(!Serial.available());
        config.green = Serial.read();
        while(!Serial.available());
        config.blue = Serial.read();
        changed=true;
        break;
      case 'D': // Darker
        state = STATE_ON;
        config.lum = constrain(config.lum>100 ? config.lum-30 : config.lum-12,10,255);
        break;
      case 'B': // Brighter
        state = STATE_ON;
        config.lum = constrain(config.lum>100 ? config.lum+30 : config.lum+12,10,255);
        break;
      case 'S': // Slower
        state = STATE_ON;
        config.speed = constrain(config.speed < 5 ? config.speed+1 : config.speed+3 ,1,36);
        break;
      case 'F': // Faster
        state = STATE_ON;
        config.speed = constrain(config.speed < 5 ? config.speed-1 : config.speed-3,1,24);
        break;
      case 'G': // Send current state to remote device
        sendState();
        break;
      default:
        break;
    }
  }
}

void sendState()
{
  Serial.write(config.mode);
  Serial.write(config.red);
  Serial.write(config.green);
  Serial.write(config.blue);
  Serial.write(0x55);
  Serial.write(0xAA);
}

// remote needs to send 0x55 0xAA before sending command byte(s)
void WaitForPrefix()
{
  uint8_t first = 0, second = 0;
  while (second != 0x55 || first != 0xAA)
  {
    while (!Serial.available());
    second = first;
    first = Serial.read();
  }
}

void rainbow()
{
  static uint32_t time=0;
  static uint8_t counter=0;
  if(++counter>=config.speed) {
    time++;
    counter=0;
  }
  static uint8_t curlum = 0;
  if(curlum<config.lum)
    curlum++;
  else if(curlum>config.lum)
    curlum--;
  
  for(uint8_t y = 0; y < 5; y++)
    for(uint8_t x = 0; x < 6; x++) {
      colors[x*5+y] = hsvToRgb((uint32_t)((time) - ((x*5+y) << 3)) * 359 / 256, 255, curlum);
    }
  changed = true;
}

void cycle()
{
  static uint32_t time=0;
  static uint8_t counter=0;
  if(++counter>=config.speed) {
    time++;
    counter=0;
  }
  static uint8_t curlum = 0;
  if(curlum<config.lum)
    curlum++;
  else if(curlum>config.lum)
    curlum--;
  for(int i=0; i<LED_COUNT; i++) {
    colors[i] = hsvToRgb((uint32_t)((time)) * 359 / 256, 255, curlum);
  }
  changed = true;
}

// ***** PATTERN RandomColorWalk *****
// This function randomly changes the color of every seventh LED by
// randomly increasing or decreasing the red, green, and blue components
// by changeAmount (capped at maxBrightness) or leaving them unchanged.
// The two preceding and following LEDs are set to progressively dimmer
// versions of the central color.  The initializeColors argument
// determines how the colors are initialized:
//   0: randomly walk the existing colors
//   1: set the LEDs to alternating red and green segments
//   2: set the LEDs to random colors
// When true, the dimOnly argument changes the random walk into a 100%
// chance of LEDs getting dimmer by changeAmount; this can be used for
// a fade-out effect.
void randomColorWalk(unsigned char initializeColors, unsigned char dimOnly)
{
  const unsigned char maxBrightness = 180;  // cap on LED brightness
  const unsigned char changeAmount = 3;  // size of random walk step
  
  // pick a good starting point for our pattern so the entire strip
  // is lit well (if we pick wrong, the last four LEDs could be off)
  unsigned char start;
  switch (LED_COUNT % 7)
  {
    case 0:
    start = 3;
    break;
    case 1:
    start = 0;
    break;
    case 2:
    start = 1;
    break;
    default:
    start = 2;
  }

  for (int i = start; i < LED_COUNT; i+=7)
  {
    if (initializeColors == 0)
    {
      // randomly walk existing colors of every seventh LED
      // (neighboring LEDs to these will be dimmer versions of the same color)
      randomWalk(&colors[i].red, maxBrightness, changeAmount, dimOnly ? 1 : 3);
      randomWalk(&colors[i].green, maxBrightness, changeAmount, dimOnly ? 1 : 3);
      randomWalk(&colors[i].blue, maxBrightness, changeAmount, dimOnly ? 1 : 3);
    }
    else if (initializeColors == 1)
    {
      // initialize LEDs to alternating red and green
      if (i % 2)
      {
        colors[i] = (rgb_color){maxBrightness, 0, 0};
      }
      else
      {
        colors[i] = (rgb_color){0, maxBrightness, 0};
      }
    }
    else
    {
      // initialize LEDs to a string of random colors
      colors[i] = (rgb_color){random(maxBrightness), random(maxBrightness), random(maxBrightness)};
    }
    
    // set neighboring LEDs to be progressively dimmer versions of the color we just set
    if (i >= 1)
    {
      colors[i-1] = (rgb_color){colors[i].red >> 2, colors[i].green >> 2, colors[i].blue >> 2};
    }
    if (i >= 2)
    {
      colors[i-2] = (rgb_color){colors[i].red >> 3, colors[i].green >> 3, colors[i].blue >> 3};
    }
    if (i + 1 < LED_COUNT)
    {
      colors[i+1] = colors[i-1];
    }
    if (i + 2 < LED_COUNT)
    {
      colors[i+2] = colors[i-2];
    }
  }
}

void randomWalk(unsigned char *val, unsigned char maxVal, unsigned char changeAmount, unsigned char directions)
{
  unsigned char walk = random(directions);  // direction of random walk
  if (walk == 0)
  {
    // decrease val by changeAmount down to a min of 0
    if (*val >= changeAmount)
    {
      *val -= changeAmount;
    }
    else
    {
      *val = 0;
    }
  }
  else if (walk == 1)
  {
    // increase val by changeAmount up to a max of maxVal
    if (*val <= maxVal - changeAmount)
    {
      *val += changeAmount;
    }
    else
    {
      *val = maxVal;
    }
  }
}

void shimmer(unsigned char dimOnly) 
{
  const unsigned char maxBrightness = 120;  // cap on LED brighness
  const unsigned char changeAmount = 2;   // size of random walk step

  for (int i = 0; i < LED_COUNT; i += 2)
  {
    // randomly walk the brightness of every even LED
    randomWalk(&colors[i].red, maxBrightness, changeAmount, dimOnly ? 1 : 2);
    
    // warm white: red = x, green = 0.8x, blue = 0.125x
    colors[i].green = colors[i].red*4/5;  // green = 80% of red
    colors[i].blue = colors[i].red >> 3;  // blue = red/8
    
    // every odd LED gets set to a third the brighness of the preceding even LED
    if (i + 1 < LED_COUNT)
    {
      colors[i+1] = (rgb_color){colors[i].red /3, colors[i].green /3, colors[i].blue /3};
    }
  }
}

// This function fades val by decreasing it by an amount proportional
// to its current value.  The fadeTime argument determines the
// how quickly the value fades.  The new value of val will be:
//   val = val - val*2^(-fadeTime)
// So a smaller fadeTime value leads to a quicker fade.
// If val is greater than zero, val will always be decreased by
// at least 1.
// val is a pointer to the byte to be faded.
void fade(unsigned char *val, unsigned char fadeTime)
{
  if (*val != 0)
  {
    unsigned char subAmt = *val >> fadeTime;  // val * 2^-fadeTime
    if (subAmt < 1)
    subAmt = 1;  // make sure we always decrease by at least 1
    *val -= subAmt;  // decrease value of byte pointed to by val
  }
}

// ***** PATTERN Collision *****
// This function spawns streams of color from each end of the strip
// that collide, at which point the entire strip flashes bright white
// briefly and then fades.  Unlike the other patterns, this function
// maintains a lot of complicated state data and tells the main loop
// when it is done by returning 1 (a return value of 0 means it is
// still in progress).
unsigned char collision()
{
  const unsigned char maxBrightness = 180;  // max brightness for the colors
  const unsigned char numCollisions = 5;  // # of collisions before pattern ends
  static unsigned char state = 0;  // pattern state
  static unsigned int count = 0;  // counter used by pattern
  
  if (loopCount == 0)
  {
    state = 0;
  }
  
  if (state % 3 == 0)
  {
    // initialization state
    switch (state/3)
    {
      case 0:  // first collision: red streams
      colors[0] = (rgb_color){maxBrightness, 0, 0};
      break;
      case 1:  // second collision: green streams
      colors[0] = (rgb_color){0, maxBrightness, 0};
      break;
      case 2:  // third collision: blue streams
      colors[0] = (rgb_color){0, 0, maxBrightness};
      break;
      case 3:  // fourth collision: warm white streams
      colors[0] = (rgb_color){maxBrightness, maxBrightness*4/5, maxBrightness>>3};
      break;
      default:  // fifth collision and beyond: random-color streams
      colors[0] = (rgb_color){random(maxBrightness), random(maxBrightness), random(maxBrightness)};
    }
    
    // stream is led by two full-white LEDs
    colors[1] = colors[2] = (rgb_color){255, 255, 255};
    // make other side of the strip a mirror image of this side
    colors[LED_COUNT - 1] = colors[0];
    colors[LED_COUNT - 2] = colors[1];
    colors[LED_COUNT - 3] = colors[2];
    
    state++;  // advance to next state
    count = 8;  // pick the first value of count that results in a startIdx of 1 (see below)
    return 0;
  }
  
  if (state % 3 == 1)
  {
    // stream-generation state; streams accelerate towards each other
    unsigned int startIdx = count*(count + 1) >> 6;
    unsigned int stopIdx = startIdx + (count >> 5);
    count++;
    if (startIdx < (LED_COUNT + 1)/2)
    {
      // if streams have not crossed the half-way point, keep them growing
      for (int i = 0; i < startIdx-1; i++)
      {
        // start fading previously generated parts of the stream
        fade(&colors[i].red, 5);
        fade(&colors[i].green, 5);
        fade(&colors[i].blue, 5);
        fade(&colors[LED_COUNT - i - 1].red, 5);
        fade(&colors[LED_COUNT - i - 1].green, 5);
        fade(&colors[LED_COUNT - i - 1].blue, 5);
      }
      for (int i = startIdx; i <= stopIdx; i++)
      {
        // generate new parts of the stream
        if (i >= (LED_COUNT + 1) / 2)
        {
          // anything past the halfway point is white
          colors[i] = (rgb_color){255, 255, 255};
        }
        else
        {
          colors[i] = colors[i-1];
        }
        // make other side of the strip a mirror image of this side
        colors[LED_COUNT - i - 1] = colors[i];
      }
      // stream is led by two full-white LEDs
      colors[stopIdx + 1] = colors[stopIdx + 2] = (rgb_color){255, 255, 255};
      // make other side of the strip a mirror image of this side
      colors[LED_COUNT - stopIdx - 2] = colors[stopIdx + 1];
      colors[LED_COUNT - stopIdx - 3] = colors[stopIdx + 2];
    }
    else
    {
      // streams have crossed the half-way point of the strip;
      // flash the entire strip full-brightness white (ignores maxBrightness limits)
      for (int i = 0; i < LED_COUNT; i++)
      {
        colors[i] = (rgb_color){255, 255, 255};
      }
      state++;  // advance to next state
    }
    return 0;
  }
  
  if (state % 3 == 2)
  {
    // fade state
    if (colors[0].red == 0 && colors[0].green == 0 && colors[0].blue == 0)
    {
      // if first LED is fully off, advance to next state
      state++;
      
      // after numCollisions collisions, this pattern is done
      return state == 3*numCollisions;
    }
    
    // fade the LEDs at different rates based on the state
    for (int i = 0; i < LED_COUNT; i++)
    {
      switch (state/3)
      {
        case 0:  // fade through green
        fade(&colors[i].red, 3);
        fade(&colors[i].green, 4);
        fade(&colors[i].blue, 2);
        break;
        case 1:  // fade through red
        fade(&colors[i].red, 4);
        fade(&colors[i].green, 3);
        fade(&colors[i].blue, 2);
        break;
        case 2:  // fade through yellow
        fade(&colors[i].red, 4);
        fade(&colors[i].green, 4);
        fade(&colors[i].blue, 3);
        break;
        case 3:  // fade through blue
        fade(&colors[i].red, 3);
        fade(&colors[i].green, 2);
        fade(&colors[i].blue, 4);
        break;
        default:  // stay white through entire fade
        fade(&colors[i].red, 4);
        fade(&colors[i].green, 4);
        fade(&colors[i].blue, 4);
      }
    }
  }
  
  return 0;
}

// Helper function for adjusting the colors for the BrightTwinkle
// and ColorExplosion patterns.  Odd colors get brighter and even
// colors get dimmer.
void brightTwinkleColorAdjust(unsigned char *color)
{
  if (*color == 255)
  {
    // if reached max brightness, set to an even value to start fade
    *color = 254;
  }
  else if (*color % 2)
  {
    // if odd, approximately double the brightness
    // you should only use odd values that are of the form 2^n-1,
    // which then gets a new value of 2^(n+1)-1
    // using other odd values will break things
    *color = *color * 2 + 1;
  }
  else if (*color > 0)
  {
    fade(color, 4);
    if (*color % 2)
    {
      (*color)--;  // if faded color is odd, subtract one to keep it even
    }
  }
}

// Helper function for adjusting the colors for the ColorExplosion
// pattern.  Odd colors get brighter and even colors get dimmer.
// The propChance argument determines the likelihood that neighboring
// LEDs are put into the brightening stage when the central LED color
// is 31 (chance is: 1 - 1/(propChance+1)).  The neighboring LED colors
// are pointed to by leftColor and rightColor (it is not important that
// the leftColor LED actually be on the "left" in your setup).
void colorExplosionColorAdjust(unsigned char *color, unsigned char propChance,
unsigned char *leftColor, unsigned char *rightColor)
{
  if (*color == 31 && random(propChance+1) != 0)
  {
    if (leftColor != 0 && *leftColor == 0)
    {
      *leftColor = 1;  // if left LED exists and color is zero, propagate
    }
    if (rightColor != 0 && *rightColor == 0)
    {
      *rightColor = 1;  // if right LED exists and color is zero, propagate
    }
  }
  brightTwinkleColorAdjust(color);
}

// ***** PATTERN ColorExplosion *****
// This function creates bursts of expanding, overlapping colors by
// randomly picking LEDs to brighten and then fade away.  As these LEDs
// brighten, they have a chance to trigger the same process in
// neighboring LEDs.  The color of the burst is randomly chosen from
// among red, green, blue, and white.  If a red burst meets a green
// burst, for example, the overlapping portion will be a shade of yellow
// or orange.
// When true, the noNewBursts argument changes prevents the generation
// of new bursts; this can be used for a fade-out effect.
// This function uses a very similar algorithm to the BrightTwinkle
// pattern.  The main difference is that the random twinkling LEDs of
// the BrightTwinkle pattern do not propagate to neighboring LEDs.
void colorExplosion(unsigned char noNewBursts)
{
  // adjust the colors of the first LED
  colorExplosionColorAdjust(&colors[0].red, 9, (unsigned char*)0, &colors[1].red);
  colorExplosionColorAdjust(&colors[0].green, 9, (unsigned char*)0, &colors[1].green);
  colorExplosionColorAdjust(&colors[0].blue, 9, (unsigned char*)0, &colors[1].blue);

  for (int i = 1; i < LED_COUNT - 1; i++)
  {
    // adjust the colors of second through second-to-last LEDs
    colorExplosionColorAdjust(&colors[i].red, 9, &colors[i-1].red, &colors[i+1].red);
    colorExplosionColorAdjust(&colors[i].green, 9, &colors[i-1].green, &colors[i+1].green);
    colorExplosionColorAdjust(&colors[i].blue, 9, &colors[i-1].blue, &colors[i+1].blue);
  }
  
  // adjust the colors of the last LED
  colorExplosionColorAdjust(&colors[LED_COUNT-1].red, 9, &colors[LED_COUNT-2].red, (unsigned char*)0);
  colorExplosionColorAdjust(&colors[LED_COUNT-1].green, 9, &colors[LED_COUNT-2].green, (unsigned char*)0);
  colorExplosionColorAdjust(&colors[LED_COUNT-1].blue, 9, &colors[LED_COUNT-2].blue, (unsigned char*)0);

  if (!noNewBursts)
  {
    // if we are generating new bursts, randomly pick one new LED
    // to light up
    for (int i = 0; i < 1; i++)
    {
      int j = random(LED_COUNT);  // randomly pick an LED

      switch(random(7))  // randomly pick a color
      {
        // 2/7 chance we will spawn a red burst here (if LED has no red component)
        case 0:
        case 1:
        if (colors[j].red == 0)
        {
          colors[j].red = 1;
        }
        break;
        
        // 2/7 chance we will spawn a green burst here (if LED has no green component)
        case 2:
        case 3:
        if (colors[j].green == 0)
        {
          colors[j].green = 1;
        }
        break;

        // 2/7 chance we will spawn a white burst here (if LED is all off)
        case 4:
        case 5:
        if ((colors[j].red == 0) && (colors[j].green == 0) && (colors[j].blue == 0))
        {
          colors[j] = (rgb_color){1, 1, 1};
        }
        break;
        
        // 1/7 chance we will spawn a blue burst here (if LED has no blue component)
        case 6:
        if (colors[j].blue == 0)
        {
          colors[j].blue = 1;
        }
        break;
        
        default:
        break;
      }
    }
  }
}
