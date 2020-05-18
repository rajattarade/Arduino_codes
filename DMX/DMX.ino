/*************************************************************************************************************
*
*   Title           : Controlador DMX con Arduino
*   Version         : v 0.1
*   Last updated        : 28.08.2012
*   Target          : Arduino mega 2560, Arduino mega 1280, Arduino UNO, Arduino nano
*   Author                  : Toni Merino - merino.toni at gmail.com
*   Web                     : blog.deskontrol.net
*
*
*   Ejemplo de codigo para el mini-controlador DMX con Arduino:
*   Este codigo lee los valores de 6 potenciometros conectados a 6 entradas analogicas y escribe cada valor en la salida DMX 
*   solo cuando se presiona el pulsador correspondiente. (canales de salida 1 al 6) 
*
**************************************************************************************************************/
#include <lib_dmx.h>  // libreria DMX 4 universos   // deskontrol four universes DMX library  - blog.deskontrol.net
 
//*********************************************************************************************************
//                        New DMX modes *** EXPERIMENTAL ***
//*********************************************************************************************************
#define    DMX512     (0)    // (250 kbaud - 2 to 512 channels) Standard USITT DMX-512
#define    DMX1024    (1)    // (500 kbaud - 2 to 1024 channels) Completely non standard - TESTED ok
#define    DMX2048    (2)    // (1000 kbaud - 2 to 2048 channels) called by manufacturers DMX1000K, DMX 4x or DMX 1M ???
 
uint8_t    buffer[6];        // buffer DMX data
 
void setup() 
{
  // configurar pines arduino del 2 al 13 como entradas con pullup, (cuando se pulsa el boton = 0 si no = 1)
  // configure arduino pins 2 to 13 as inputs with pullup, (button pressed = 0, button free = 1) 
  for (int i=2;i<=13;i++) 
  {
    pinMode(i,INPUT);            // pines como entradas       
                                 // pins as inputs
    digitalWrite(i, HIGH);       // activar resistencias pullup internas
                                 // turn on pullup internal resistors
  }
   
  ArduinoDmx0.set_tx_address(10);      // poner aqui la direccion de inicio de DMX 
                                      // put here DMX start address 
                                       
  ArduinoDmx0.set_tx_channels(6);   // poner aqui el numero de canales a transmitir 
                                      // put here the number of DMX channels to transmmit
                                       
  ArduinoDmx0.init_tx(DMX512);        // iniciar transmision universo 0, modo estandar DMX512
                                      // starts universe 0 as TX, standard mode DMX512
}  //end setup()
 
void loop()
{
  // seis entradas con potenciometros que envian valores DMX entre 0 y 255 a los canales 1 al 6, cuando se presiona el pulsador
  // six analog inputs with potentiometers, sending values from 0 to 255, to dmx output channels 1 to 6, when switch is pressed
   
  buffer[0] = scale(analogRead(2)); // copiar valor de la entrada analogica 0 al canal DMX 1
                                    // copy value from analog input 0 to DMX channel 1
  buffer[1] = scale(analogRead(3)); // copiar valor de la entrada analogica 1 al canal DMX 2
                                    // copy value from analog input 1 to DMX channel 2
  buffer[2] = scale(analogRead(4)); // copiar valor de la entrada analogica 2 al canal DMX 3
                                    // copy value from analog input 2 to DMX channel 3
  buffer[3] = scale(analogRead(5)); // copiar valor de la entrada analogica 3 al canal DMX 4
                                    // copy value from analog input 3 to DMX channel 4
  buffer[4] = scale(analogRead(6)); // copiar valor de la entrada analogica 4 al canal DMX 5
                                    // copy value from analog input 4 to DMX channel 5
  buffer[5] = scale(analogRead(7)); // copiar valor de la entrada analogica 5 al canal DMX 6
                                    // copy value from analog input 5 to DMX channel 6
   
  if (digitalRead(2) == LOW)             // pulsador en pin 2 apretado                  // push-button on pin 2, is pressed
    ArduinoDmx0.TxBuffer[0] = buffer[0]; // enviar valor potenciometro al canal DMX 1   // send analog value to DMX channel 1
  else
    ArduinoDmx0.TxBuffer[0] = 0;         // si no enviar 0                              // push-button free, send 0
         
  if (digitalRead(3) == LOW)             // pulsador en pin 3 apretado                  // push-button on pin 3, is pressed
    ArduinoDmx0.TxBuffer[1] = buffer[1]; // enviar valor potenciometro al canal DMX 2   // send analog value to DMX channel 2
  else
    ArduinoDmx0.TxBuffer[1] = 0;         // si no enviar 0                              // push-button free, send 0
     
  if (digitalRead(4) == LOW)       
    ArduinoDmx0.TxBuffer[2] = buffer[2]; 
  else
    ArduinoDmx0.TxBuffer[2] = 0;   
     
  if (digitalRead(5) == LOW)       
    ArduinoDmx0.TxBuffer[3] = buffer[3]; 
  else
    ArduinoDmx0.TxBuffer[3] = 0;   
     
  if (digitalRead(6) == LOW)       
    ArduinoDmx0.TxBuffer[4] = buffer[4]; 
  else
    ArduinoDmx0.TxBuffer[4] = 0;   
     
  if (digitalRead(7) == LOW)       
    ArduinoDmx0.TxBuffer[5] = buffer[5]; 
  else
    ArduinoDmx0.TxBuffer[5] = 0;   
        
     
}  //end loop()
 
 
uint8_t scale(uint16_t value) // scale values from 10 bits to 8 bits
{
  if(value > 1023) // test for 10 bits limit
    value = 1023;
     
  return (value >> 2); // scale
}  //end scale()
 
