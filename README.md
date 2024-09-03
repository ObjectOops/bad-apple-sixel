# bad-apple-sixel
[Bad Apple!!](https://en.wikipedia.org/wiki/Bad_Apple!!#Use_as_a_graphical_and_audio_test) in high definition on terminals that support the sixel protocol (i.e. in VSCode &amp; Xterm).

![image](https://github.com/user-attachments/assets/0fbb295b-3736-44f9-a497-835e0fd2127f)

[Click here to watch the video.](https://objectoops.github.io/bad-apple-sixel/)

___

## Notes
- All sixels have been combined into a [single file](./assets/frame_data_sixels) using `generator.sh`.
- Some video quality needed to be sacrificed to fit below the 100 MB GitHub file size limit without LFS.
- The duration of the video has been manually decreased by about 2.08 seconds, and begins playing about half a second late in order to match up with the audio being played with ffplay. *It works on my machine*.

## Requirements
- A C compiler (GCC, Clang - requires `unistd.h`).
  - `make` or `gcc -O3 main.c -o main`
- A terminal that supports sixels (i.e. VSCode integrated terminal).
- FFmpeg (ffplay for audio).

Read more about sixels [here](https://code.visualstudio.com/updates/v1_80#_terminal).
