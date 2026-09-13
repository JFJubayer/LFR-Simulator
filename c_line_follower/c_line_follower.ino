#define inA     11
#define inB     10
#define inC     9
#define inD     8
#define enA     6
#define enB     5

int leftBaseSpeed   = 160;
int rightBaseSpeed  = 170;
int maxSpeed        = 255;
int spinSpeed       = 120;

#define NUM_SENSORS 8
const uint8_t sensorPins[NUM_SENSORS] = {3, 2, A5, A4, A2, A1, A3, A0};

const int LINE_LOST = 420;
int lastSensor;     // 1 = left, 2 = right, 0 = unset

float kp            = 6.0;
float kd            = 8.0;
int prevError;

void initialize();
void lineFollow();
int readSensor();
void wheel(int leftSpeed, int rightSpeed);

void setup() {
  initialize();
}

void loop() {
  lineFollow();
  delay(2); // Stable sampling rate for derivative term
}

