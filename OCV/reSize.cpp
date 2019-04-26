//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
//#include <stdlib.h>
//#include <stdio.h>
//using namespace std;
//
//
//// исходная 
//IplImage* image = 0;
//IplImage* dst[4];
//
//int main(int argc, char* argv[])
//{
//	// имя картинки задаётся первым параметром
//	const char* filename = "Image.jpg";
//	// получаем картинку
//	image = cvLoadImage(filename, 1);
//
//	int i = 0;
//
//	printf("[i] image: %s\n", filename);
//	assert(image != 0);
//
//	// создание уменьшенных картинок (разный тип интерполяции)
//	for (i = 0; i<4; i++) {
//		dst[i] = cvCreateImage(cvSize((image->width / 3), (image->height / 3)), image->depth, image->nChannels);
//		cvResize(image, dst[i], i);
//	}
//
//	// окно для отображения картинки
//	cvNamedWindow("original", CV_WINDOW_AUTOSIZE);
//	cvShowImage("original", image);
//
//	// показываем результат
//	char buf[128];
//	for (i = 0; i<4; i++) {
//		std::string s = std::to_string(i);
//		cvNamedWindow(s.c_str(), CV_WINDOW_AUTOSIZE);
//		cvShowImage(s.c_str(), dst[i]);
//	}
//
//	// ждём нажатия клавиши
//	cvWaitKey(0);
//
//	// освобождаем ресурсы
//	cvReleaseImage(&image);
//	for (i = 0; i<4; i++) {
//		cvReleaseImage(&dst[i]);
//	}
//
//	// удаляем окна
//	cvDestroyAllWindows();
//	return 0;
//}