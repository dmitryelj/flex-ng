// FlexDemod.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

#include "multimon-ng/multimon.h"
#include "multimon-ng/BCHCode.h"

#define FREQ_SAMP            22050

// FLEX decoder support
struct Flex * Flex_New(unsigned int SampleFrequency);
void Flex_Demodulate(struct Flex * flex, double sample);
void Flex_Delete(struct Flex * flex);

void exec_cmd(const char* cmd)
{
	FILE* pipe = _popen(cmd, "rb");
	if (!pipe) return;

	struct Flex *flex = Flex_New(FREQ_SAMP);

	while (1) {
		int16_t buffer[16*1024] = {};

		int len = fread(buffer, 1, sizeof buffer, pipe);
		if (len <= 0) break;

		// printf(".");
		// printf("%d %d %d;", len, buffer[0], buffer[1]);

		for (int p = 0; p < len/2; p++) {
			double sample = 1.0f*buffer[p]/32768.0f;
			Flex_Demodulate(flex, sample);
		}
	}

	Flex_Delete(flex);

	_pclose(pipe);
}

int main(int argc, char **argv)
{
	printf("Flex-ng v0.2, a lightweight FLEX decoder, based on multimon-ng\n");
	printf("Made by Dmitrii Eliseev\n");
	printf("Use: flex-ng -f 169.65M -g 26 -p 0\n\n");

	char run_params[255] = "rtl_fm -s 22050";
	for (int i = 1; i < argc; ++i) {
		strcat(run_params, " ");
		strcat(run_params, argv[i]);
	}

	printf("Process started: %s\n\n", run_params);

	exec_cmd(run_params);
	return 0;
}
