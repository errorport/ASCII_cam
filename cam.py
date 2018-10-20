from cv2 import VideoCapture, resize
import asciify

cam = VideoCapture(0)
cam.set(3, 120)
cam.set(4, 160)

while True:

    s, img = cam.read()

    if s:
        img = resize(img, (160, 58))
        asciify.asciify(img)

cam.release()
