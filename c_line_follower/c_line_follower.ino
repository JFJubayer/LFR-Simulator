#define inA     11
#define inB     10
#define inC     9
#define inD     8
#define enA     6
#define enB     5

int leftBaseSpeed   = 150;
int rightBaseSpeed  = 160;
int minBaseSpeed    = 90;   // Adaptive deceleration on acute angles & zig-zag resistors
int maxSpeed        = 255;
int spinSpeed       = 115;  // Crisp 90-degree pivot speed

#define NUM_SENSORS 8
const uint8_t sensorPins[NUM_SENSORS] = {3, 2, A5, A4, A2, A1, A3, A0};

// Navigation & Obstacle Identifiers
const int LINE_LOST                 = 420;
const int INTERSECTION_LEFT         = 421;
const int INTERSECTION_RIGHT        = 422;
const int INTERSECTION_T_OR_CROSS   = 423;
const int END_BOX                   = 424;

const int STATE_NORMAL              = 0;
const int STATE_TURN_LEFT           = 1;
const int STATE_TURN_RIGHT          = 2;
int navState;
int turnTicks;

int lastSensor;       // 1 = left, 2 = right, 0 = unset
int gapCounter;       // Filter for dashed/broken line gaps
const int GAP_LIMIT = 45; // ~90ms forward dead-reckoning over gaps
int stopBoxCounter;   // Counter for end-box termination
bool isInverted;      // Inverted line block detection
int invertFilter;     // Debounce filter for track inversion
bool isStopped;       // Terminal pad halt

float kp            = 5.5;
float kd            = 14.0; // High damping for acute angles and zig-zags
int prevError;

void initialize();
void lineFollow();
int readSensor();
void wheel(int leftSpeed, int rightSpeed);
void brake();

void setup() {
  initialize();
}

void loop() {
  lineFollow();
  delay(2); // Stable 500Hz control loop
}
