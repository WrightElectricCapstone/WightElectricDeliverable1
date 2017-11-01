#include <PololuMaestro.h>


//Due has dedicated serial port
#define maestroSerial SERIAL_PORT_HARDWARE_OPEN


MiniMaestro maestro(maestroSerial);

//User Input Variables
uint8_t ChannelEntered = 0;
uint16_t ChannelValue = 0;

//State Flag
bool ChannelStage = true;

//Sets target of servo channel ChannelNum, ChannelVal is pulse width in us
int TransmitChannel(uint8_t ChannelNum, uint16_t ChannelVal);

void setup() {

  //Start Serial Comms
  Serial.begin(9600);
  maestroSerial.begin(9600);

  //Setup Servo Channel
  maestro.setSpeed(0, 0);
  maestro.setAcceleration(0, 0);
  TransmitChannel(0,1000);

  delay(1000);
  Serial.println("Enter Channel Number:");
}

void loop() {
  //accept user input for channel number
  if(Serial.available() && ChannelStage)
  {
      ChannelEntered = Serial.parseInt();
      Serial.print("Enter Value between 1000 and 2000 for Channel ");
      Serial.print(ChannelEntered);
      Serial.print(":\n");
      ChannelStage = false;
      delay(200);
  }
  //accpet user input for channel target
  if(Serial.available() && !ChannelStage)
  {
      ChannelValue = Serial.parseInt();
      if(ChannelValue < 1000)
      {
        ChannelValue = 1000;
      }
      if(ChannelValue > 2000)
      {
        ChannelValue = 2000;
      }
      TransmitStatus = TransmitChannel(ChannelEntered, ChannelValue);
      if(TransmitStatus == 0)
      {
        Serial.print("Channnel ");
        Serial.print(ChannelEntered);
        Serial.print(" set to ");
        Serial.print(ChannelValue);
        Serial.print("\n\n");
        
      }
      else
      {
        Serial.println("Failed to set Target!");
        Serial.print("Failed to set channel ");
        Serial.print(ChannelEntered);
        Serial.print("to value ");
        Serial.print(ChannelValue);
        Serial.print("\n\n");
      }
      Serial.println("Enter Channel Number:");
      ChannelStage = true;
  }
}

int TransmitChannel(uint8_t ChannelNum, uint16_t ChannelVal)
{
  maestro.setTarget(ChannelNum, ChannelVal);
  return 0; 
}



