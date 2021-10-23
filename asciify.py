# -*- coding: utf-8 -*-
# Andrew Webb 02/2016

'''
Script to create high resolution ascii art from images.
Usage: python ascii.py <image-filename> <horizontal-resolution>
'''

import numpy as np
import cv2

import sys
import bisect
import time

# The printable characters from string.printable, minus \t, \r, \n
characters = ['█', '▓', '▒', '░', '•', '×', ':', '·', ' ']

# The brightnesses of each character, previously calculated by creating an image containing only that character
global_brightnesses = np.array([0.0, 20.0, 40.0, 60.0, 80.0, 100.0, 120.0, 140.0, 255.0])

# Color-circle order.
color_prefixes = [
	31, # red
	33, # yellow
	32, # green
	36, # cyan
	34, # blue
	35, # magenta
]

hue_offset = 1 # empiric
hue_gain = 1

indices = [0] * 256
frames = 0
start = time.time()

def colorize(hue):
	# Calculating color-circle index
	rang = len(color_prefixes)
	hue = (hue_offset + (hue * rang * hue_gain) // 360) % rang
	return str(color_prefixes[hue])

def asciify(image):
	global frames, t, indices

	# Downsample and convert to grayscale
	gray_image = 255 - cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

	# Normalize so that the whole range of characters is used
	upper_limit = gray_image.max()*((len(characters)+1)/float(len(characters)))
	lower_limit = gray_image.min()
	brightnesses = ((global_brightnesses - global_brightnesses.min()) / (global_brightnesses.max() - global_brightnesses.min() )) * (upper_limit - lower_limit) + lower_limit

	frames += 1
	elapsed = time.time() - start
	fps = int(frames / elapsed)
	fps_str = ' {} FPS'.format(fps)

	for c in range(gray_image.min(), gray_image.max() + 1):
		indices[c] = bisect.bisect(brightnesses, c)

	width = image.shape[1]
	height = image.shape[0]
	string = ''
	for h in range(height):
		for w in range(width):
			c = gray_image[h, w]
			character_index = indices[c]
			string += "\x1b["+ colorize(hsv[h, w][0]) +"m"
			string += characters[character_index]
			string += "\x1b[0m"
		string += '\n'
	#string = string[:-len(fps_str)-1] + fps_str
	print(string)
