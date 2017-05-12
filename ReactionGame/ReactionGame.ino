int P1_LED = 8;
int P2_LED = 9; 
int STATUS = 10;
int P1_BUTTON = 6;
int P2_BUTTON = 7;

boolean p1Cheater = false;
boolean p2Cheater = false;

void setup() {
  pinMode(P1_BUTTON, INPUT_PULLUP);
  pinMode(P2_BUTTON, INPUT_PULLUP);
  pinMode(P1_LED, OUTPUT);
  pinMode(P2_LED, OUTPUT);
  pinMode(STATUS, OUTPUT);
  randomSeed(analogRead(0));

  Serial.begin(9600);
}

void loop() {
  p1Cheater = false;
  p2Cheater = false;
  
  digitalWrite(P1_LED, LOW);
  digitalWrite(P2_LED, LOW);

  digitalWrite(STATUS, HIGH);
  delay(200);
  digitalWrite(STATUS, LOW);
  delay(200);
  digitalWrite(STATUS, HIGH);
  delay(200);
  digitalWrite(STATUS, LOW);
  delay(200);
  digitalWrite(STATUS, HIGH);
  delay(200);
  digitalWrite(STATUS, LOW);
  delay(200);
  
  delay(random(5000) + 2500);

  int p1 = digitalRead(P1_BUTTON);
  int p2 = digitalRead(P2_BUTTON);

  if (p1 == LOW) p1Cheater = true;
  if (p2 == LOW) p2Cheater = true;

  if (p1Cheater || p2Cheater) {
    flashCheaters();
    delay(2000);
  } else {
    digitalWrite(STATUS, HIGH);
    boolean waiting = true;

    while (waiting) {
      p1 = digitalRead(P1_BUTTON);
      p2 = digitalRead(P2_BUTTON);
           
      if (p1 == LOW) {
        digitalWrite(STATUS, LOW);
        digitalWrite(P1_LED, HIGH);
        delay(5000);
        waiting = false;
      } else if (p2 == LOW) {
        digitalWrite(STATUS, LOW);
        digitalWrite(P2_LED, HIGH);
        delay(5000);
        waiting = false;
      }
    }
  }
}

void flashCheaters() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(STATUS, HIGH);
    if (p1Cheater) digitalWrite(P1_LED, HIGH);
    if (p2Cheater) digitalWrite(P2_LED, HIGH);
    delay(100);
    digitalWrite(STATUS, LOW);
    if (p1Cheater) digitalWrite(P1_LED, LOW);
    if (p2Cheater) digitalWrite(P2_LED, LOW);
    delay(100);
  }
}

