#!/bin/bash

pip install --upgrade youtube-dl

# Temporary workaround.
pip install --upgrade --force-reinstall "git+https://github.com/ytdl-org/youtube-dl.git"

sudo apt update
sudo apt install -y ffmpeg libsixel-bin

mkdir assets
cd assets

VIDEO="https://www.youtube.com/watch?v=FtutLA63Cp8"
FILE_NAME="bad-apple.mp4"
OUTPUT_DIGITS="4"
OUTPUT_FPS="30"
OUTPUT_DIMENSIONS="480x360"

youtube-dl -f mp4 -o $FILE_NAME $VIDEO

mkdir frames
cd frames

ffmpeg -r $OUTPUT_FPS -i ../$FILE_NAME -s $OUTPUT_DIMENSIONS -vf format=gray "frame%0${OUTPUT_DIGITS}d.png"

cd ..

ffmpeg -i $FILE_NAME -vn audio.mp3

rm $FILE_NAME

printf "" > frame_data_sixels
printf "" > frame_sizes
for i in {1..6572}; do
    IMG=$(img2sixel -E size -b gray4 $(printf "./frames/frame%04d.png" $i))
    SIZE=${#IMG}
    printf '%s' $IMG >> frame_data_sixels
    printf "${SIZE} " >> frame_sizes
done

rm -r frames
