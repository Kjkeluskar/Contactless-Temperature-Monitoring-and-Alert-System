#define BLYNK_PRINT Serial
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

SoftwareSerial Serial1(10, 11);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
String str;
int ambTemp;
int objTemp;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);  
  mlx.begin(); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Start the OLED display
  display.clearDisplay();
  display.display();
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

}

void loop() {
  display.clearDisplay();
  digitalWrite(9, HIGH);
  delay(3000); //delay 4 secs
  digitalWrite(9, HIGH);
  digitalWrite(9, HIGH);
  display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,4);                
  display.println("Ambient"); 
  
  display.setTextSize(2);
  display.setCursor(50,0);
  display.println(mlx.readAmbientTempC(),1);
 
  display.setCursor(110,0);
  display.println("C");
  
  display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,20);                
  display.println("Target"); 
  
  display.setTextSize(2);
  display.setCursor(50,17);
  display.println(mlx.readObjectTempC(),1);
  
  display.setCursor(110,17);
  display.println("C");
  
  display.display();

  str =String('A')+String(mlx.readAmbientTempC())+String(' ') + String('O')+String(mlx.readObjectTempC());
  Serial1.println(str);

  if(mlx.readObjectTempC()>35) {
    //INPUT - FREQUENCY - TIME THAT LASTS
    tone(8, 800, 300);
  }
  digitalWrite(9, LOW);
  
  digitalWrite(10, HIGH);
  delay(10000); //delay 10 secs
  digitalWrite(10, LOW);
}
