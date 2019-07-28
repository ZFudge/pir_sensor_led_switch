

const int PIR_PIN = 7; // HC-S501 input
const int LED_PIN = 13;
const int pirValue; // Place to store read PIR Value

const int COUNT_START = 150;
const int MS = 500;
int counter = 0;

void count_down() {
  if (counter >= 1) {
     counter -= 1; 
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  pirValue = digitalRead(PIR_PIN);
  if (pirValue) {
    counter = COUNT_START; // 1:45
  }

  if (counter < 1) {
    digitalWrite(LED_PIN, 0);
  } else {
    digitalWrite(LED_PIN, 1);
  }

  Serial.println("reading: " + String(pirValue));
  Serial.println("counter: " + String(counter));
  Serial.println("");

  count_down();
  delay(MS);
}
