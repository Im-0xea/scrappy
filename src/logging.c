#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static void
logout(const int color, const char * label, const char * fmt, va_list args)
{
	fprintf(stderr, "\033[%dm[%s] ", color, label);
	vfprintf(stderr, fmt, args);
	fputs("\033[0m\n", stderr);
}
	
void lerror(const int code, const char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	logout(31, "Error", fmt, args);
	va_end(args);
	if (code != -1)
		exit(code);
}
void lwarn(const char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	logout(33, "Warning", fmt, args);
	va_end(args);
}
void linfo(const char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	logout(37, "Info", fmt, args);
	va_end(args);
}
void ldebug(const char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	logout(37, "Info", fmt, args);
	va_end(args);
}
