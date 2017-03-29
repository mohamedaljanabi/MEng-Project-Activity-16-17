#include <Wire.h> 
volatile int distance1;  // Variable for distance
volatile int distance2;  //
volatile int distance3;  //
int slaveA= 11;
int slaveB=12;
int slaveAddrs;


void setup()
{
   Serial.begin(9600);

  pinMode(52,INPUT_PULLUP);

    if( digitalRead(52)==LOW){
      slaveAddrs=slaveA;
      Serial.println("this slave is jumpered ");
    }
    else{
      slaveAddrs= slaveB;
    }
    
    
 
  Serial.print("this slave is at address ");
  Serial.println(slaveAddrs);
  // Join i2c bus with address 
  Wire.begin(slaveAddrs);      
  Wire.onRequest(requestEvent);      // register event when maser call for data
}

void start_sensor()                  // This is for initialize the sensor
{
}

void read_sensors(){
  }  
void read_TestData()      // This function read the sensors values
{ 

distance1 = slaveAddrs*10; // test value base on slaveaddrs
distance2 = slaveAddrs*10+1; 
distance3 = slaveAddrs*10+2;   //
} 

void loop()
{
 // read_sensor();
 read_TestData();
  
  /*Serial.print(distance1); // Serial monitering
  Serial.print(",");
  Serial.print(distance2);  //  Same as above
  Serial.print(",");
  Serial.println(distance3);*/ //
  delay(96);
}


void requestEvent()   // This function send data to the master
{
  Wire.write(distance1); // lower byte
  Wire.write(distance1>>8); // upper byte

  Wire.write(distance2); // lower byte
  Wire.write(distance2>>8); // upper byte

  Wire.write(distance3); // lower byte
  Wire.write(distance3>>8); // upper byte*/
}
