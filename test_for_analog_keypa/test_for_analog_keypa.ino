int adc_key_val[5] = {1022, 508, 336, 145, 125 }; //0.146, 0.829, 1.903, 2.928, 3.904
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;

void setup() {
  Serial.begin(9600);
}

void loop() {


  Serial.print(ReadKeypad());
  Serial.print("\t");
  Serial.println(analogRead(0));

  delay(2);
}

int ReadKeypad() {
  adc_key_in = analogRead(0);             // read the value from the sensor  
  digitalWrite(13, HIGH);  
  key = get_key(adc_key_in);              // convert into key press
     
  if (key != oldkey) {                    // if keypress is detected
    delay(100);                            // wait for debounce time
    adc_key_in = analogRead(0);           // read the value from the sensor  
    key = get_key(adc_key_in);            // convert into key press
    if (key != oldkey) {                  
      oldkey = key;
      if (key >=0){
        return key;
      }
    }
  }
  return key;
}
     
     

// Convert ADC value to key number
int get_key(unsigned int input) {
  int k;
  for (k = 0; k < NUM_KEYS; k++)
    {
      if (input >= adc_key_val[k]) {        
      return k;
    }
  }
  if (k <= NUM_KEYS)
    k = -1;                               // No valid key pressed
  return k;
}

