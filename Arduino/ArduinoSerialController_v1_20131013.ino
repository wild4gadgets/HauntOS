/*
  This code reads a serial ASCII-encoded string, looking for a single integer command. Based on the integer received, the Arduino then takes action to activate a specific prop.
  The notion here is that there is a Raspberry Pi connected to the Arduino via serial (generally USB but on some boards this can also be other pins). The RPi has a web server
  running on it which is taking inputs via a device running a web browser. In my implementation I created a simple graphic image with "hot spots" that, when clicked (or pressed
  on a tablet), invokes an html file. The html file then makes a command-line shell call which simply sends the ASCII string over USB to the Arduino. This could of course be easily
  expanded via more complex code on the RPi, for example if you wanted to wait for a response from the Arduiuno, etc. Since I tend to build most of that logic into the Arduino my
  main driver here is to just take the input from the web browser and convert it to a very simple Arduino command. 
*/
//#define DEBUG //uncomment for debug mode

// pins for the effects. Change these as required. I've included the standard pin 13 testLED as it's a great way to test the code without requiring the Arduino be attached to anything.
const int testLED = 13;
const int doubleghoulpin1 = 7;
const int doubleghoulpin2 = 8;
const int effect2pin = testLED;
const int effect3pin = testLED;
const int effect1 = 1;
const int effect2 = 2;
const int effect3 = 3;

void setup() {
  // initialize serial:
  Serial.begin(9600); // make sure the baud rate on the RPi matches this
  #ifdef DEBUG
    Serial.print("Initialize....");
  #endif
  // make the pins outputs:
  pinMode(doubleghoulpin1, OUTPUT); 
  pinMode(doubleghoulpin2, OUTPUT); 
  pinMode(effect2pin, OUTPUT); 
  pinMode(effect3pin, OUTPUT); 
  #ifdef DEBUG
    Serial.println("complete....");
  #endif
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int RPiInput = Serial.parseInt(); 
    #ifdef DEBUG
      Serial.print("Received integer: [");
      Serial.print(RPiInput);
      Serial.println("]");
    #endif
    // look for the newline. That's the end of your
    // sentence:
    //if (Serial.read() == '\n') {
 
    switch(RPiInput) { // I put this into a switch statement so that additional logic can be added if needed
     case (effect1): // activate effect 1, which is double ghoul
       activate_effect(doubleghoulpin1, 2000); // initiate ghoul #1    delay(5000); // wait 5 secs to let drama build
       activate_effect(doubleghoulpin2, 2000); // initiate ghoul #2
       break;
     case (effect2): // activate effect 2
       activate_effect(effect2pin, 1000);
       break;
     case (effect3): // activate effect 3
       activate_effect(effect3pin, 1000);
        break;
     default:
     #ifdef DEBUG
       Serial.print("Error: invalid input: [");
       Serial.print(RPiInput);
       Serial.println("]");
     #endif
       break;
    }  
   //}
  }
}

void activate_effect(int effect, int delay_msec) {
  #ifdef DEBUG
    Serial.print("Activate effect pin #");
    Serial.print(effect);
    Serial.print("  delay ");
    Serial.println(delay_msec);
   #endif
    
   digitalWrite(effect,HIGH);
   delay(delay_msec);
   digitalWrite(effect,LOW);
}




