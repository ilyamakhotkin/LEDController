#include "DS1822.h"

//private function definitions
void temp_init(void);
void w0();
void w1();
char read();
void w_cmd(char cmd);
char r();

int TEMP_GET_T(void){
	unsigned int temp;

	temp_init();
	w_cmd(SR);
	w_cmd(CT);
	while(!r());

	temp_init();
	w_cmd(SR);
	w_cmd(RS);

	temp = read();
	temp |= (read()<<8);
	//temp = temp >> 4;
	return temp;
}

// Port2, 0 = power, 1 = communication, 2 = GND
void TEMP_GPIO_init(void){
	P2DIR |= BIT0 | BIT2;
	P2DIR &= ~WIRE;
	P2OUT |= WIRE | BIT0;
	P2OUT &= ~BIT2;
	P2REN |= WIRE;
}

void temp_init(void){
	down
	__delay_cycles(480);
	up
	__delay_cycles(60);
	while((P2IN & WIRE));// wait if no presence pulse
	__delay_cycles(440);
}


void w1(void){
	down
	__delay_cycles(2);
	up
	__delay_cycles(60);
}

void w0(void){
	down
	__delay_cycles(60);
	up
	__delay_cycles(2);
}

char r(void){
	down
	__delay_cycles(2);
	up
	__delay_cycles(8);
	char result = P2IN & WIRE; // sample within 15us
	__delay_cycles(50); // time slot is 60us
	return result >> 1;
}

char read(void){
	char counter = 0;
	char reply = 0;
	while (counter < 8){
		reply |= r() << counter;
		counter++;
	}
	return reply;
}

void w_cmd(char cmd){
	int counter = 8;
	while (counter != 0){
		if (cmd & 1) w1();
		else w0();
		cmd = cmd>>1;
		counter --;
	}
}

void TEMP_int_to_string(int temp, char* string){
	int number;

	if (temp < 0 ){
		string[0] = '-';
		temp = 0 - temp;
	} else string[0] = ' ';

	number = temp >> 4;

	string[3] = (number % 10) + '0';
	number /= 10;
	string[2] = (number % 10) + '0';
	number /= 10;
	string[1] = (number % 10) + '0';

	string[4] = '.';

	number = temp & 0xF;
	number *= 625;

	//char counter;

	string[5] = (number / 1000) + '0';
	string[6] = 0;

	/*for (counter = 8; counter > 4; counter--){
		string[counter] = (number % 10) + '0';
		number /= 10;
	}*/
	string[7] = 0;
}
