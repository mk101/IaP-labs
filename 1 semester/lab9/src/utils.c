#include "utils.h"

#ifdef WIN32
#include <Windows.h>

void wait(unsigned int ms) {
	Sleep(ms);
}

#elif unix
#include <time.h>

void wait(unsigned int ms) {
	struct timespec ts;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;
	nanosleep(&ts, NULL);
}
#endif 

void copy(int* from, int* to, int len) {
	for (int i = 0; i < len; i++) {
		to[i] = from[i];
	}
}

int testSort(int arr[], int count) {
	int min = arr[0];
	for (int i = 1; i < count; i++) {
		if (arr[i] < min)
			return i + 1;
		min = arr[i];
	}

	return 0;
}