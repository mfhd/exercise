#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

int main()
{
	FILE *fp;
	fp = fopen("./config","r");
	char line[256];
	int linenum = 0;
	char conf[10][2][256];
	while(fgets(line,256,fp) !=NULL)
	{
		sscanf(line,"%s %*s %s",conf[linenum][0],conf[linenum][1]);
		linenum++;
	}
	char logdlp[30];
	if (strstr(conf[0][0],"logtype") !=NULL)
	{
		sprintf(logdlp,"./log%s.so",conf[0][1]);
	}
	else
	{
		printf("missing config params\n");
		return 1;
	}
	fclose(fp);

	void* cdl_handle;
	void* ldl_handle;
	float (*crect)(float a, float b);
	float (*ccircle)(float r);
	float (*cnewton)(float l,float r,int a,int b,int c,int d);
	int (*log)();

	cdl_handle = dlopen("./libcalc.so", RTLD_LOCAL | RTLD_LAZY);
	if(cdl_handle == NULL)
	{
		fputs(dlerror(), stderr);
		return 1;
	}

	*(void **)(&crect) = dlsym(cdl_handle, "calcRectArea");
	*(void **)(&ccircle) = dlsym(cdl_handle, "calcCircleArea");
	*(void **)(&cnewton) = dlsym(cdl_handle, "calcNewton");

	ldl_handle = dlopen(logdlp, RTLD_LOCAL | RTLD_LAZY);
	if(ldl_handle == NULL)
	{
		fputs(dlerror(), stderr);
		return 1;
	}

	*(void **)(&log) = dlsym(ldl_handle, "logstr");

	if(crect == NULL || ccircle == NULL || cnewton == NULL)
	{
		fputs(dlerror(), stderr);
		return 1;
	}
	char lstr[100];
	int input;
	float a;
	float b;
	float c;
	float d;
	int l;
	int r;

	printf("What kind of Area do you want to calculate?\n");
	printf("1 -> Rectangle\n2 -> Circle\n3 -> Under a Function\n");
	scanf("%i",&input);

	switch(input)
	{
	case 1: //Rectangle
		printf("a = ");
		scanf("%f",&a);
		printf("b = ");
		scanf("%f",&b);
		sprintf(lstr,"Area of the Rectangle: %f", (*crect)(a,b));
		(*log)(lstr);
		break;

	case 2: //Circle
		printf("r = ");
		scanf("%f",&a);
		sprintf(lstr,"Area of the Circle: %f", (*ccircle)(a));
		(*log)(lstr);
		break;

	case 3: //Newton
		printf("f(x) = (a + b*x + c*x^2 + d*x^3)\n");
		printf("a = ");
		scanf("%f",&a);
		printf("b = ");
		scanf("%f",&b);
		printf("c = ");
		scanf("%f",&c);
		printf("d = ");
		scanf("%f",&d);
		printf("Left Border = ");
		scanf("%i",&l);
		printf("Right Border = ");
		scanf("%i",&r);
		sprintf(lstr,"Area under the function: ~%i", (int)((*cnewton)(l,r,a,b,c,d)+0.1));
		(*log)(lstr);
		break;
	}

	dlclose(cdl_handle);
	dlclose(ldl_handle);
	
	return 1;
}
