#include <opencv2/core.hpp> 
// 기본적인 자료구조와 함수들이 포함
#include <opencv2/imgcodecs.hpp> 
// 이미지 파일을 읽어오는 함수와 이미지 파일을 저장하는 함수를 포함
#include <opencv2/highgui.hpp> 
// 인터페이스를 구현해 놓은 모듈, 사용자의 입력을 받기 위해 대기하는 함수와 화면에 이미지를 보여주기 위한 함수가 포함되어 있다.
#include <opencv2/imgproc.hpp>
// Canny 함수를 사용하기 위한 모듈

//	#include <opencv2/opencv.hpp> 위 3개를 하나로 합쳐서 선언
#include <iostream>	// 입출력을 위한 C++ 헤더 파일


using namespace cv;
using namespace std;


int main()
{
	Mat image;
	image = imread("OhMyGirl.jpeg", IMREAD_GRAYSCALE);
	// MAT cv::imread(const String & filename, int flags = IMREAD_COLOR)
	// IMREAD_UNCHANGED		알파 채널을 포함시킨 컬러 이미지 반환
	// IMREAD_COLOR			알파 채널이 없는 컬러 이미지를 반환
	// IMREAD_GRAYSCALE		그레이 스케일 이미지로 변환하여 반환
	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	imshow("Original", image);
	Canny(image, image, 50, 150);
	// 엣지를 검출하는 함수
	// 엣지를 검출하는 함수를 호출할 시 image 는 IMREAD_GRAYSCALE 옵션으로 읽어와야 한다.

	//namedWindow("Original", WINDOW_NORMAL);
	//namedWindow("Canny", WINDOW_NORMAL);
	// 이미지를 보여줄 윈도우 생성
	// 1번째 인자는 윈도우의 식별자 이면서 윈도우 타이틀에 보여질 메세지
	// 2번째 인자는 WINDOW_AUTOSIZE는 이미지 크기에 맞춰 윈도우 크기가 정해짐 사용자가 윈도우 크기를 조절할 수 없음
	// WINDOW_NORMAL 은 이미지가 큰 경우 해상도 크기에 맞춰 윈도우 크기가 정정 됨. 사용자가 윈도우 크기를 조절할 수 있다. 
	// WND_PROP_FULLSCREEN 을 사용한 후
	// setWindowProperty("Original", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
	// 를 사용하면 화면이 모니터에 꽉 찬다.
	imshow("Canny", image);
	// Original 왼도우에 image 에 저장되있는 이미지를 보여준다.

	waitKey(0);
	// 키보드 입력이 있을 때 까지 대기

	return 0;
}