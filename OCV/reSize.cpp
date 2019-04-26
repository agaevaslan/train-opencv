//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
//#include <stdlib.h>
//#include <stdio.h>
//using namespace std;
//
//
//// �������� 
//IplImage* image = 0;
//IplImage* dst[4];
//
//int main(int argc, char* argv[])
//{
//	// ��� �������� ������� ������ ����������
//	const char* filename = "Image.jpg";
//	// �������� ��������
//	image = cvLoadImage(filename, 1);
//
//	int i = 0;
//
//	printf("[i] image: %s\n", filename);
//	assert(image != 0);
//
//	// �������� ����������� �������� (������ ��� ������������)
//	for (i = 0; i<4; i++) {
//		dst[i] = cvCreateImage(cvSize((image->width / 3), (image->height / 3)), image->depth, image->nChannels);
//		cvResize(image, dst[i], i);
//	}
//
//	// ���� ��� ����������� ��������
//	cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
//	cvShowImage("original", image);
//
//	// ���������� ���������
//	char buf[128];
//	for (i = 0; i<4; i++) {
//		std::string s = std::to_string(i);
//		cvNamedWindow(s.c_str(), CV_WINDOW_AUTOSIZE);
//		cvShowImage(s.c_str(), dst[i]);
//	}
//
//	// ��� ������� �������
//	cvWaitKey(0);
//
//	// ����������� �������
//	cvReleaseImage(&image);
//	for (i = 0; i<4; i++) {
//		cvReleaseImage(&dst[i]);
//	}
//
//	// ������� ����
//	cvDestroyAllWindows();
//	return 0;
//}