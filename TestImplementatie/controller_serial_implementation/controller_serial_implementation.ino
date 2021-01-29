const int PIN_MOTOR_A = 5;
const int PIN_MOTOR_B = 6;

const int ENC_A = 3;
const int ENC_B = 4;

float kp = 80;
float ki = 0.5; 
float kd = 0.5;

int LPF = 150; // rad/s or hz ?

// This is necessary since we do not let the control software send float strings, only ints.
// Still, these values need to be lower than 1, so we divide them down later on

const float ts = 0.001; // time step in seconds
const float OUTPUT_MAX = 255; // max duty cycle

bool motor_on = false; // changeable in terminal

const long BAUDRATE = 250000; // Computer <-> Arduino serial Baudrate.
const int DELAY_TIME = 1; // ms

enum SYS_STATUS { STOPPED, PAUSED, RUNNING, EMERGENCY };
int systemStatus = STOPPED;

long error_previous = 0; // memory value. Used to calculate derivative action
long error_current = 0; // current value. Declared here to save memory
long integral = 0; // error integral memory
long last_time = 0; // previous setpoint switch time
long previous_sample_time = 0; // previous sample time

int setpoint = 10;
int output = 0; // output. Declared here to save memory

int state = 0; // 0-3 : encoder state
int measured = 0; // measured relative position
long lastTime = 0;


// arrays for storing data for debugging e.d.
short memoryPointer = 0;
long timeData[100];
int positionData[100];
int setpointData[100];

boolean bufferFull = false; // set to true if buffer has once been filled

void setup() {
  Serial.begin(BAUDRATE);

  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);

  pinMode(PIN_MOTOR_A, OUTPUT);
  pinMode(PIN_MOTOR_B, OUTPUT);

  updateRead();
  savePosition();  
}

void loop() {
  checkSerial();
  // Encoder reading runs pseudo-parallel
  updateRead();

  // only write to motor when status is really RUNNING
  if (systemStatus == RUNNING) 
  {
    // max controller frequency fixed:
    if ((millis() - previous_sample_time) > (ts*1000))
    {
      previous_sample_time = millis(); // record this sample timestamp
      updatePID();
      savePosition();
    }
  }
  else
  {
    output = 0;
  }
  writeMotorOutput(&output);
}
