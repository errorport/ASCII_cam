from cv2 import VideoCapture, resize, flip
import asciify
import curses

def main(stdscr):
	stdscr.clear()

	cam = VideoCapture(0)
	cam.set(3, 600)
	cam.set(4, 800)

	while True:

		s, img = cam.read()

		if s:
			rows, cols = stdscr.getmaxyx()
			img = flip(resize(img, (cols, rows)), 1)
			asciify.asciify(img)
			stdscr.refresh()

	cam.release()

if __name__ == "__main__":
	curses.wrapper(main)

