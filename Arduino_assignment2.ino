// ============================================================
// Assignment 2 - Task 5: Beeping Countdown
// Combines Task 4 (7-segment digit display) with a buzzer.
//
// The 7-segment display counts down from 9 to 0.
// The buzzer gives a short beep on every step (9 -> 1),
// and a longer "completion" tone when it reaches 0.
// ============================================================

// ----- Pin setup -----
int buzzerPin = 8;                          // passive buzzer
int segmentPins[] = {2, 3, 4, 5, 6, 7, 9};   // a, b, c, d, e, f, g
int numSegments = 7;

// ----- Digit lookup table (from Task 4) -----
// Each row = one digit (0-9). Each column = one segment (a..g).
// 1 = segment ON, 0 = segment OFF.
byte digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}, // 9
};

// Show a digit (0-9) on the 7-segment display.
void showDigit(int n) {
  if (n < 0 || n > 9) return;   // ignore invalid input

  for (int i = 0; i < numSegments; i++) {
    digitalWrite(segmentPins[i], digits[n][i]);
  }
}

void setup() {
  Serial.begin(9600);

  // Set up the buzzer pin
  pinMode(buzzerPin, OUTPUT);

  // Set up each segment pin
  for (int i = 0; i < numSegments; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  Serial.println("=== Beeping Countdown Starting ===");

  // Count down from 9 to 1
  int count = 9;
  while (count >= 1) {
    Serial.print("Counting: ");
    Serial.println(count);

    showDigit(count);                    // show current number
    tone(buzzerPin, 1000, 200);          // short beep
    delay(1000);                         // hold digit for 1 second

    count = count - 1;
  }

  // Countdown finished - show 0 and play completion tone
  showDigit(0);
  tone(buzzerPin, 1500, 1000);           // longer completion tone

  Serial.println("=== Countdown Complete ===");
}

void loop() {
  // Nothing here - the countdown runs once in setup()
}