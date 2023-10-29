#include<stdio.h>

int main(int argc, char *argv[])
{
	double squelch_on=0.02;
	double squelch_off=0.01;

	double i[3]={0,0,0};
	double q[3]={0,0,0};
	
	double t,x;
	double avg_power=0;
	int cnt=0;
	int on_off=0;
	while (scanf("%lf%lf", &t, &x)==2) {
		int ph=cnt%4;
		if (ph==0) i[0]=x;
		if (ph==1) q[0]=x;
		if (ph==2) i[0]=-x;
		if (ph==3) q[0]=-x;
		if (cnt%2==1) {
			double i_=i[0]-i[1];
			double q_=q[0]-q[1];
			double ia=(i[0]+i[1])/2;
			double qa=(q[0]+q[1])/2;

			double f_=i_*qa-q_*ia;
			double p=ia*ia+qa*qa;

			avg_power=(avg_power*0.99)+(p*0.01);

			if (avg_power>squelch_on) on_off=1;
			if (avg_power<squelch_off) on_off=0;

			double f=f_/avg_power;
			if (on_off==0) f=-2;

			if (f<-1) f=-1;
			if (f>1) f=1;

			printf("%lf %lf\n", t, f*0.5);

			for (int n=0; n<2; n++) {
				i[n+1]=i[n];
				q[n+1]=q[n];
			}
		}
		cnt=cnt+1;
	}
}
