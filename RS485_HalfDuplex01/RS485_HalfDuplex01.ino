#include <ModbusMaster.h>

#define MAX485_DE      3
#define MAX485_RE_NEG  2

// instantiate ModbusMaster object
ModbusMaster node;

void preTransmission()
{
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

void setup()
{
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  // Init in receive mode
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);

  // Modbus communication runs at 115200 baud
  Serial.begin(9600);
  Serial1.begin(9600);
  // Modbus slave ID 1
  node.begin(103, Serial1);
  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

bool state = true;

void loop()
{
  uint8_t result;

  // Read 16 registers starting at 0x3100)
  result = node.readInputRegisters(0x00, 5);
  if (result == node.ku8MBSuccess)
  {
  Serial.print(float(node.getResponseBuffer(0x00)));
  Serial.print("  ");
 }
  delay(1000);
}

