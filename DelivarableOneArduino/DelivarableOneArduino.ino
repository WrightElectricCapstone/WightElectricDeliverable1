#include <PololuMaestro.h>

#define maestroSerial SERIAL_PORT_HARDWARE_OPEN
MiniMaestro maestro(maestroSerial);

uint8_t ChannelEntered = 0;
uint16_t ChannelValue = 0;
bool ChannelStage = true;
bool TransmitStatus = false;


int TransmitChannel(uint8_t ChannelNum, uint8_t ChannelVal);
bool SetTarget(unsigned char Channel, unsigned short Target);

void setup() {
  Serial.begin(9600);
  maestroSerial.begin(9600);
  maestro.setSpeed(0, 0);
      maestro.setAcceleration(0, 0);
      delay(1000);
  Serial.println("Enter Channel Number:");
}

void loop() {

  if(Serial.available() && ChannelStage)
  {
      ChannelEntered = Serial.parseInt();
      Serial.print("Enter 8 Bit Value for Channel ");
      Serial.print(ChannelEntered);
      Serial.print(":\n");
      ChannelStage = false;
      delay(200);
  }
  if(Serial.available() && !ChannelStage)
  {
      ChannelValue = Serial.parseInt();
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


bool SetTarget(unsigned char Channel, unsigned short Target)
{
  unsigned char Command[4];
  Command[0] = 0x84;
  Command[1] = Channel;
  Command[2] = Target & 0x7F;
  Command[3] = (Target >> 7) & 0x7F;
  SerialUSB.write(Command, 4);
  return true;
}

