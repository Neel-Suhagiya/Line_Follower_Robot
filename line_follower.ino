// ============================================================
//  Line Following Car — Fixed for ESP32 Arduino Core v3.x
//  Uses new ledcAttach() instead of ledcSetup/ledcAttachPin
// ============================================================

// --- IR Sensor Pins ---
#define IR_LEFT   35
#define IR_RIGHT  34

// --- L298N Motor Control Pins ---
#define IN1  18
#define IN2  19
#define IN3  25
#define IN4  14

#define ENA  32
#define ENB  33

// --- PWM Settings ---
#define PWM_FREQ    1000   // 1 kHz
#define PWM_RES     8      // 8-bit (0–255)

// --- Speed Settings ---
#define LEFT_SPEED    65  // Left motor (fast one) — tune this
#define RIGHT_SPEED   65  // Right motor
#define LEFT_TURN     150
#define RIGHT_TURN    150

// ============================================================
void setup() {
  Serial.begin(115200);

  pinMode(IR_LEFT,  INPUT);
  pinMode(IR_RIGHT, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // ✅ New ESP32 Core v3.x PWM setup — single function
  ledcAttach(ENA, PWM_FREQ, PWM_RES);
  ledcAttach(ENB, PWM_FREQ, PWM_RES);

  stopMotors();
  Serial.println("Starting in 3 seconds...");
  delay(3000);
  Serial.println("Car started!");
}

// ============================================================
void loop() {
  int left  = digitalRead(IR_LEFT);
  int right = digitalRead(IR_RIGHT);

  Serial.print("LEFT="); Serial.print(left);
  Serial.print("  RIGHT="); Serial.println(right);

  if (left == LOW && right == LOW) {
    moveForward();

  } else if (left == HIGH && right == HIGH) {
    stopMotors();
    Serial.println(">> STOPPED — both on black");

  } else if (left == HIGH && right == LOW) {
    turnLeft();

  } else if (left == LOW && right == HIGH) {
    turnRight();
  }

  delay(10);
}

// ============================================================
//  Motor Functions
// ============================================================

void moveForward() {
  ledcWrite(ENA, LEFT_SPEED);
  ledcWrite(ENB, RIGHT_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  ledcWrite(ENA, 0);
  ledcWrite(ENB, RIGHT_TURN);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  ledcWrite(ENA, LEFT_TURN);
  ledcWrite(ENB, 0);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  ledcWrite(ENA, 0);
  ledcWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}