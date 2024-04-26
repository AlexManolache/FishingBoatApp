#include <SPI.h>
#include <LoRa.h>
#include <Servo.h>

// Pins from Lora module connected to Arduino
// Ground Pin connected to Ground Arduino
const int SS_Pin = 10;
const int RST_Pin = 9;
const int DI00_Pin = 2;

// Analog Pin connected with servo for direction system
const int Servo_Pin_Direction = A6;

// Digital Pin conntected with servo from left side for the door
const int Servo_Left_Pin_Gate = 5;

// Digital Pin conntected with servo from right side for the door
const int Servo_Right_Pin_Gate = 6;

// Digital Pin to control the relay which must be connected with dc motor;
const int Relay_1_Pin = 7;

// ESC wire connected to analog pin A4
const int Speed_Engine = A4;

// Reference for servo direction
Servo servoDirection;

// Reference for servo gate of the left side
Servo servoLeftDoor;

// Reference for servo gate of the right side
Servo servoRightDoor;

unsigned int powerEngine = 0;
unsigned int stopEngine = 0;

unsigned int maxSpeed = 255;

unsigned int changeDirection = 90;

int newValue = 0;

int openDoorValue = 90;
int closedDoorValue = 0;

void setup() {
  pinMode(Relay_1_Pin, OUTPUT);
  pinMode(Speed_Engine, OUTPUT);
 
  digitalWrite(Relay_1_Pin, LOW);

  analogWrite(Speed_Engine, 0);

  servoDirection.attach(Servo_Pin_Direction);

  servoLeftDoor.attach(Servo_Left_Pin_Gate);
  servoRightDoor.attach(Servo_Right_Pin_Gate);

  Serial.begin(9600);

  Serial.println("Lora sender!");

  if(!LoRa.begin(433E6)) {
    Serial.println("Lora failed!");
    while(1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();

  if(packetSize) {

    String receiveMessage = "";

    while(LoRa.available()) {
      receiveMessage += (char)LoRa.read();
    }

    controlBoat(receiveMessage, powerEngine, changeDirection);

  }
}

void controlBoat(String receiveMessage, unsigned int & powerEngine, unsigned int & changeDirection) {

   if(receiveMessage == "ON") {
      digitalWrite(Relay_1_Pin, HIGH);
      powerEngine = powerEngine < maxSpeed ? powerEngine++ : maxSpeed;
      analogWrite(Speed_Engine, powerEngine);
      Serial.println("Engine Running!");
    } else if(receiveMessage == "OFF") {
      digitalWrite(Relay_1_Pin, LOW);
      powerEngine = powerEngine == 0 ? stopEngine : powerEngine--;
      analogWrite(Speed_Engine, powerEngine);
      Serial.println("Brake pressed!");
    } else if (receiveMessage == "LEFT") {
      newValue = changeDirection - 1;
      servoDirection.write(newValue); // Move Left the boat
      Serial.println("Change the direction of the boat to the left");
    } else if (receiveMessage == "FORWARD") {
       newValue = changeDirection + newValue;
      servoDirection.write(newValue);
      Serial.println("Go straight");
    } else if (receiveMessage == "RIGHT") {
       newValue = changeDirection + 1;
       servoDirection.write(180); // Move Left the boat
       Serial.println("Change the direction of the boat to the right");
    } else if(receiveMessage == "OPEN") {
      servoLeftDoor.write(openDoorValue);
      servoRightDoor.write(openDoorValue);
      Serial.println("Door is opened!");
    } else if (receiveMessage == "CLOSE") {
      servoLeftDoor.write(closedDoorValue);
      servoRightDoor.write(closedDoorValue);
      Serial.println("Door is closed!");
    } else {
      Serial.println("unknown command");
    }
}
