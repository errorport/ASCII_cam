from cv2 import VideoCapture, resize, flip
import asciify

cam = VideoCapture(0)
cam.set(3, 600)
cam.set(4, 800)

while True:

	s, img = cam.read()

	if s:
		img = flip(resize(img, (80, 35)), 1)
		asciify.asciify(img)

cam.release()
