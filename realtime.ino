/*  
 *  COVID-19 Data: https://www.worldometers.info/coronavirus/
 *  ThingSpeak: https://thingspeak.com/
  */
 #include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>


String apiKey = "9PFLMV479T8STXOC";     //  Enter your Write API key from ThingSpeak
char auth[] = "s8gfnM7NvqnovS1CNKnfCdiOXO8Urb7o"; //Auth code sent via Email
const char *ssid =  "Avengers";     // replace with your wifi ssid and wpa2 key
const char *pass =  "jmk123123";
const char* server = "api.thingspeak.com";
const char* host = "api.thingspeak.com";  //We read the data from this host                                   
  const int httpPortRead = 80;                                           
                                                  
  const char* url1 = "/apps/thinghttp/send_request?api_key=EB6KG6AK3BR1NEJS";     //Change this URL Cases
  const char* url2 = "/apps/thinghttp/send_request?api_key=GJB3WSS65LJ2SGVU";   //Deaths
  const char* url3 = "/apps/thinghttp/send_request?api_key=IEDCE69TOWZYSY7M";   //Recovered
  int To_remove;      //There are some irrelevant data on the string and here's how I keep the index
                      //of those characters 
  String Cases,Deaths,Recovered,Data_Raw,Data_Raw_1,Data_Raw_2,Data_Raw_3;  //Here I keep the numbers that I got

  WiFiClient client;      //Create a WiFi client and http client                                                     
  HTTPClient http; 
  


Adafruit_MLX90614 mlx = Adafruit_MLX90614();


int objTemp;
int ambTemp;

void setup() 
{
       Serial.begin(115200);
       delay(10);
        Blynk.begin(auth, ssid, pass); 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
     mlx.begin();  
     Wire.begin(D1,D2);
 
}
 
void loop() 
{
  if(mlx.readObjectTempC()>32){
    Blynk.notify("Alert : High Temperature Detected");
    Blynk.email("kjkeluskar1@gmail.com", "Sensor alert", "High temperature detected");
  }
  Blynk.run();

  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  {  
        String postStr = apiKey; 
         postStr +="&field2=";
         postStr += String(mlx.readAmbientTempC());
         postStr += "\r\n\r\n";
          postStr +="&field3=";
         postStr += String(mlx.readObjectTempC());
         postStr += "\r\n\r\n";

         client.print("POST /update HTTP/1.1\n");
         client.print("Host: api.thingspeak.com\n");
         client.print("Connection: close\n");
         client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
         client.print("Content-Type: application/x-www-form-urlencoded\n");
         client.print("Content-Length: ");
         client.print(postStr.length());
         client.print("\n\n");
         client.print(postStr);

         Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
        Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");

    }
    client.stop();
   
   //Reading 1: Reading of cases
    if( http.begin(host,httpPortRead,url1))        //Connect to the host and the url                                      
      {
        int httpCode = http.GET();                //Check feedback if there's a response                                                  
        if (httpCode > 0)                                                              
        {
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
            {                
              
              Data_Raw = http.getString();   //Here we store the raw data string
            
              
              Data_Raw_1 = Data_Raw;                                    
              To_remove = Data_Raw_1.indexOf(">");                      //I look for the position of this symbol ">"                                 
              Data_Raw_1.remove(0,To_remove+1);                        //I remove it and everything that's before
              To_remove = Data_Raw_1.indexOf("<");                     //I look for the position of this symbol ">"                                
              Data_Raw_1.remove(To_remove,Data_Raw_1.length());          //I remove it and everything that's after
                                                                     //Example: This is the raw data received <td style="font-weight: bold; text-align:right">63,927</td>
                                                                     //First we look for ">" and we remove everything before it including it
                                                                     //We stay with this 63,927</td>
                                                                     //We look for "<" symbol and we remove it + everything after
                                                                     //We keep only this 63,927 as string
              Cases=Data_Raw_1;
              Serial.print("Cases: ");  //I choosed to display it on the serial monitor to help you debug
              Serial.println(Cases); 
              
              Data_Raw_2=Data_Raw;
              To_remove = Data_Raw_2.indexOf("<span>");
              Data_Raw_2.remove(0,To_remove+6);
              Data_Raw_3=Data_Raw_2;
              To_remove = Data_Raw_2.indexOf("</span>");
              Data_Raw_2.remove(To_remove,Data_Raw_2.length());

              Deaths=Data_Raw_2;
              Serial.print("Deaths: ");
              Serial.println(Deaths);
            
              To_remove = Data_Raw_3.indexOf("<span>");
              Data_Raw_3.remove(0,To_remove+6);

              To_remove = Data_Raw_3.indexOf("<");
              Data_Raw_3.remove(To_remove,Data_Raw_3.length());

              Recovered=Data_Raw_3;
              
              Serial.print("Recovered: ");
              Serial.println(Recovered);    
                                                                                       
            }
        }
        else //If we can't get data
        {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        
        http.end();                                                                 
      } 
    else //If we can't connect to the HTTP
      {
        Serial.printf("[HTTP} Unable to connect\n");
      }

    while (WiFi.status() != WL_CONNECTED)     //In case the Wifi connexion is lost                                    
      { 
        
        WiFi.disconnect();                                                        
        delay(1000);                                                             
        
        WiFi.begin(ssid, pass);                                              
        Serial.println("Reconnecting to WiFi..");       
        delay(10000);                                                             
      }
  
  delay(10000); //delay 10 secs
}
