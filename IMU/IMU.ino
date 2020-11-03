#include <Wire.h>
#include <helper_3dmath.h>
#include <MPU6050.h>
MPU6050 accelgyro;
#define SDA  PB7;  // SDA FOR THE STM32
#define clk  PB6;  // SCL FOR THE STM32
int current_time = 0, pervious_time, working_time; // for calulating the time of reading
int16_t gx, gy, gyro_z;
int16_t yaw;
void setup() {
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();      //  as a master
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE    // join I2C bus
  Fastwire::setup(400, true);
#endif
  Serial.begin(115200);
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();                              // initialize I2C protocol
  Serial.println("Testing device connections...");     // Testing the connection
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
  pervious_time = current_time;    // to equal the pervious calculating times

  accelgyro.getRotation(&gx, &gy, &gyro_z);   // to get the geroscope reading in degree/second


#ifdef OUTPUT_BINARY_ACCELGYRO
  Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
  Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
  Serial.write((uint8_t)(gyro_z >> 8)); Serial.write((uint8_t)(gyro_z & 0xFF));  // to read the Yaw angle in degree/second
#endif

  current_time = millis();      // to calculate the all time of working
  working_time = (current_time - pervious_time) / 1000;      // to determine the reading time 
  yaw = gyro_z * working_time;  

  Serial.print("YAW ANGLE equal :");
  Serial.print(yaw);




}
