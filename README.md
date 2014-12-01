HauntOS
=======

Raspberry Pi->Arduino Haunted House Remote Controller

This is a set of code that I wrote in 2013 to control my home haunt props wirelessly using a Raspberri Pi and a set of Arduino
microcontrollers. The Raspberry Pi is used as a simplistic html web server. The html pages can be viewed on virtually any
device which supports a web browser. The RPi can be outfitted with a WiFi adapter (or simply connected to an Ethernet 
network which includes a WiFi access point). The RPI serves up a single web page that contains graphical "hot spots"
(which I actually created using PowerPoint), when when clicked / pressed by the user, then invoke a very simple PHP
script. The PHP script writes a command out the RPI's serial USB port, which is connected to an Arduino's USB input port
(I used an Arduino Mega but virtually any Arduino should work just fine, so long as it has a USB input).

The Arduino "catches" the serial command coming in from the RPi, which is a simple string that indicates which prop to activate.
The Arduino code, written in C, then activates the appropriate output port (which can be digital or analog), which then triggers
the prop. In my haunt I use a set of relay controllers which take an output from the Arduino and use that to trigger a relay,
which then sets off the prop. 

The advantage of this architecture is that it's very easy to get a web server running on the RPi, and since the RPi supports
a wide number of USB WiFi adapters, it's very simple to get it up on WiFi. Then any device, including PCs, tablets and 
smartphones, can control the haunt. There is virtually no limit to the number of props that can be controlled, especially when
an Arduino Mega is used (which has literally dozens of I/O ports).

After using this in my haunt last year, I learned several important tings, which I planned to fix this year but ran out of time.
These are as follows:

1. There is a definite delay between the time that the user presses an option on the web page and when the prop gets 
activated. This is due to a couple of things, mostly related to the time it takes to process the html page (the RPi isn't 
exacty a speedy machine after all). This resulted in a bit of frustration, as when you're running a haunt, you really want
nearly instantaneous response to commands, as the difference between a prop working as intended and missing the mark can be as
fine as a second.

2. To address this, I intend to replace the RPi/WiFi architecture with an Arduino Mega running an XBee Series 1 communications
card. Basically I want to create a self contained controller in a box, complete with a rechargeable battery, based on the
Arduino/XBee combo. I plan to use touch screens as the user interface (which are now pretty cheap). When the user presses a
"button" on the touchscreen, the Arduino will immediately send the command out over the XBee bus to a set of "slave"
Arduino controllers, also equipped with XBee cards. This should result in nearly instantaneous response time and a fully
mobile controller capable to controlling props as far as 300 feet away (note that XBee "Pro" cards can go considerably further
that that, if additional distance is required). 

3. I also came to realize that some props still work best with good physical triggers, like step switches or passive infrared 
motion sensors. Especially as the quantity of automated props increases in my haunt, it becomes more unrealistic to think 
that one human could orchestrate the whole thing. So a combination of automated and manually triggered props makes the most
sense to me.

4. I began using actors in my haunt last year, which I continued this year (I had four highschoolers helping this year). 
Actors are so much more flexible and creative than any amount of technology can be. Now giving the actors specialized
controllers that allow them to set off one or two props in their "area" might make a whole lot of sense...and my new
architecture outlined in #2 above can be easily expanded to accomodate multiple controllers. 

I will continue to update this area as I update the code for the new "Haunt OS" controller.
