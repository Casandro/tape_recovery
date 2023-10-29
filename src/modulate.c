#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define SRATE 48000
#define BRATE 1200

#define F_1 1300.0
#define F_0 2100.0

double phi=0;


void output(const int bit, const int samples)
{
	for (int n=0; n<samples; n++) {
		if (bit!=0) {
			phi=phi+F_1/SRATE*2*M_PI;
		} else {
			phi=phi+F_0/SRATE*2*M_PI;
		}
		printf("0 %lf\n", sin(phi)*0.5);
	}
}

void write_bit(const int bit)
{
	output(bit, SRATE/BRATE);
}

void write_byte(const int byte)
{
	write_bit(0);
	for (int n=0; n<8; n++) {
		write_bit((byte>>n)&0x1);
	}
	write_bit(1);
}

void write_gap()
{
	int rnd=random() % 80;
	output(1, rnd);
}

char *testtext="Hallo Welt Geb\x19Huren Geb\x1dHren Testtext";

int main(int argc, char *argv[])
{
	for (int m=0; m<10; m++) {
		output(1,1000);
		output(0,1000);
	}
	output(1, 500);
	for (int m=0; m<20; m++) {
		for (int n=0; n<strlen(testtext); n++) {
			write_byte(testtext[n]);
			write_gap();
			output(1, 100);
		}
		output(1,500);
	}

}
