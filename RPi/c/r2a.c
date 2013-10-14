#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rs232.h"

#define COMPORT 24 //see rs232.c for the full list.  This is /dev/ttyACM0, for the Arduino Mega 2560
#define BAUDRATE 9600
#define OPENDELAY 1
int main (int argc, char **argv) {
	int i,n=1;
	unsigned char send_char = 49;
	unsigned char buf[4096];
	if (RS232_OpenComport(COMPORT, BAUDRATE)) {
		printf("Can't open com port\n");
		return(0);
	}
	usleep(OPENDELAY*1000000); // x sec delay
	
	if (RS232_SendByte(COMPORT, send_char)) 
		printf("Error sending byte\n");
	while (n) {
		n = RS232_PollComport(COMPORT, buf, 4096);
		if (n > 0) {
			buf[n] = 0;
			for (i=0; i < n; i++) 
				if (buf[i] < 32)
					buf[i]='.'; //replace unreadable chars with dots
			printf("Received %i bytes: [%s]\n",n, (char *)buf);
		}
	}


	usleep(5000000);
	
	RS232_CloseComport(COMPORT);
	
}
