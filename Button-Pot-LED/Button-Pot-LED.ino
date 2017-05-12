int led1 = 2;
int led2 = 3;
int led3 = 4;
int button = 7;

boolean enabled = true;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(button, INPUT_PULLUP);
}

void loop()
{
  enableLED(led1);
  delay(analogRead(A0));
  enableLED(led2);
  delay(analogRead(A0));
  enableLED(led3);
  delay(analogRead(A0));
}

void enableLED(int value) {
  int buttonState = digitalRead(button);

  if (buttonState == HIGH) {
    enabled = !enabled;
  }

  analogWrite(led1, 0);
  analogWrite(led2, 0);
  analogWrite(led3, 0);

  if (enabled) {
    analogWrite(value, 255);
  }
}
