#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	if (argc<3) {
		printf("Usage: %s <pause duration> <output directory>\n", argv[0]);
	}
	const double pause=atof(argv[1]);
	const char *dir=argv[2];
	printf("Pause detection: %lf s\nOutput directory: %s\n", pause, dir);
	double t=0;
	double t_last=-1;
	int byte=-1;
	FILE *f=NULL;
	int ocnt=-1;
	size_t fn_len=strlen(dir)+15;
	char *fn=malloc(fn_len);
	memset(fn, 0, fn_len);
	while (scanf("%lf%d", &t, &byte)==2) {
		double p=t-t_last;
		ocnt=ocnt+1;
		t_last=t;
		if ((t_last<0) || (p>pause)) {
			if (f!=NULL) {
				fclose(f);
				printf("%d bytes", ocnt);
				printf("\n");
				ocnt=-1;
				f=NULL;
			}
			ocnt=0;
			int minutes=t/60;
			double seconds=t-minutes*60;
			snprintf(fn, fn_len-1, "%s/%02d-%05.2lf.dat", dir, minutes, seconds);
			f=fopen(fn, "w");
			printf("%s: ", fn);
		}
		fprintf(f, "%c", byte);
	}
	if (f!=NULL) {
		fclose(f);
		printf("%d bytes\n", ocnt);
		ocnt=-1;
	}
}
