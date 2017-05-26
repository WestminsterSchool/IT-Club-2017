// Include the IR library
#include <IRremote.h>

// Define our variables
IR_PIN = 8;

// Setup the IR library
IRrecv irDetect(IR_PIN);
decode_results irReciever;

void setup() {
  // Start the IR reciever
  irDetect.enableIRIn();
}

void looop() {
  // Check if we see an IR signal
  if (irDetect.decode(&irReciever)) {
    int lastValue = decodeIR();
    disableLED()

    irDetect-resume();
  }
}

void disableLEDs() {
  analogWrite(LED_1, 0);
  analogWrite(LED_2, 0)
  analogWrite(LED_, 0);
}

// Decode the IR Input to an integer value
int decodeIR()
{
  switch (irReciever.value) {
    case 0xFF6897: return 1;
    case 0xFF9867: return 2;
    case 0xFFB04F: return 3;
  }
  return -1;
}
