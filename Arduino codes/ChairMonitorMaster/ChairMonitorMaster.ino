/*
   Angle_master_mm.ino
*/

#include <Wire.h>  // required for I2C
//IMU libraries:
#include <CurieIMU.h>
#include <MadgwickAHRS.h>
// address constants:
const int firstMega  = 11;
const int secondMega = 12;
//IMU variables
Madgwick filter;
unsigned long millisPerReading, millisPrevious;
unsigned long messageCounter = 0; // number of messages sent

int distances[6]; //global array holding six distance sensor readings
  
void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
  CurieIMU.begin();
  CurieIMU.setGyroRate(25);
  CurieIMU.setAccelerometerRate(25);
  // initialize serial communication
  Serial.begin(9600);
  //intilizing the IMU and its variables
  //filter.begin(25); // where did this come from ???
  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
  // Set the gyroscope range to 250 degrees/second
  CurieIMU.setGyroRange(250);
  // initialize variables to pace updates to correct rate
  millisPerReading = 1000 / 25;
  //this means that it reads 25 times a second
}
void loop() {
  int roll, pitch, heading;
  // check if it's time to read data and update the filter
  if (millis() - millisPrevious >= millisPerReading) {
    millisPrevious = millis(); //reset the millis time counter
    getAngles( roll, pitch, heading);
    messageCounter++;
    //To change the ratio of angle data readings to distance readings change the if conditional
    if (messageCounter % 1 == 0) {   
      // here on every third reading
     getDistanceSensors(firstMega, 3, &distances[0]); // get the first three distances
     getDistanceSensors(secondMega,3, &distances[3]); // get the second three distances
    }
    else {
      for(int i=0; i < 6; i++)
        distances[i] = 0;  // zero the distance values for messages with no distance data
    }
    /*
     * code needed here to format message to monitor. The protocol for this message should be similar to the protocol used for the watcher
     * messsages from the middleware.
     */
    // debug printing for testing ...
    Serial.print("angles:"); Serial.print(roll); Serial.print(","); Serial.print(pitch); Serial.print(","); Serial.println(heading);   
    for(int i=0; i < 6; i++ ) {
       Serial.print(i); Serial.print("="); Serial.print(distances[i]);
       if( i < 5) Serial.print(","); 
       else Serial.println();   // print newline at end, othewise print commas
    }
    Serial.println();
  }
  delay(500);
}

void getAngles(int& roll, int& pitch, int& heading)
{
  int aix, aiy, aiz;
  int gix, giy, giz;
  float ax, ay, az;
  float gx, gy, gz;
  const float radians = 57.29578;
  // read raw data from CurieIMU
  CurieIMU.readMotionSensor(aix, aiy, aiz, gix, giy, giz);
  ax = convertRawAcceleration(aix);
  ay = convertRawAcceleration(aiy);
  az = convertRawAcceleration(aiz);
  gx = convertRawGyro(gix);
  gy = convertRawGyro(giy);
  gz = convertRawGyro(giz);
  // update the filter, which computes orientation
  filter.updateIMU(gx, gy, gz, ax, ay, az);
  // get filter output and convert from radians to degrees
  roll = int(radians * filter.getRoll());
  pitch = int(radians * filter.getPitch());
  heading = int(radians * filter.getYaw());
  Serial.print("angles:"); Serial.print(roll); Serial.print(","); Serial.print(pitch); Serial.print(","); Serial.println(heading);
}
float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  float a = (aRaw * 2.0) / 32768.0;
  return a;
}
float convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767
  float g = (gRaw * 250.0) / 32768.0;
  return g;
}

// Distance Sensor Check Code Below
// gets three distance readings from the sensors at the given I2C address
void getDistanceSensors( int address, int nbrSensors, int* distances)
{
  
  const int numberOfBytes = nbrSensors*2; // two bytes per sensor
  //distances[0] = 10; distances[1] = 11; distances[2] = 12;  // dummy data
 
  //return;  // debug only, remove this to read from I2C
  Wire.requestFrom(address, numberOfBytes);
  while (Wire.available())
  {
    for (int i = 0; i < nbrSensors; i++ ) {
      int distance_a = Wire.read();
      int distance_b = Wire.read();
      distances[i] = (distance_b << 8) | distance_a;
      //Serial.print(i); Serial.print("="); Serial.println(distances[i]); // for debug only
    }
  }
}
