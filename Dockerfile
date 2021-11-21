FROM debian

RUN apt-get update
RUN apt-get upgrade -y || true
RUN apt-get install -y \
	cpp \
	g++ \
	make \
	cmake \
	binutils \
	ffmpeg \
	libopencv-dev
RUN apt-get install -y \
	libjack-dev
