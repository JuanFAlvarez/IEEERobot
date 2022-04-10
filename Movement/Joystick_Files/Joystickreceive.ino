#include <esp_now.h>
#include <WiFi.h>
//This is for the joystick to be used as sender

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
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
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


///////////////////////////////////////////////////////////

// H-bridge pin set up

// Motor 1
const int EN1 = 5;
const int a1 = 19;
const int a2 = 18;

// Motor 2
const int EN2 = 15;
const int b1 = 2;
const int b2 =4;

// setting PWM properties
const int freq = 5000;
const int motorchannel = 0;
const int resolution = 8;

const int sped = 255;








// Variables to store values
int LEFT_X = 0;
int LEFT_Y = 0;
int RIGHT_X = 0;
int RIGHT_Y =0;
int LBUTTON = HIGH;
int RBUTTON = HIGH;


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
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}

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

  if (incomingLX>1800){
  fwd();}
  else{
    reverse();
  }
  delay(500);



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




