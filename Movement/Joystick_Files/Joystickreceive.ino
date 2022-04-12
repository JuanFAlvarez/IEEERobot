#include <esp_now.h>
#include <WiFi.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

//This is for the joystick to be used as receiver


// Ultrasonic setup /////////////////////////////////////////////////////////////////////////////////////////

// Ultrasonic sensor setup
const int trigPin = 12;
const int echoPin = 14;

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
long duration;
float distanceCm;
float distanceInch;


/// ESPNOW SETUP /////////////////////////////////////////////////////////////////////////////////

// REPLACE WITH THE MAC Address of your receiver
uint8_t broadcastAddress[] = {0x08, 0x3A, 0xF2, 0x7B, 0xFC, 0x34};

// Variable to store if sending data was successful
String success;

// Structure to send data
// Must mach the receiver structure
typedef struct struct_message {

  // Left and right values for x and y
  int LX;
  int LY;
  int RX;
  int RY;

  // Left and right buttons
  int LB;
  int RB;
} struct_message;


// Structure to hold readings
struct_message stuff2send;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;



// Variable to store incoming readings
int incomingLX;
int incomingLY;
int incomingRX;
int incomingRY;
int incomingLB;
int incomingRB;

esp_now_peer_info_t peerInfo;


// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0) {
    success = "Delivery Success :)";
  }
  else {
    success = "Delivery Fail :(";
  }
}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingLX = incomingReadings.LX;
  incomingLY = incomingReadings.LY;
  incomingRX = incomingReadings.RX;
  incomingRY = incomingReadings.RY;
  incomingLB = incomingReadings.LB;
  incomingRB = incomingReadings.RB;
  Serial.println("incmoing lx, ly, rx,ry,lb,rb");


}


// H-bridge pin set up /////////////////////////////////////////////////////////////////////////////



// Motor 1
const int EN1 = 5;
const int a1 = 19;
const int a2 = 18;

// Motor 2
const int EN2 = 15;
const int b1 = 2;
const int b2 = 4;

// setting PWM properties
const int freq = 5000;
const int motorchannel = 0;
const int resolution = 8;
const int sped = 255;

// Variables to store values
int LEFT_X = 0;
int LEFT_Y = 0;
int RIGHT_X = 0;
int RIGHT_Y = 0;
int LBUTTON = HIGH;
int RBUTTON = HIGH;

///////////////////////////////////// Absolute orientation sensor setup //////////////////////////////////////////
// current heading and sensor events
int cur_h = 0;
volatile sensors_event_t orientationData , linearAccelData;

//heading and sampling variables and constants
double xPos = 0, yPos = 0, headingVel = 0;
uint16_t BNO055_SAMPLERATE_DELAY_MS = 10; //how often to read data from the board
uint16_t PRINT_DELAY_MS = 500; // how often to print the data
uint16_t printCount = 0; //counter to avoid printing every 10MS sample
//velocity = accel*dt (dt in seconds)
//position = 0.5*accel*dt^2
double ACCEL_VEL_TRANSITION =  (double)(BNO055_SAMPLERATE_DELAY_MS) / 1000.0;
double ACCEL_POS_TRANSITION = 0.5 * ACCEL_VEL_TRANSITION * ACCEL_VEL_TRANSITION;
double DEG_2_RAD = 0.01745329251; //trig functions require radians, BNO055 outputs degrees
// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void setup() {

  // setup PWM
  ledcSetup(motorchannel, freq, resolution);

  //attach channel to the GPIO to be controlled
  ledcAttachPin(EN1, motorchannel);
  ledcAttachPin(EN2, motorchannel);

  // set control pins for H-bridge as output
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);


  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  if (!bno.begin())
  {
    Serial.print("No BNO055 detected");
    while (1);
  }
  delay(1000);

}

// Heading angles for magnetometer
int left = 270;
int right = 90;
int down = 180;
int up = 360;

void loop() {

  // Write all values to structur
  Serial.print("Left_X: ");
  Serial.print(incomingLX);
  Serial.print("\t Left_Y: ");
  Serial.print(LEFT_Y);
  Serial.print("\t LBUTTON: ");
  Serial.println(LBUTTON);
  Serial.print("Right_X: ");
  Serial.print(RIGHT_X);
  Serial.print("\t Right_Y: ");
  Serial.print(RIGHT_Y);
  Serial.print("\t RBUTTON: ");
  Serial.println(RBUTTON);

  //  if (incomingLB == LOW) {
  //    turn1();
  //  }
  //
  //  else if (incomingRB == LOW) {
  //    turn2();
  //  }
  //  else if (incomingLX > 2650) {
  //    fwd();
  //  }
  //  else if (incomingLX < 1600) {
  //    reverse();
  //  }
  //  else {
  //    brake();
  //  }

  // Clear trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Turn HIGH for 10 us
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate distance
  distanceCm = duration * SOUND_SPEED / 2;
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  Serial.println(distanceInch);
  Serial.println(distanceCm);

  // Initialize BNO055
  sensors_event_t orientationData , linearAccelData;
  unsigned long tStart = micros();

  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  //  bno.getEvent(&angVelData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);

  xPos = xPos + ACCEL_POS_TRANSITION * linearAccelData.acceleration.x;
  yPos = yPos + ACCEL_POS_TRANSITION * linearAccelData.acceleration.y;

  // velocity of sensor in the direction it's facing
  headingVel = ACCEL_VEL_TRANSITION * linearAccelData.acceleration.x / cos(DEG_2_RAD * orientationData.orientation.x);

  // Poll BNO055
  while ((micros() - tStart) < (BNO055_SAMPLERATE_DELAY_MS * 1000));
  {
    //poll until the next sample is ready
  }

  if (distanceInch < 10.0) {
    Serial.println(distanceInch);
      cur_h = orientationData.orientation.x;
      if ((cur_h-90) <= 0||(cur_h-90) >= 360){
        cur_h = 359; 
      }
      Serial.println("moving to:");
      Serial.println(cur_h-90);
    turnTo(cur_h-90, cur_h = orientationData.orientation.x);
    delay(1000);
    cur_h = orientationData.orientation.x;
  }
  else {
    fwd();
  }
}


