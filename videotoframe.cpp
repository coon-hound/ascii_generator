#include <stdio.h>
#include <sys/stat.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
	mkdir("frames", 0777);

    if (argc != 2) {
        printf("Usage: %s <video_file>\n", argv[0]);
        return -1;
    }

    VideoCapture cap(argv[1]);
    if (!cap.isOpened()) {
        printf("Error opening video file: %s\n", argv[1]);
        return -1;
    }

    int frame_count = 0;
    Mat frame;
    while (cap.read(frame)) {
        char filename[100];
        sprintf(filename, "frames/frame_%d.jpg", frame_count++);
        imwrite(filename, frame);
    }

    cap.release();
    return 0;
}


