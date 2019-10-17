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
	// Mat::at �޼ҵ�� ������ �ȼ��� (y, x) ��ǥ�� �˰� ������ �̹����� �ȼ��� ������ �� �ִ� ���
	// ������ �Ź� �ȼ� ��ġ�� ����ϱ� ������ �ӵ��� ������.
	// 3ä�� �ȼ� ���ٽÿ��� at ������ Vec3b Ÿ���� �������ְ� ��ǥ ������ ���° ä���� �������� ���ȣ �ȿ� index �� �����ش�.
	// 1ä�� �ȼ� ���ٽÿ��� at ������ unchar Ÿ���� �������ش�.
	t1 = ((double)getTickCount() - t1) / getTickFrequency();

	double t2 = (double)getTickCount();

	for (int i = 0; i < 2000; i++)
		for (int y = 0; y < height; y++) {
			// y ��° row �� ���� �ּҸ� �����Ϳ� ������ ��
			uchar* pointer_input = img_color.ptr<uchar>(y);
			uchar* pointer_ouput = img_grayscale.ptr<uchar>(y);
			for (int x = 0; x < width; x++) {
				// row �����ͷκ��� (x * 3) ��° ������ �ִ� �ȼ��� �����´�.
				// 0, 1, 2 ������� blue, green, red ä�� ���� ������ �� �ִ� ������ �ϳ��� �ȼ��� �޸� �� b g r ������� ����Ǳ� ����
				uchar b = pointer_input[x * 3 + 0];
				uchar g = pointer_input[x * 3 + 1];
				uchar r = pointer_input[x * 3 + 2];

				pointer_ouput[x] = (r + g + b) / 3.0;
			}
		}
	// Mat::ptr
	// �����͸� ����ϴ� ������� at ����� ���� ���� �ӵ��� �����ش�.
	// ���� row�� �����͸� ������ Ÿ������ �̸� ����ؼ� �������� �����̴�.
	// OpenCV�� Mat ������ row�� �����͸� �ѹ� �������� ���� ����ϸ� �ȼ� ��ġ ����� ������ �ȴ�.
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
	// Mat Ŭ������ data �� ���� �����ϴ� ���

	t3 = ((double)getTickCount() - t3) / getTickFrequency();


	cout << "Mat::at time at =  " << t1 << " sec" << endl;
	cout << "Mat::ptr time at =  " << t2 << " sec" << endl;
	cout << "Mat::data time at =  " << t3 << " sec" << endl;


	imshow("color", img_color);
	imshow("grayscale", img_grayscale);

	waitKey(0);
	return 0;
}