// Movement functions for H-bridge
void fwd() {
  digitalWrite(a1, HIGH);
  digitalWrite(a2, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);
  ledcWrite(motorchannel, sped);
}

void brake() {
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  ledcWrite(motorchannel, 0);
}

void reverse() {
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);
  ledcWrite(motorchannel, sped);
}

void turn1() {
  //clockwise
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH);
  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);
  ledcWrite(motorchannel, sped);
}

void turn2() {
  //counterclockwise
  digitalWrite(a1, HIGH);
  digitalWrite(a2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);
  ledcWrite(motorchannel, sped);
}

/********************************************** Essential functions for path following ********************************************************/


// print x y and z
void printEvent(sensors_event_t* event) {
  Serial.println();
  Serial.print(event->type);
  double x = -1000000, y = -1000000 , z = -1000000; //dumb values, easy to spot problem
  if (event->type == SENSOR_TYPE_ACCELEROMETER) {
    x = event->acceleration.x;
    y = event->acceleration.y;
    z = event->acceleration.z;
  }
  else if (event->type == SENSOR_TYPE_ORIENTATION) {
    x = event->orientation.x;
    y = event->orientation.y;
    z = event->orientation.z;
  }
  else if (event->type == SENSOR_TYPE_MAGNETIC_FIELD) {
    x = event->magnetic.x;
    y = event->magnetic.y;
    z = event->magnetic.z;
  }
  else if ((event->type == SENSOR_TYPE_GYROSCOPE) || (event->type == SENSOR_TYPE_ROTATION_VECTOR)) {
    x = event->gyro.x;
    y = event->gyro.y;
    z = event->gyro.z;
  }

  Serial.print(": x= ");
  Serial.print(x);
  Serial.print(" | y= ");
  Serial.print(y);
  Serial.print(" | z= ");
  Serial.println(z);
}


// rotate to the position LEFT RIGHT UP DOWN
void turnTo(int dir, int cur_h) {
  sensors_event_t orientationData , linearAccelData;

  int rotdir;
  //define upper and lower bounds
  //define cur_h as int in the void turnTo
  int upbound = dir + 5;
  int lowbound = dir - 5;
  //get orientation event to read angle
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  //get current angle from orientation event
  cur_h = orientationData.orientation.x;

  int delthet = cur_h - dir;


  if (delthet < 0) {
    delthet += 360;
  }

  if (delthet <= 180) {
    rotdir = 1;
  }
  else {
    rotdir = 0;
  }
  if (dir != up) {
    //move if cur_h is greater than highest threshold or lower than lowest threshold
    while (cur_h > upbound || cur_h < lowbound) {
      Serial.println("rotating CCW");
      Serial.println("Current Angle is: ");
      Serial.println(cur_h);
      if (rotdir == 0) {
        turn1();
      }
      else {
        turn2();
      }
      bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
      cur_h = orientationData.orientation.x;
    }
  }

  //dir is up
  else {
    //move if cur_h is greater than 5 AND less than 355 aka 0-355
    while (cur_h > 5 && cur_h < 355) {
      Serial.println("rotating CCW");
      Serial.println("Current Angle is: ");
      Serial.println(cur_h);
      if (rotdir == 0) {
        turn1();
      }
      else {
        turn2();
      }
      bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
      cur_h = orientationData.orientation.x;

    }
  }
  //after breaking out of either loop it should brake
  Serial.println("Braking");
  brake();
}
void move_left() {
  Serial.print("TurningLeft");
  turnTo(left, cur_h = orientationData.orientation.x);
  Serial.print("MovingLeft");
  fwd();
  delay(2000);
  brake();
}


void move_right() {
  Serial.print("Turning right");
  turnTo(right, cur_h = orientationData.orientation.x);
  Serial.print("Moving right");
  fwd();
  delay(2000);
  brake();
}

void move_up() {
  Serial.print("Turning up");
  turnTo(up, cur_h = orientationData.orientation.x);
  Serial.print("Moving up");
  fwd();
  delay(2000);
  brake();
}

void move_down() {
  Serial.print("Turning down");
  turnTo(down, cur_h = orientationData.orientation.x);
  Serial.print("Moving down");
  fwd();
  delay(2000);
  brake();
}

