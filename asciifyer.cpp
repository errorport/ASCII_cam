#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <omp.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <sys/ioctl.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>

#include <config.hpp>

using namespace std;

void get_winsize(winsize* w);

uint8_t colorize(uint8_t hue_value);

wchar_t asciify(uint8_t value);

void insert_character(wchar_t*, uint16_t*, cv::Vec3b);

int main(void) {
	setlocale(LC_ALL, "en_US.UTF-8");
	fwide(stdout, 1);
	cv::VideoCapture cap;
	cap.open(0);
	if(cap.isOpened()){
		cv::Mat input_frame;
		cv::Mat resized_frame;
		cv::Mat hsv_frame;
		struct winsize w;
		chrono::_V2::system_clock::time_point t_start;
		chrono::_V2::system_clock::time_point t_end;
		uint32_t frame_size = 0;
		while(1) {
			t_start = chrono::high_resolution_clock::now();
			cap.read(input_frame);
			if (!input_frame.empty()){
				get_winsize(&w);
				cv::resize(input_frame, resized_frame, cv::Size(w.ws_col, w.ws_row));
				cv:: normalize(resized_frame, resized_frame, 255, 0, cv::NORM_MINMAX, -1, cv::noArray());
				cv::cvtColor(resized_frame, hsv_frame, cv::COLOR_BGR2HSV);
				wchar_t table[MAX_ROWS][LINE_LENGTH];
				#pragma omp parallel for
				for(size_t hidx = 0; hidx < hsv_frame.rows; hidx++) {
					wchar_t line_str[LINE_LENGTH];
					uint16_t ch_idx = 0;
					for(size_t widx = 0; widx < hsv_frame.cols; widx++) {
						insert_character(line_str, &ch_idx, hsv_frame.at<cv::Vec3b>(hidx, widx));
					}
					//memcpy(table[hidx], line_str, LINE_LENGTH * sizeof(wchar_t));
					swprintf(table[hidx], LINE_LENGTH, L"%ls\n\r", line_str);
				}
				for(size_t hidx = 0; hidx < hsv_frame.rows; hidx++) {
					wprintf(L"%ls", table[hidx]);
				}
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

uint8_t colorize(uint8_t hue_value) {
	return color_prefixes[
		int(hue_offset + (hue_value * COLOR_COUNT * hue_gain) / 179) % COLOR_COUNT
	];
}

wchar_t asciify(uint8_t value) {
	for(size_t step_idx = 0; step_idx < STEP_COUNT; step_idx++) {
		if(value >= brightness_steps[step_idx]) {
			return characters[step_idx];
		}
	}
	return characters[0];
}

void insert_character(wchar_t* line_str, uint16_t* ch_idx, cv::Vec3b pixel) {
	*ch_idx += swprintf(
		line_str + *ch_idx
		, CHAR_LENGTH
		, L"\x1b[%dm%lc\x1b[0m", colorize(pixel[0]), asciify(pixel[2])
	);
}
