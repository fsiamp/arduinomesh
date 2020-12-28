
// Include Libraries
#include "Arduino.h"
#include "Pump.h"
#include "LIDARLite.h"
#include "Wire.h"
#include "HX711.h"
#include "Button.h"


// Pin Definitions
#define BLOWER_PIN_COIL1	5
#define FINGERPRINTSCANNER_5V_PIN_RX	10
#define FINGERPRINTSCANNER_5V_PIN_TX	11
#define SCALE_PIN_DAT	3
#define SCALE_PIN_CLK	2
#define TILTSWITCH_PIN_2	4



// Global variables and defines

// object initialization
Pump blower(BLOWER_PIN_COIL1);
LIDARLite lidarLite;
HX711 scale(SCALE_PIN_DAT, SCALE_PIN_CLK);
#define calibration_factor 2280 //This value is obtained using the SparkFun_HX711_Calibration sketch https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide?_ga=2.77038550.2126325781.1526891300-303225217.1493631967
Button TiltSwitch(TILTSWITCH_PIN_2);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    lidarLite.begin(0, true); // Set configuration to default '0', change this number to try out alternate configurations. I2C speed set to 400 kHz.
    scale.set_scale(calibration_factor); 
    scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
    TiltSwitch.init();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // Blower - Squirrel Cage (12V) - Test Code
    // The water pump will turn on and off for 2000ms (4 sec)
    blower.on(); // 1. turns on
    delay(2000);       // 2. waits 500 milliseconds (0.5 sec).
    blower.off();// 3. turns off
    delay(2000);       // 4. waits 500 milliseconds (0.5 sec).

    }
    else if(menuOption == '2')
    {
    // Disclaimer: The Fingerprint Scanner - TTL (GT-511C3) is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '3') {
    // LIDAR-Lite v3 - Test Code
    // Take a measurement with receiver bias correction and print to serial terminal
    int lidarLiteDist = lidarLite.distance();
    Serial.print(lidarLiteDist);
    Serial.println(" [cm]");
    delay(50);
    }
    else if(menuOption == '4') {
    // SparkFun HX711 - Load Cell Amplifier - Test Code
    float scaleUnits = scale.get_units(); //scale.get_units() returns a float
    Serial.print(scaleUnits); //You can change this to lbs but you'll need to refactor the calibration_factor
    Serial.println(" Kg"); //You can change this to lbs but you'll need to refactor the calibration_factor
    }
    else if(menuOption == '5') {
    // Tilt Sensor - AT407 - Test Code
    //Read Tilt Switch state. 
    //if Switch is tilted function will return HIGH (1). if not function will return LOW (0). 
    //for debounce funtionality try also TiltSwitch.onPress(), .onRelease() and .onChange().
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    bool TiltSwitchVal = TiltSwitch.read();
    Serial.print(F("Val: ")); Serial.println(TiltSwitchVal);

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Blower - Squirrel Cage (12V)"));
    Serial.println(F("(2) Fingerprint Scanner - TTL (GT-511C3)"));
    Serial.println(F("(3) LIDAR-Lite v3"));
    Serial.println(F("(4) SparkFun HX711 - Load Cell Amplifier"));
    Serial.println(F("(5) Tilt Sensor - AT407"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing Blower - Squirrel Cage (12V)"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Fingerprint Scanner - TTL (GT-511C3) - note that this component doesn't have a test code"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing LIDAR-Lite v3"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing SparkFun HX711 - Load Cell Amplifier"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing Tilt Sensor - AT407"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/