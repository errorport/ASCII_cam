from cv2 import VideoCapture, resize
import asciify

cam = VideoCapture(0)
cam.set(3, 180)
cam.set(4, 240)

while True:

    s, img = cam.read()

    if s:
        img = resize(img, (240, 87))
        asciify.asciify(img)

cam.release()
