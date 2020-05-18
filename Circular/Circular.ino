
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float x[15],h[15],y[15];
  int i,j,m,n;
  Serial.println("enter value for m:");
    while(!Serial.available());
    
    m = Serial.parseInt(); 
    Serial.println(m);
    delay(100);
    
  Serial.println("enter value for n:");
     while(!Serial.available());
    n = Serial.parseInt(); 
    Serial.println(n);
    delay(100);
    
  Serial.println("enter the value of x(n):");
  for(i=0;i<m;i++)
  {
    while(!Serial.available());
    x[i] = Serial.parseInt(); 
    Serial.println(x[i]);
    delay(100);
    
  }
  Serial.println("enter the value of h(n):");
  for(i=0;i<n;i++)
  {
     while(!Serial.available());
    h[i] = Serial.parseInt(); 
    Serial.println(h[i]);
    delay(100);
    
  }
  for(i=m;i<=m+n-1;i++)
  {
    x[i]=0;
  }
  for(i=n;i<=m+n-1;i++)
  {
    h[i]=0;
  }
  for(i=0;i<=m+n-1;i++)
  {
    y[i]=0;
    for(j=0;j<=i;j++)
    {
      y[i]=y[i]+(x[j]*h[i-j]);
    }
  }
  for(i=0;i<m+n-1;i++)
  {
    //Serial.print("y[%d]=%f\n",i,y[i]);
    Serial.print("y(n)= ");
    Serial.print(y[i]);
    Serial.print("\t");
  }
  while(1);
}
