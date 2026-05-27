#define TdsSensorPin 34
#define VREF 3.3
#define SCOUNT 30

int analogBuffer[SCOUNT];
int sampleIndex = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  analogBuffer[sampleIndex] = analogRead(TdsSensorPin);
  sampleIndex++;

  if (sampleIndex == SCOUNT) {
    sampleIndex = 0;

    int sum = 0;
    for (int i = 0; i < SCOUNT; i++) sum += analogBuffer[i];

    float avg = sum / (float)SCOUNT;
    float voltage = avg * (VREF / 4095.0);

    float tds = (133.42 * voltage * voltage * voltage
               - 255.86 * voltage * voltage
               + 857.39 * voltage) * 0.5;

    Serial.print("Voltage: ");
    Serial.print(voltage, 2);
    Serial.print(" V | TDS: ");
    Serial.print(tds, 0);
    Serial.println(" ppm");
  }

  delay(100);
}
