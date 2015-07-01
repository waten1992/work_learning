#include "header.h"
#include "utils.h"

static char str_error[1024];
int debug_output = 5;
#if 0
void set_error(const char *err)
{
	bzero(str_error, sizeof(str_error));
	strncpy(str_error, err, sizeof(str_error));
	if(debug_output >=5) {
		printf("[error] %s\n",str_error);
	}
}

#endif
void set_error(const char *fmt, ...)
{
	char buff[128];
	va_list ap;
	bzero(buff, sizeof(buff));
	va_start(ap, fmt);
	vsnprintf(buff ,sizeof(buff),fmt,ap);
	strncpy(str_error, buff, sizeof(str_error));
	va_end(ap);
	if(debug_output >=1) {
		printf("[error] %s\n",buff);
	}
}


void get_error(char *buff, int *len)
{
	if(*len >(int)sizeof(str_error)) {
		*len=sizeof(str_error);
	}
	strncpy(buff, str_error, *len);
}

void set_debug(const char *fmt, ...)
{
	if(debug_output <5) {
		return;
	}
	va_list ap;
	va_start(ap, fmt);
	//	vsnprintf(str_error, sizeof(str_error),
	//			fmt,ap);
	fprintf(stdout,"[debug] ");
	vfprintf(stdout, fmt,ap);
	fprintf(stdout,"\n");
	//printf("%s\n", str_error);
	va_end(ap);
}

