#include <C:\Users\thewo\Documents\DelivarableOneArduino\PololuMaestro.h>

#define maestroSerial SERIAL_PORT_HARDWARE_OPEN
MiniMaestro maestro(maestroSerial);

uint8_t ChannelEntered = 0;
uint8_t ChannelValue = 0;
bool ChannelStage = true;
int TransmitStatus = 1;

int TransmitChannel(uint8_t ChannelNum, uint8_t ChannelVal);

void setup() {
  Serial.begin(9600);
  SerialUSB.begin(9600);
  maestroSerial.begin(9600);
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

int TransmitChannel(uint8_t ChannelNum, uint8_t ChannelVal)
{
  maestro.setTargetMiniSSC(ChannelNum, ChannelVal);
  return 0; 
}

