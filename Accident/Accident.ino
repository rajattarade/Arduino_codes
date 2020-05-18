#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)

        Wire.begin();
 

    Serial.begin(19200);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        if(az<=-32000)
       { Serial.print("AD...!!!!");
        delay(1000);}
        delay(20);
       Serial.print(gx); Serial.print("\t");

}
