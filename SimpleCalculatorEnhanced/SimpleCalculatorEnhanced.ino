// Define our pin variables
int LED_RED_1_PIN = 7;
int LED_RED_2_PIN = 6;
int LED_BLUE_1_PIN = 5;

int BUTTON_STAGE_PIN = 8;
int BUTTON_MODE_PIN = 9;
int POT_PIN = A0;

// Define our program execution stage variable
int CODE_STAGE = 0;
int NUMBER_1;
int NUMBER_2;

int SCREEN_NUMBER = 0;

// 0 = Addition. 1 = Subtraction
int calculationMode = 0;

#include "SevSeg.h"
SevSeg sevseg;

bool acceptingStageInput = true;
bool acceptingModeInput = true;

void setup() {
	Serial.begin(9600);
	
	pinMode(LED_RED_1_PIN, OUTPUT);
	pinMode(LED_RED_2_PIN, OUTPUT);
	pinMode(LED_BLUE_1_PIN, OUTPUT);
  
  pinMode(BUTTON_STAGE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_MODE_PIN, INPUT_PULLUP);

  byte digitPins[] = {33, 27, 25, 45};
  byte segmentPins[] = {31, 23, 41, 37, 35, 29, 43, 39};
  
  sevseg.begin(COMMON_CATHODE, 4, digitPins, segmentPins); 

  changeState(0);
}

void loop() {
  /**
   * Check Button States
   */
  int BUTTON_STAGE_STATE = digitalRead(BUTTON_STAGE_pin);
  int BUTTON_MODE_STATE = digitalRead(BUTTON_STAGE_pin);
  
  if (BUTTON_STAGE_STATE == LOW) {
    if (acceptingStageInput) {
      acceptingStageInput = false;
      
      if (CODE_STAGE == 2) {
        changeState(0);
      } else {
        changeState(CODE_STAGE + 1);
      }
    }
  } else {
    acceptingStageInput = true;
  }

  if (BUTTON_MODE_STATE == LOW) {
    if (acceptingModeInput) {
      changeCalcMode();
    }
  } else {
    acceptingModeInput = true;
  }

  /**
   * Execute the code relative to the code stage
   * 
   * Stage 0: Choose number 1
   * Stage 1: Choose number 2
   * Stage 2: Perform the mathematical operation on n1 and n2;
   */
  switch (CODE_STAGE) {
    case 0: {
      NUMBER_1 = analogRead(POT_PIN);
      SCREEN_NUMBER = NUMBER_1;
      break;
    }
    case 1: {
      NUMBER_2 = analogRead(POT_PIN);
      SCREEN_NUMBER = NUMBER_2;
      break;
    }
    case 2: {
      if (
      SCREEN_NUMBER = NUMBER_1 + NUMBER_2;
      break;
    }
  }

  sevseg.setNumber(SCREEN_NUMBER);
  sevseg.refreshDisplay();
}

void changeState(int newState) {
  CODE_STAGE = newState;
  disableLEDs();
 
  switch (CODE_STAGE) {
    case 0: {
      disableLEDs();
      NUMBER_1 = 0;
      NUMBER_2 = 0;

      digitalWrite(LED_RED_1_PIN, 255);
      return;
    }
    case 1: {
      disableLEDs();
      digitalWrite(LED_RED_2_PIN, 255);
      return;
    }
    case 2: {
      disableLEDs();
      digitalWrite(LED_BLUE_1_PIN, 255);
      return;
    }
  }
}

void changeCalcMode() {
  if (calculationMode == 1)( {
    calculationMode = 0;
  } else {
    calculationMode = 1;
    
  }
}

void disableLEDs() {
  digitalWrite(LED_BLUE_1_PIN, 0);
  digitalWrite(LED_RED_1_PIN, 0);
  digitalWrite(LED_RED_2_PIN, 0);
}

