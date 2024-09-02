#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <time.h>

#define FRAME_DATA_FILE "./assets/frame_data_sixels"
#define FRAME_SIZE_FILE "./assets/frame_sizes"
#define FRAME_COUNT 6572
#define FRAME_BUFFER_SIZE 0xFFFF
#define DURATION 219.08

int main(int argc, char **argv) {
    
    FILE *f_frameData = fopen(FRAME_DATA_FILE, "r");
    FILE *f_frameSize = fopen(FRAME_SIZE_FILE, "r");
    assert(f_frameData != NULL && f_frameSize != NULL);
    
    int *frameSizes = malloc(sizeof(int) * FRAME_COUNT);
    
    int i = 0;
    char buffer [0xFF], format [0xFF];
    snprintf(format, sizeof(format), "%%%ds", sizeof(buffer) - 1);
    for (; fscanf(f_frameSize, format, buffer) && i < FRAME_COUNT; ++i) {
        frameSizes[i] = atoi(buffer);
    }
    
    printf("\033[?25l"); // Hide the cursor.
    
    int currentFrameNum = -1, nextFrameNum;
    size_t pos = 0;
    char *frame = malloc(FRAME_BUFFER_SIZE);
    while ((nextFrameNum = (float)clock() 
        / CLOCKS_PER_SEC / DURATION * FRAME_COUNT) < FRAME_COUNT
    ) {
        
        // DEBUG PURPOSES
        // getchar();
        // nextFrameNum = currentFrameNum + 1;
        
        if (nextFrameNum == currentFrameNum) {
            sched_yield();
            continue;
        }
        for (; currentFrameNum < nextFrameNum; ++currentFrameNum) {
            pos += frameSizes[currentFrameNum];
        }
        int frameSize = frameSizes[currentFrameNum];
        fseek(f_frameData, pos, SEEK_SET);
        fread(frame, 1, frameSize, f_frameData);
        frame[frameSize] = '\0';
        printf("\033[H%s", frame);
        fflush(stdout);
    }
    
    printf("\033[?25h"); // Show the cursor.
    
    free(frameSizes);
    free(frame);
    fclose(f_frameData);
    fclose(f_frameSize);
    
    return 0;
}
