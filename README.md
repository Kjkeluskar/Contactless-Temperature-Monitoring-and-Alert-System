# Contactless-Temperature-Monitoring-and-Alert-System

This project will enable the user to measure the temperature in a contactless manner using a short range IR temperature sensor.

# Requirements
# Hardware Requirements
<ul>
  <li> Arduino Uno R3 </li>
  <li> MLX90614 IR temperature sensor</li>
  <li> ESP8266 Wi-Fi module (NodeMCU used in this project)</li>
  <li> Compatible cables </li>
  <li> Breadboard </li>
  <li> Jumper wires (M-M & M-F)</li>
  <li> OLED i2c Display </li>
  <li> Piezo Buzzer </li>
  <li> 5V LED (Red and Green) </li>
  <li> 1K ohm resistors </li>  
</ul>

# Software Requirements
<ul>
  <li> Arduino IDE </li>
  <li> Thingspeak </li>
  <li> Blynk App </li>
</ul>

# Connections
Since the connections are unclear in the diagrams, following are the connections done for the project

# Arduino Connections
<ol>
  <li> Piezo Buzzer, positive= pin 8 of Arduino, negative=ground </li>
  <li> 5V LED, Red, positive=pin 10 of Arduino with 1K ohm resistors, negative=GND </li>
  <li> 5V LED, Green, positive=pin 9 of Arduino with 1K ohm resistors, negative=Gnd </li>
  <li> i2C OLED Display, SDA=A4, SCL=A5 </li>
  <li> MLX90614 IR temperature sensor, SDA=A4, SCL=A5 </li>
</ol>

# NodeMCU Connections
<ol>
  <li> MLX90614, D1=SDA, D2=SCL </li>
</ol>
  
  
  
Note: Main power supply to both, the NodeMCU and Arduino is given via laptop's USB
