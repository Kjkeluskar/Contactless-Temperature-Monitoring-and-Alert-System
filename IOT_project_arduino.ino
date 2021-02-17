#define BLYNK_PRINT Serial
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define echoPin 12 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 13 //attach pin D3 Arduino to pin Trig of HC-SR04
int myCounter = 0; //declare your variable myCounter and set to 0

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
SoftwareSerial Serial1(10, 11);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
String str, str1;
int temp=0;
int ambTemp;
int objTemp;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  mlx.begin(); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Start the OLED display
  display.clearDisplay();
  display.display();
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,4);                
  display.println("Distance:");
  

}

void loop() {
  digitalWrite(trigPin, LOW); //Set trigger pin low
  delayMicroseconds(2000); //Let signal settle
  digitalWrite(trigPin, HIGH); //Set trigPin high
  delayMicroseconds(15); //Delay in high state
  digitalWrite(trigPin, LOW); //ping has now been sent
  delayMicroseconds(10); //Delay in high state

   digitalWrite(trigPin, LOW);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  digitalWrite(10, HIGH);

  if (distance > 20) {
      display.setTextSize(1);
      display.setCursor(40,2);
      display.println("Come Closer");
      digitalWrite(10, HIGH);
      display.display();
      display.clearDisplay();
    
  }
  else if (distance < 20) {
      display.setTextSize(1);
  display.setCursor(40,2);
  display.println("Hold steady");
  
    digitalWrite(10, HIGH);
    delay(2000);
    digitalWrite(10, LOW);
    digitalWrite(9, HIGH);
    display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,22);                
  display.println("Target");
  display.display();
  delay(2000);
    display.setTextSize(2);
    display.setCursor(50,17);
    display.println(mlx.readObjectTempC(),1);
    
    display.setCursor(110,17);
    display.println("C");
    if(mlx.readObjectTempC()>32)
    {
      //INPUT - FREQUENCY - TIME THAT LASTS
    tone(8, 800, 300);
    }
  
  display.display();
  }
  display.clearDisplay();
  delay(2000);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  

}
