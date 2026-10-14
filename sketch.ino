// Wokwi / Arduino Uno ambient-light headlamp demonstration.
// Bright surroundings select LOW beam; darkness selects HIGH beam.
// This is a light-level demo, not an oncoming-vehicle detector.

constexpr byte LDR_PIN = A0;
constexpr byte RELAY_PIN = 7;

// The Wokwi photoresistor AO signal rises as it gets darker.
// Hysteresis prevents relay chatter around the transition.
constexpr int DARK_TO_HIGH_BEAM = 560;
constexpr int BRIGHT_TO_LOW_BEAM = 500;
constexpr unsigned long SAMPLE_INTERVAL_MS = 50;
constexpr unsigned long REPORT_INTERVAL_MS = 500;

bool highBeam = false;
unsigned long lastSampleAt = 0;
unsigned long lastReportAt = 0;
int lastLdr = 0;

void setup() {
  pinMode(LDR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Relay module uses transistor="pnp": HIGH selects COM-NO (green/high),
  // LOW selects COM-NC (red/low). Start in the lower-beam state.
  digitalWrite(RELAY_PIN, LOW);

  Serial.begin(9600);
  Serial.println(F("Edu adaptive headlight demo ready"));
}

void loop() {
  const unsigned long now = millis();

  if (now - lastSampleAt >= SAMPLE_INTERVAL_MS) {
    lastSampleAt = now;
    lastLdr = analogRead(LDR_PIN);

    if (!highBeam && lastLdr >= DARK_TO_HIGH_BEAM) {
      highBeam = true;
    } else if (highBeam && lastLdr <= BRIGHT_TO_LOW_BEAM) {
      highBeam = false;
    }

    digitalWrite(RELAY_PIN, highBeam ? HIGH : LOW);
  }

  if (now - lastReportAt >= REPORT_INTERVAL_MS) {
    lastReportAt = now;
    Serial.print(F("LDR="));
    Serial.print(lastLdr);
    Serial.print(F(" | "));
    Serial.println(highBeam ? F("DARK -> COM-NO -> GREEN / HIGH BEAM")
                            : F("BRIGHT -> COM-NC -> RED / LOW BEAM"));
  }
}
