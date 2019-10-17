#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[])
{
	// Create a VideoCapture object to read from video file
	VideoWriter writer;
	VideoCapture cap("ray.mp4");
	Size size = Size((int)cap.get(CAP_PROP_FRAME_WIDTH), (int)cap.get(CAP_PROP_FRAME_HEIGHT));
	double fps = 30.0;
	//check if the file was opened properly
	if (!cap.isOpened())
	{
		cout << "Capture could not be opened succesfully" << endl;
		return -1;
	}
	namedWindow("video");

	writer.open("gray ray.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size, true);
	// Play the video in a loop till it ends
	while (char(waitKey(30)) != 'q' && cap.isOpened()) {
		Mat frame;
		bool bSuccess = cap.read(frame);

		if (!bSuccess) {
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat grayscale;

		cvtColor(frame, grayscale, COLOR_BGR2GRAY);
		
		//Sobel(frame, frame, 5, 1, 1, 3);

		//Check if the video is over
		if (frame.empty())
		{
			cout << "Video over" << endl;
			break;
		}
		imshow("Video", grayscale);
		writer.write(frame);
	}

	return 0;
}