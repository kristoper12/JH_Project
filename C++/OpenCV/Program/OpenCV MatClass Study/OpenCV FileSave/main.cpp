#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;



int main()
{
	Mat img_color = imread("fullhd.jpg", IMREAD_COLOR);


	int height = img_color.rows;
	int width = img_color.cols;


	Mat img_grayscale(height, width, CV_8UC1);


	double t1 = (double)getTickCount();

	for (int i = 0; i < 2000; i++)
		for (int y = 0; y < height; y++) {


			for (int x = 0; x < width; x++) {

				uchar b = img_color.at<Vec3b>(y, x)[0];
				uchar g = img_color.at<Vec3b>(y, x)[1];
				uchar r = img_color.at<Vec3b>(y, x)[2];

				img_grayscale.at<uchar>(y, x) = (r + g + b) / 3.0;
			}
		}
	// Mat::at
	// Mat::at 메소드는 접근할 픽셀의 (y, x) 좌표만 알고 있으면 이미지의 픽셀에 접근할 수 있는 방법
	// 하지만 매번 픽셀 위치를 계산하기 때문에 속도가 느리다.
	// 3채널 픽셀 접근시에는 at 다음에 Vec3b 타입을 지정해주고 좌표 다음에 몇번째 채널을 가져올지 대괄호 안에 index 를 적어준다.
	// 1채널 픽셀 접근시에는 at 다음에 unchar 타입을 지정해준다.
	t1 = ((double)getTickCount() - t1) / getTickFrequency();

	double t2 = (double)getTickCount();

	for (int i = 0; i < 2000; i++)
		for (int y = 0; y < height; y++) {
			// y 번째 row 에 대한 주소를 포인터에 저장한 후
			uchar* pointer_input = img_color.ptr<uchar>(y);
			uchar* pointer_ouput = img_grayscale.ptr<uchar>(y);
			for (int x = 0; x < width; x++) {
				// row 포인터로부터 (x * 3) 번째 떨어져 있는 픽셀을 가져온다.
				// 0, 1, 2 순서대로 blue, green, red 채널 값을 가져올 수 있는 이유는 하나의 픽셀이 메모리 상에 b g r 순서대로 저장되기 때문
				uchar b = pointer_input[x * 3 + 0];
				uchar g = pointer_input[x * 3 + 1];
				uchar r = pointer_input[x * 3 + 2];

				pointer_ouput[x] = (r + g + b) / 3.0;
			}
		}
	// Mat::ptr
	// 포인터를 사용하는 방법으로 at 방법에 비해 빠른 속도를 보여준다.
	// 현재 row의 포인터를 지정한 타입으로 미리 계산해서 가져오기 때문이다.
	// OpenCV의 Mat 구조상 row의 포인터를 한번 가져오고 이후 사용하면 픽셀 위치 계산이 빠르게 된다.
	t2 = ((double)getTickCount() - t2) / getTickFrequency();

	double t3 = (double)getTickCount();

	uchar *data_input = img_color.data;

	for (int i = 0; i < 2000; i++)
		for (int y = 0; y < height; y++) {

			uchar *data_output = img_grayscale.data;


			for (int x = 0; x < width; x++) {

				uchar b = data_input[y * width * 3 + x * 3];
				uchar g = data_input[y * width * 3 + x * 3 + 1];
				uchar r = data_input[y * width * 3 + x * 3 + 2];


				data_output[width * y + x] = (r + g + b) / 3.0;
			}
		}
	// Mat::data
	// Mat 클래스의 data 에 직접 접근하는 방법

	t3 = ((double)getTickCount() - t3) / getTickFrequency();


	cout << "Mat::at time at =  " << t1 << " sec" << endl;
	cout << "Mat::ptr time at =  " << t2 << " sec" << endl;
	cout << "Mat::data time at =  " << t3 << " sec" << endl;


	imshow("color", img_color);
	imshow("grayscale", img_grayscale);

	waitKey(0);
	return 0;
}