#!/bin/bash

docker run -it \
	--mount type=bind,source="$(pwd)", target=/project
	exo_video_toolset_builder:latest
	./build.sh
