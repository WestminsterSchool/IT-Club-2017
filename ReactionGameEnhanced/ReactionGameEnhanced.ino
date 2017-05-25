/**
 * ReactionGameEnhanced
 * 
 * @author  Luke Anderson
 * @version 1.0
 */

// Define our Pin variables
int LED = 7;
int BUTTON = 8;


// Define our code variables
boolean isCheating = false;
// Include the SevSeg library
#include "SevSeg.h"
SevSeg sevseg;

/*
 * 0 = Get Ready
 * 1 = Timing
 * 2 = Button Pressed
 */
int codeStage = 0;

int screenDisplay = 0;
double startMillis = 0;

// SevSeg Variables
byte digitPins[] = {33, 27, 25, 45};
byte segmentPins[] = {31, 23, 41, 37, 35, 29, 43, 39};
  
// Initial setup function, runs once
void setup() {
  // Set our Pin Modes
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  // Generate a random seed
  randomSeed(analogRead(0));

  // Initalize the SevSeg library
  
  sevseg.begin(COMMON_CATHODE, 4, digitPins, segmentPins, false); 
}

/* 
 *  Code is always running
 *
 * 0 = Get Ready
 * 1 = Timing
 * 2 = Button Pressed
 */
void loop() {
  if (codeStage == 0) {
    // Reset the program states
    isCheating = false;
    screenDisplay = 0;

    // Flash the LED 5 times
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED, HIGH);
      delay(200);
      digitalWrite(LED, LOW);
      delay(200);
    }

    // Random delay
    delay(random(3050) + 2500);

    /* Detect for cheaters
     *  
     * How does this work? The logic is simple. At this point in the code execution, 
     * the LED is not on. If the button is being pressed they are cheating!
     */
    int buttonState = digitalRead(BUTTON);

    if (buttonState == LOW) {
      codeStage = 0;
      
      // Flash the LED 10 times
      for (int i = 0; i < 10; i++) {
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
        delay(100);
      }
      
      delay(3000);
      return;
    }

    // Turn on the LED and start the timing
    codeStage = 1;
    digitalWrite(LED, HIGH);

    // Track the start time 
    startMillis = millis();
  } else if (codeStage == 1) {
    // Arduino clock cycles are fast. Every 100ms increase the counter.
    double actualMillis = millis() - startMillis;

    if (actualMillis >= 1) {
      startMillis = millis();
      screenDisplay += 1;
    }

    // Is the button being pressed?
    int buttonState = digitalRead(BUTTON);

    if (buttonState == LOW) {
      startMillis = millis();
      codeStage = 2;
    }
  } else if (codeStage == 2) {
    // Button has been pressed
    double actualMillis = millis() - startMillis;
    
    // Wait 5 seconds
    if (actualMillis >= 5000) {
      screenDisplay = 0;
      codeStage = 0;
      startMillis = millis();
      digitalWrite(LED, LOW);
      
      sevseg.begin(COMMON_CATHODE, 4, digitPins, segmentPins, false); 
      return;
    }
  }

  // Send the number to the screen
  sevseg.setNumber(screenDisplay,  3);
  sevseg.refreshDisplay();
}

