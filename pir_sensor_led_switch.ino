

const int LIGHT_PIN = A0; // Pin connected to voltage divider output
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 4660.0; // Measured resistance of 3.3k resistor
const float DARK_THRESHOLD = 10000.0;

const int LED_PIN = 13; 

const int PIR_PIN = 7; // HC-S501 input
int pirValue;

const int COUNT_START = 150;
int counter = 0;

const int MS = 500; // loop speed

void setup() {
  Serial.begin(9600);

  pinMode(LIGHT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  digitalWrite(LED_PIN, LOW);
}

void loop() {
  int lightADC = analogRead(LIGHT_PIN);
  if (lightADC > 0) {
    float lightV = lightADC * VCC / 1023.0;
    float lightResistance = R_DIV * (VCC / lightV - 1.0);
    Serial.println("lightADC: " + String(lightADC) + " analog");
    Serial.println("Voltage: " + String(lightV) + " V");
    Serial.println("Resistance: " + String(lightResistance) + " ohms");
    Serial.println();

    if (lightResistance >= DARK_THRESHOLD) {
      if (counter >= 0) {
        pirValue = digitalRead(PIR_PIN);
        if (pirValue) {
          counter = COUNT_START; // 1:45
        }
  
        if (counter < 1) {
          digitalWrite(LED_PIN, LOW);
        } else {
          digitalWrite(LED_PIN, HIGH);
        }
      }
    } else {
      digitalWrite(LED_PIN, LOW);
      counter = -5;
    }
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  countTowardsZero();

  Serial.println("reading: " + String(pirValue));
  Serial.println("counter: " + String(counter));
  Serial.println("\n\n");

  delay(MS);
}

void countTowardsZero() {
  if (counter > 0) {
    counter--;
  } else if (counter < 0) {
    counter++;
  }
}
