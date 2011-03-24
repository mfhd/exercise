#include <stdio.h>

void logstr(char* txt)
{
	FILE *fp;
	fp = fopen("./log","a");
	printf("write into log...\n");
	fprintf(fp,"%s\n",txt);
	printf("complete\n");
	fclose(fp);
}
