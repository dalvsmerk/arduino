#include <IRremote.hpp>

#define pin_recv 2

#define pin_data 3

void setup() {
  Serial.begin(9600);

  IrReceiver.begin(pin_recv, ENABLE_LED_FEEDBACK);
}

void loop() {
  int val = digitalRead(pin_recv);

  if (IrReceiver.decode()) {
    // Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
    // IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    // IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data

    Serial.print("0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    IrReceiver.resume();  // Enable receiving of the next value
  }
}
