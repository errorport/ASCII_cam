#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <omp.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <sys/ioctl.h>

#include <config.hpp>

using namespace std;

void get_winsize(winsize* w);

int main(void) {
	cv::VideoCapture cap;
	cap.open(0);
	if(cap.isOpened()){
		cv::Mat input_frame;
		cv::Mat resized_frame;
		struct winsize w;
		chrono::_V2::system_clock::time_point t_start;
		chrono::_V2::system_clock::time_point t_end;
		while(1) {
			t_start = chrono::high_resolution_clock::now();
			cap.read(input_frame);
			if (!input_frame.empty()){
				get_winsize(&w);
				cv::resize(input_frame, resized_frame, cv::Size(w.ws_row, w.ws_col));
			}
			t_end = chrono::high_resolution_clock::now();
			//printf("D: %dms\n\r", chrono::duration_cast<chrono::microseconds>(t_end - t_start));
		}
	} else {
		return 1;
	}
	return 0;
}

void get_winsize(winsize* w) {
	ioctl(0, TIOCGWINSZ, w);
	//printf("lines %d\n", w->ws_row);
	//printf("columns %d\n", w->ws_col);
}
