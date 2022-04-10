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
int incomingRL;
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
  incomingLX = incomingReadings.RX;
  incomingLY = incomingReadings.RY;
  incomingLX = incomingReadings.LB;
  incomingLY = incomingReadings.RB;

}


///////////////////////////////////////////////////////////






// Joystick input pins
const int left_xpin = 34;
const int left_ypin = 35;
const int right_xpin = 13;
const int right_ypin = 12;

// Button input pins
const int Lbutpin = 32;
const int Rbutpin = 14;

// Variables to store values
int LEFT_X = 0;
int LEFT_Y = 0;
int RIGHT_X = 0;
int RIGHT_Y =0;
int LBUTTON = HIGH;
int RBUTTON = HIGH;


void setup() {

  pinMode(left_xpin, INPUT);
  pinMode(left_ypin, INPUT);

  pinMode(right_xpin, INPUT);
  pinMode(right_ypin, INPUT);
  
  pinMode(Lbutpin, INPUT);
  pinMode(Rbutpin, INPUT);

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

  // Read all values
  LEFT_X = analogRead(left_xpin);
  LEFT_Y = analogRead(left_ypin);
  RIGHT_X = analogRead(right_xpin);
  RIGHT_Y = analogRead(right_ypin);
  LBUTTON = digitalRead(Lbutpin);
  RBUTTON = digitalRead(Rbutpin);


  // Write all values to structure
  stuff2send.LX = LEFT_X;
  stuff2send.LY = LEFT_Y;
  stuff2send.RX = RIGHT_X;
  stuff2send.RY = RIGHT_Y;
  stuff2send.LB = LBUTTON;
  stuff2send.RB = RBUTTON;

  Serial.print("Left_X: ");
  Serial.print(LEFT_X);
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

 // Send values via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &stuff2send, sizeof(stuff2send));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
    Serial.println("Data that was sent");
    Serial.println(stuff2send.LX);
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(500);



}
