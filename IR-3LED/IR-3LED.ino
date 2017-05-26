// Include the IR library
#include <IRremote.h>

// Define our variables
int IR_PIN = 8;

int LED_1 = 5;
int LED_2 = 6;
int LED_3 = 7;

// Setup the IR library
IRrecv irDetect(IR_PIN);
decode_results irReciever;

void setup() {
  // Start the IR reciever
  irDetect.enableIRIn();

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
}

void loop() {
  // Check if we see an IR signal
  if (irDetect.decode(&irReciever)) {
    int lastValue = decodeIR();

    disableLEDs();
    if (lastValue == 1) {
      analogWrite(LED_1, 255);
    } else if (lastValue == 2) {
      analogWrite(LED_2, 255);
    } else if (lastValue == 3) {
      analogWrite(LED_3, 255);
    } else {
      for (int i = 0; i < 5; i++) {
        analogWrite(LED_1, 255);
        analogWrite(LED_2, 255);
        analogWrite(LED_3, 255);
        delay(200);
        disableLEDs();
        delay(200);
      }
    }
    delay(1000);

    irDetect.resume();
  }
}

void disableLEDs() {
  analogWrite(LED_1, 0);
  analogWrite(LED_2, 0);
  analogWrite(LED_3, 0);
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
