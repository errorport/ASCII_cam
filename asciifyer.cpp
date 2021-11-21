#include <opencv2/core.hpp>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>

int main(void) {
	struct winsize w;
	while(1) {
		ioctl(0, TIOCGWINSZ, &w);
		printf ("lines %d\n", w.ws_row);
		printf ("columns %d\n", w.ws_col);
	}
	return 0;
}

