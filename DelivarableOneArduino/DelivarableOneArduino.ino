#include <PololuMaestro.h>


//Due has dedicated serial port
#define maestroSerial SERIAL_PORT_HARDWARE_OPEN


MiniMaestro maestro(maestroSerial);

//User Input Variables
uint8_t ChannelEntered = 0;
uint16_t ChannelValue = 0;

//State Flag
bool ChannelStage = true;

int TransmitStatus = 0;

//Sets target of servo channel ChannelNum, ChannelVal is pulse width in us
int TransmitChannel(uint8_t ChannelNum, uint16_t ChannelVal);

void setup() {

  //Start Serial Comms
  Serial.begin(9600);
  maestroSerial.begin(9600);

  //Setup Servo Channel
  maestro.setSpeed(0, 0);
  maestro.setAcceleration(0, 0);
  TransmitChannel(0,4000);

  delay(1000);
  Serial.println("Enter Channel Number:");
}

void loop() {
  //accept user input for channel number
  if(Serial.available() && ChannelStage)
  {
      ChannelEntered = Serial.parseInt();
      Serial.print("Enter Value between 4000 and 8000 for Channel ");
      Serial.print(ChannelEntered);
      Serial.print(":\n");
      ChannelStage = false;
      delay(200);
  }
  //accpet user input for channel target
  if(Serial.available() && !ChannelStage)
  {
      ChannelValue = Serial.parseInt();
      TransmitChannel(ChannelEntered, ChannelValue);
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



