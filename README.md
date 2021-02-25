# SqueakMail
![squeakmail](/images/SqueakMail.png)

Do you use humane (live) mouse traps? Do you hate checking them every day to make sure that a critter isn't dying of thirst/hunger?

For <$10 USD, you can build a SqueakMail to alert you when the trap has been triggered.

# **Supplies:**
1. an ESP32 or ESP8266 microcontroller ![esp8266](/images/esp8266.jpg)(~[$6](https://www.amazon.com/Wireless-NodeMcu-Internet-Development-ESP8266/dp/B0829L36V6))
1. an Obstacle Avoidance Sensor ![ir_obstacle_sensor](/images/ir_obstacle_sensor.jpg)(~[$4](https://www.amazon.com/Infrared-Obstacle-Avoidance-Reflective-Photoelectric/dp/B081YR8NY1), down to <$1 if you buy in a multipack)

*Mouse Trap itself*
* Reusable humane / live mouse trap ![mouse_trap](/images/mouse_trap.jpg)(~[$6](https://www.amazon.com/dp/B08219DSXP))
  * There are many sellers for this same style of traps
  * SqueakMail's enclosure makes use of the holes on the top of the traps. Some variations don't include those holes. If you have them you can either drill holes or modify the 3D printed enclosure accordingly

# Step 1: Create a IFTTT (If This Then That) Email Trigger
* Go to Random Nerd Tutorials and set up IFTTT following their instructions [ESP32 HTTP POST with Arduino IDE](https://randomnerdtutorials.com/esp32-http-post-ifttt-thingspeak-arduino/)
*(for SqueakMail, skip their ThingSpeak section and jump to the section ```2. ESP32 HTTP POST (IFTTT.com)```*

# Step 2: Upload the Attached Sketch ([SqueakMail.ino](squeakmail.ino)) to Your ESP32/ESP8266
* Before you upload, edit the file to replace the **ssid**, **password**, **serverName** with your own WiFi SSID, WiFi password, and IFTTT API Key respectively
* Edit **timerDelay** to set how often you will get emails once the mouse has been caught. The default 30000 = 30 seconds
* Upload the file to your microcontroller

# Step 3: Wire Your Obstacle Sensor
![wiring](/images/wiring.png)
* Wire your Sensor's VCC to your ESP's 5V or 3V3 (either one should work)
* Wire your Sensor's GND to your ESP's GND
* Wire your Sensor's OUT to your ESP's Pin12 (change this to another Pin as needed based on your ESP layout)

# Step 4: 3D Print the Holder ([SqueakMail.stl](SqueakMail.stl))
![3d_enclosure](/images/3d_enclosure.png)
* The ESP holder has 2 pegs that tab into the top holes nearest the door (the pegs don't take up all the space so oxygen should still flow. also 11 out of the 13 holes remain completely unobstructed)
* The Sensor holder fits into the groove at the bottom of the ESP holder and should situate the IR sensors slightly past the door and high up enough that it should stay out of the way of the mouse
* You may need to tune the sensor's sensitivity using a phillips head screwdriver so that it triggers/lights up when the door is closed, but not when the door is open

1. Fit the ESP holder onto the trap
1. Fit the Sensor into the Sensor holder
1. Fit the Sensor holder into the ESP holder
1. Fit the ESP into the ESP holder

# How Does the Code Work
Pseudocode logic:

* Flashes the onboard LED 3 times upon startup so you can visually see it initiate
* Connects to your WiFi using your credentials
* Posts to IFTTT, you will get an email with "trap initiated"
* Starts a timer for how long it's been since the trap has been set
* When it detects that the sensor has been triggered (door blocks the sensor because it's been closed)
  * Starts a second timer for how long it's been since the mouse has been trapped
  * Post to IFTTT, you will get an email "Trap has been running for <Trap Timer>. Mouse has been trapped for <Mouse Timer>

# Video Demonstration
![squeakmail_demo](/images/squeakmail_demo.gif)

# How you can support Mewt
<details>
 <summary>Click to expand</summary>
 
 All I ask is that you take a moment to do something kind.  
  
 * Think of what you would have been willing to contribute to the Mewt project (however small the amount), and donate that to your favorite charity instead.
 
 * See someone hungry or cold?  Buy them a small meal or cheap socks.
 
 * Have elderly neighbors?  Offer to help shovel their driveway or mow their lawn.
 
 * People across the political divide have you on edge?  Bake them some cookies just to be nice.
 
 * Even something as simple as given a random stranger your best smile.  
 
 If you can report back via this 5 second [#SqueakMailForGood questionnaire](https://www.surveymonkey.com/r/DFHGL6H), it would really make my day.  I'm hoping we can push out $1000 and/or 100 hours of kindness from this little corner of the internet.
 </details>

# Questions/Comments/Help
Join me on the [SqueakMail Discord](https://discord.gg/9AsQSmHgDM)

# Acknowledgments
<details>
 <summary>Click to expand</summary>
A big thank you to the below:

* @plbarrio for 3D [Customizable ESP32 lateral support](https://www.thingiverse.com/thing:3884388)
* Random Nerd Tutorial for [IFTTT tutorial](https://randomnerdtutorials.com/esp32-http-post-ifttt-thingspeak-arduino/)
* OpenMoji for 
  * [mouse face](https://openmoji.org/library/#search=mouse%20mail&emoji=1F42D)
  * [envelope](https://openmoji.org/library/#search=mouse%20mail&emoji=2709)
</details>

 
