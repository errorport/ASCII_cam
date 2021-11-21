#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <stdint.h>

extern uint8_t hue_offset	= 1
extern uint8_t hue_gain		= 10

extern char characters[9] = {'█', '▓', '▒', '░', '•', '×', ':', '·', ' '};

extern uint8_t brightness_steps[9] = {0, 20, 40, 60, 80, 100, 120, 140, 255};

extern uint8_t color_prefixes = {
	31, // RED
	33, // YELLOW
	32, // GREEN
	36, // CYAN
	34, // BLUE
	35, // MAGENTA
};

#endif
