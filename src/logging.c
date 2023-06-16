#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static void
log(const int color, const char * label, const char * fmt, va_list args)
{
	fprintf(stderr, "\033[%dm[%s] ", color, label)
	vfprintf(stderr, fmt, args);
	fputs(stderr, "\033[0m\n");
}
	
noreturn void lerror(const int code, const char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	log(31, "Error", fmt, args);
	va_end(args);
	if (code != -1)
		exit(code);
}
void lwarn(const int code, const char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	log(33, "Warning", fmt, args);
	va_end(args);
	exit(code);
}
void linfo(const int code, const char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	log(37, "Info", fmt, args);
	va_end(args);
	exit(code);
}
