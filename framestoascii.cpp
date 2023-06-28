#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <unistd.h>

using namespace cv;

char brightness_scale[] = " .:-=+*#%@";

double toGreyscale(double red, double green, double blue)
{
	return 0.299 * red + 0.587 * green + 0.114 * blue;
}

char greyscaleToChar(double greyscale_value)
{
	int arr_size = sizeof(brightness_scale) - 1;
	double threshold = (255.f / (arr_size / sizeof(char)));

	greyscale_value = 254;

	for(int i = 0; i < arr_size - 1; i++){
		if(greyscale_value >= i * threshold && greyscale_value < (i+1) * threshold){
//			printf("greyscale >= %f && greyscale < %f\n", i * threshold, (i+1) * threshold);
//			printf("greyscale = %f i = %d\n", greyscale_value, i);
			return brightness_scale[i];
		}
	}
//	printf("shit\n");
	return brightness_scale[arr_size - 1];
}


int main()
{
	String frame_path = "frames/frame_";

	Mat img = imread("frames/frame_1.jpg", IMREAD_COLOR); // load image in color format 
	
	//get resolution of the first image 
	Size resolution = img.size();

	printf("resolution = %d x %d\n", resolution.width, resolution.height);


	int width = resolution.width;
	int height = resolution.height;

	int index = 0;

	printf("\x1b[2J\x1b[H");

	while(1)
	{
		index = 68;
		printf("frame = %d\n", index);
		frame_path = "frames/frame_";
		frame_path.append(std::to_string(index));
		frame_path.append(".jpg");
//		printf("frame_path = %s\n", frame_path.c_str());
		Mat og_img = imread(frame_path, IMREAD_COLOR); // load image in color format 

		Size new_size(og_img.cols/10, og_img.rows/10);

		Mat img;
		
		resize(og_img, img, new_size);
		imshow("Resized Image", img);
		waitKey(0);

		//check if image isn't empty 
		if(img.empty()){
			break;
		}

		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				Vec3b pixel = img.at<Vec3b>(Point(j, i));

				double greyscale_value = toGreyscale(pixel[2], pixel[1], pixel[0]);

				if(greyscale_value == 0)
					break;

				printf("%c", greyscaleToChar(greyscale_value));
			}
			printf("\n");
		}


		index++;

		break;
		usleep(250*1000);

	}
	printf("all good didn't crash\n");

}
