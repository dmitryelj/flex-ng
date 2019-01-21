// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

int verbose_level = 2;
int timestamp = 0;
bool dont_flush = false;
bool is_startline = true;
char *label = NULL;

void _verbprintf(int verb_level, const char *fmt, ...)
{
	char time_buf[20];
	time_t t;
	struct tm* tm_info;

	if (verb_level > verbose_level)
		return;
	va_list args;
	va_start(args, fmt);

	if (is_startline)
	{
		if (label != NULL)
			fprintf(stdout, "%s: ", label);

		if (timestamp) {
			t = time(NULL);
			tm_info = localtime(&t);
			strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);
			fprintf(stdout, "%s: ", time_buf);
		}

		is_startline = false;
	}
	if (NULL != strchr(fmt, '\n')) /* detect end of line in stream */
		is_startline = true;

	vfprintf(stdout, fmt, args);
	if (!dont_flush)
		fflush(stdout);
	va_end(args);
}