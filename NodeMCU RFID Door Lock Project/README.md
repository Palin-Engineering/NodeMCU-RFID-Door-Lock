<h1> Welcome to NodeMCU RFID Door Lock Project </h1>

Welcome to the NodeMCU (IoT) RFID Door/Draw Lock, the idea of this project was to make a simple and secure way to lock draws & doors. In this Instructables, I use a NodeMCU microcontroller which connects to the webserver and by using these components allow for remote management of RFID cards to unlock the draw. Furthermore, with the addition of a keypad adds another layer of security, particularly from cloning and losing the RFID card.

<hr>
<h2>Build Guide and Code Explination</h2>
For a detailed build guide, please check out this project on Instructables (see link below). There are detailed explanations of the code and how to deploy it to both the webserver and nodeMCU.

<a href="https://url.bzest.co.uk/6etrg1v">NodeMCU (IoT) RFID Door/Draw Lock (Instructables)</a>

<hr>
<h2>Addtional Libraries Needed for Arduino Code</h2>
For the Arduino Code in this project to work correctly a few addtional libraries are required to interface between the NodeMCU, webserver, RFID modules, I/O Expander and Keypad. Please add theese libraries to your Arduino IDE before deploying the code in this project.
<br>
<li>RFID library for RFID-RC522.   
<ul>  
<li><a href="https://github.com/miguelbalboa/rfid" rel="nofollow">https://github.com/miguelbalboa/rfid</a></li></ul></li><li>HTTP Client this allows for the NodeMCU to POST data to the web server:   
<ul>  
<li><a href="https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient" rel="nofollow">https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient</a></li></ul></li><li>Adafruit's MCP23017 Library this is used to interface with the I/O Expander over I2C   
<ul>   
<li><a href="https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library" rel="nofollow">https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library</a></li></ul></li><li>MCP23017 4x3 Keyboard Library. This is used to interface the I/O expander with the 4x3 keyboard.   
<ul>   
<li><a href="https://github.com/joeyoung/arduino_keypads/tree/master/Keypad_MC17" rel="nofollow">https://github.com/joeyoung/arduino_keypads/tree/master/Keypad_MC17</a></li></ul>
