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

indices = [0] * 256
frames = 0
start = time.time()

def asciify(image):
	global frames, t, indices

	# Downsample and convert to grayscale
	gray_image = 255 - cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

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

	string = ''
	for row in gray_image:
		for c in row:
			character_index = indices[c]
			string += characters[character_index]
		string += '\n'
	string = string[:-len(fps_str)-1] + fps_str
	print(string)
