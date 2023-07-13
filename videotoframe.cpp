#include <stdio.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);

    double t_cols = w.ws_col;
    double t_rows = w.ws_row;

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

    Size frame_res = frame.size();

    while (cap.read(frame)) {
        printf("frame.cols = %d, frame.rows = %d\n", frame.cols, frame.rows);
        double r = frame.rows;
        printf("r = %d\n", r);
        printf("t_cols = %d, t_rows = %d\n", t_cols, t_rows);
        double ratio = t_rows / r;
        printf("ratio = %f\n", ratio);

        Size new_size(frame.cols * ratio * 2, frame.rows * ratio);
        // new_size(frame.cols/10, frame.rows/20);
		Mat img;
		
		resize(frame, img, new_size);

		Size resolution = img.size();

        char filename[100];
        sprintf(filename, "frames/frame_%d.jpg", frame_count++);
        imwrite(filename, img);
    }

    cap.release();
    return 0;
}


