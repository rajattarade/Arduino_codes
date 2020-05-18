void setup() {
  // put your setup code here  to run once:
Serial.begin(9600);
//S1 S2 S3 S4 S5 HEATER SOAPP PUMP
}

void loop() {
  // put your main code here  to run repeatedly:
//while(Serial.read()!='s');
 Serial.print("0 0 0 1 0 1 1 0 n");
 delay(10000); 
 //Serial.print("*********WAIT*********"); 
 Serial.print("0 1 0 0 1 1 0 1 n");
 //Serial.print("*********READY*********");
 //while(Serial.read()!='n');
 //Serial.print("*********SOAPPY WASH*********");
 delay(10000); 
 Serial.print("1 1 0 0 0 1 0 1 n");
 //Serial.print("*********FRESH WATER PIPE CLEAN*********");
 delay(10000); 
 Serial.print("1 0 1 0 0 1 0 1 n");
 delay(10000);  
 //Serial.print("*********GEYSER FILLED WITH FRESH WATER*********");
 Serial.print("1 0 1 0 0 1 0 0 n"); 
 //Serial.print("*********WATER IS HEATING*********");
 delay(10000); 
 Serial.print("1 0 1 0 0 1 0 1 n");
 //Serial.print("*********FRESH WARM WATER RINSE*********");
 delay(10000); 
 Serial.print("1 0 1 0 0 1 0 0 n");
 //Serial.print("*********PLEASE RESET*********"); 
 while(1);
}
