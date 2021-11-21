#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <stdint.h>
#include <wchar.h>

// OPT
#define COLOR_COUNT	6
#define STEP_COUNT	9
#define LINE_LENGTH 1024
#define CHAR_LENGTH 16

extern uint8_t hue_offset	= 1;
extern uint8_t hue_gain		= 10;

extern wchar_t characters[STEP_COUNT] = {L'█', L'▓', L'▒', L'░', L'•', L'×', L':', L'·', L' '};

//extern uint8_t brightness_steps[STEP_COUNT] = {255, 140, 120, 100, 80, 60, 40, 20, 0};
extern uint8_t brightness_steps[STEP_COUNT] = {0, 20, 40, 60, 100, 120, 140, 255};

extern uint8_t color_prefixes[COLOR_COUNT] = {
	31, // RED
	33, // YELLOW
	32, // GREEN
	36, // CYAN
	34, // BLUE
	35, // MAGENTA
};

#endif
