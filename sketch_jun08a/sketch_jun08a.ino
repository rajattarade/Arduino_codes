char s_number1[] = {"+919404292958"};

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200); 
}

void loop() {
  // put your main code here, to run repeatedly:
 for(int i=0;i < 13;i++)
    {
     Serial.print(s_number1[i]);
     delay(10);
    }
    Serial.println();
}
