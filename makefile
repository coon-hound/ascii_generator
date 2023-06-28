all:
	g++ videotoframe.cpp -I/opt/homebrew/include/opencv4 -std=c++17 -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lopencv_imgcodecs -L/opt/homebrew/lib -o videotoframe
	g++ framestoascii.cpp -I/opt/homebrew/include/opencv4 -std=c++17 -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lopencv_imgcodecs -L/opt/homebrew/lib -o framestoascii

clean:
	rm -rf frames videotoframe framestoascii a.out

