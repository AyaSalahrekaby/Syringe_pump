#include <Stepper.h>

#define STEPS 32

#define IN1 4 
#define IN2 5
#define IN3 6
#define IN4 7
int speed = 3;
int volume = 0;
float flow_rate =0;

Stepper strpper(STEPS, IN4, IN3, IN2, IN1);

int button_forward = A2;
int button_backward = A3;



#define TRIG_pin 13
#define ECHO_pin 12
#define buzzer 11
#define heart_led 8

#define syringe_finshed_led 9
int IR_sensor = 3;
int IR = HIGH;
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

byte compteur;
#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>        

//  Variables
const int PulseWire = 0;       
const int LED = LED_BUILTIN;         
int Threshold = 550;
int myBPM; 
PulseSensorPlayground pulseSensor;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIG_pin, OUTPUT);
  pinMode(ECHO_pin, INPUT);
  pinMode(button_forward, INPUT);
  pinMode(button_backward, INPUT);
  pinMode(syringe_finshed_led, OUTPUT);
  pinMode(IR_sensor, INPUT); 
  pinMode(buzzer, OUTPUT);
  pinMode(heart_led, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  display.display();

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);

   
  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
  myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
}

  digitalWrite(heart_led, LOW);


  

  digitalWrite(TRIG_pin, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_pin, HIGH);
  delayMicroseconds(10);  
  digitalWrite(TRIG_pin, LOW);
  int distance;
  int t;  
  t=pulseIn(ECHO_pin, HIGH);
  distance = (t*.0343)/2;  
  Serial.println(distance);
  int forward;
  int back;
  forward = digitalRead(button_backward);
  back = digitalRead(button_forward);

  if((back == LOW) && (forward == LOW)){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  else if ((volume == 2) && (distance==3)){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(heart_led, HIGH);
  }
  
  else if ((volume == 4) && (distance==4)){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(heart_led, HIGH);
  }
 
  
  else if((back == LOW) && (forward == HIGH) && (volume != 3 ) && (volume != 4)){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(speed);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(speed);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(speed);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(speed);

  }
  else if((back == HIGH) && (forward == LOW)){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(speed);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(speed);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(speed);

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(speed);

  }
  if (speed == 3){
    flow_rate=0.8;
  }
  else if(speed ==4){
    flow_rate=0.9;
  }
  else if(speed ==5){
    flow_rate=1;
  }  
  if (distance <= 2){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("VOlume: 0ml");
    display.print("Flow Rate:  ");
    display.print(flow_rate);
    display.println("ml/s");
    display.display();
  }
  if (distance == 3){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("VOlume: 2ml");
    display.print("Flow Rate:  ");
    display.print(flow_rate);
    display.println("ml/s");
    display.display();
  }
  if (distance == 4){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("VOlume: 4ml");
    display.print("Flow Rate:  ");
    display.print(flow_rate);
    display.println("ml/s");
    display.display();
  }
  if (distance == 5){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("VOlume: 6ml");
    display.print("Flow Rate:  ");
    display.print(flow_rate);
    display.println("ml/s");
    display.display();
  }
  if (distance == 6){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("VOlume: 8ml");
    display.print("Flow Rate:  ");
    display.print(flow_rate);
    display.println("ml/s");    
    display.display();
  }
  if (distance >= 7){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("VOlume: 10ml");
    display.print("Flow Rate:  ");
    display.print(flow_rate);
    display.println("ml/s");
    display.display();
  }
  IR = digitalRead(IR_sensor);
  if(IR == LOW){
    digitalWrite(syringe_finshed_led, HIGH);
    tone(buzzer, 1000);
  }
  else{
    digitalWrite(syringe_finshed_led, LOW);
    noTone(buzzer);
  }
}