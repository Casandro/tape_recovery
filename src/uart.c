#include <stdio.h>
#include <string.h>


#define BITLEN 16

#define BULEN (BITLEN*32)
//This program takes input samples at 16 times the bitrate

int p=0; //Position of the oldest bit in the buffer

int buffer[BULEN];


void put_bit(int b) //Buts the bit into the ring buffer
{
	buffer[p]=b;
	p=(p+1)%BULEN;
}

int get_sample(int pos) //Gets the sample from position pos
{
	int p2=(p+pos)%BULEN;
	return buffer[p2];
}

int get_bit(int bit) //Gets the bit from the bit position 0=start 1-8=data 9=stop
{
	int pos=bit*BITLEN+1;
	int sum=0;
	for (int n=pos+7; n<pos+10; n++) sum=sum+get_sample(n)*3-1;
	if (sum<=0) return 0;
	return 1;
}


int is_start() //Check if there is a start condition
{
	if (get_sample(0)==0) return 0; //No prestart condition
	if (get_sample(1)==1) return 0; //No prestart condition
	if (get_bit(0)!=0) return 0; //No start bit
	return 1; //Apparently this is a start bit
}

int has_framing()//Check if the position has propper framing
{
	if (is_start()==0) return 0;
	//Add parity checks here, if you want
	return get_bit(9);
}

int main(int argc, char *argv[])
{
	memset(buffer, 0, sizeof(buffer));
	int countdown=BITLEN*10;
	double t,x;
	while (scanf("%lf%lf", &t, &x)==2) {
		if (x<0) put_bit(1); else put_bit(0);
		//prevent the system to detect a new byte
		if (countdown>0) {
			countdown=countdown-1;
			continue;
		}
		if (has_framing()!=0) { //framing found
			int byte=0;
			for (int n=0; n<8; n++) {
				byte=byte+ (get_bit(n+1)<<n);
			}
			double ot=t-((double)BULEN/19200.0);
			printf("%lf %d\n", ot, byte);
			countdown=BITLEN*8+BITLEN/2;
		}

	}
}
