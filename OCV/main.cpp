#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include <string>

using namespace std;

#define REL_MIN_LEN 150

#define REL_MAX_LEN 750

#define CON_MAX 35

#define CON_MIN 5

#define MIN_NUM_CON 3


IplImage* img_resize(IplImage* src_img, int new_width, int new_height)
{
	IplImage* des_img;
	des_img = cvCreateImage(cvSize(new_width, new_height), src_img->depth, src_img->nChannels);
	cvResize(src_img, des_img, CV_INTER_LINEAR);
	return des_img;
}

// ��������� �������� �� �������� �� �������� 
bool testMatch(IplImage* original)
{
	assert(original != 0);

	printf("[i] test cvMatchShapes()\n");

	IplImage *src = 0, *dst = 0;

	src = cvCloneImage(original);

	src = img_resize(src, 500, 280);

	cvSetImageROI(src, cvRect(216, 170, 140, 110));

	//src = cvCreateImage(cvSize(500, 280), src->depth, src->nChannels);
	//cvResize(original, src, 0);

	IplImage* binI = cvCreateImage(cvGetSize(src), 8, 1);

	// ������ ������� ��������
	IplImage* rgb = cvCreateImage(cvGetSize(src), 8, 3);
	cvConvertImage(src, rgb, CV_GRAY2BGR);
	
	// �������� ������� ����������� � �������
	cvCanny(src, binI, 50, 200);
	
	// ����������
	//cvNamedWindow("cannyI", 1);
	//cvShowImage("cannyI", binI);

	// ��� �������� ��������
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contoursI = 0;

	// ������� ������� �����������
	int contoursCont = cvFindContours(binI, storage, &contoursI, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

	// ��� ������� ��������
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0);
	char buf[128];
	int counter = 0;

	CvSeq* seqI = 0;
	double perimI = 0;
	int relCounter = 0;
	int conCounter = 0;
	bool isRel = true;
	// �������� ������� �����������
	if (contoursI != 0) {
		for (CvSeq* seq0 = contoursI; seq0 != 0; seq0 = seq0->h_next) {
			conCounter++;
			
			// ������� ��� �����
			//CvPoint2D32f point; float rad;
			//cvMinEnclosingCircle(seq0,&point,&rad); // ������� ���������� ���������� ������
			//cvPutText(rgb, itoa(++counter, buf, 10), cvPointFrom32f(point), &font, CV_RGB(0,255,0));

			
			double perim = cvContourPerimeter(seq0);
			if (perim>perimI) {
				perimI = perim;
				seqI = seq0;
			}

			int col = 255;
			if (perim > REL_MIN_LEN && perim < REL_MAX_LEN) {
				col = 100;
				relCounter++;
			}

			if (perim > REL_MAX_LEN) {
				isRel = false;
			}
			// ������ ������
			cvDrawContours(rgb, seq0, CV_RGB(col, 216, 0), CV_RGB(0, 0, 250), 0, 1, 8);
			
			//cout << perim << "\n";
		}
	}

	if (conCounter > CON_MAX || conCounter < CON_MIN) {
		isRel = false;
	}

	if (relCounter < MIN_NUM_CON) {
		isRel = false;
	}


	if (!isRel) {
		cout << "Not rel\n";
	}
	else {
		cout << "THIS IS REL\n";

		
	}

	//cout << "PerimI=" << perimI << "\n";
	//cout << "Rel num=" << relCounter << "\n";




	// ����������
	//cvNamedWindow("cont", 1);
	//cvShowImage("cont", rgb);

	cvConvertImage(src, rgb, CV_GRAY2BGR);


	/*CvSeq* seqT = 0;
	double perimT = 0;

	if (contoursT != 0) {
		// ������� ����� ������� ������ 
		for (CvSeq* seq0 = contoursT; seq0 != 0; seq0 = seq0->h_next) {
			double perim = cvContourPerimeter(seq0);
			if (perim>perimT) {
				perimT = perim;
				seqT = seq0;
			}
			// ������
			cvDrawContours(rgbT, seq0, CV_RGB(255, 216, 0), CV_RGB(0, 0, 250), 0, 1, 8); // ������ ������
		}
	}*/
	// ������� ������ �������
	

	/*CvSeq* seqM = 0;
	double matchM = 1000;
	// ������� ������� ����������� 
	counter = 0;
	if (contoursI != 0) {
		// ����� ������� ���������� �������� �� �� �������� 
		for (CvSeq* seq0 = contoursI; seq0 != 0; seq0 = seq0->h_next) {
			double match0 = cvMatchShapes(seq0, seqT, CV_CONTOURS_MATCH_I3);
			if (match0<matchM) {
				matchM = match0;
				seqM = seq0;
			}
			printf("[i] %d match: %.2f\n", ++counter, match0);
		}
	}
	// ������ ��������� ������
	cvDrawContours(rgb, seqM, CV_RGB(52, 201, 36), CV_RGB(36, 201, 197), 0, 2, 8); // ������ ������
	*/
	//cvNamedWindow("find", 1);
	//cvShowImage("find", rgb);

	// ��� ������� �������
	//cvWaitKey(0);

	// ����������� �������
	cvReleaseMemStorage(&storage);

	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseImage(&rgb);
	cvReleaseImage(&binI);
	return isRel;

	// ������� ����
	//cvDestroyAllWindows();
}


int main()
{
	for (int i = 0; i < 124; i++) {
		IplImage *original = 0;

		// ��� �������� ������� ������ ����������
		char my_str[4];
		char buffer[256]; 
		_itoa_s(i, my_str, 10);

		sprintf_s(buffer, "train%s.jpg", my_str);
		cout << buffer<< endl; 
		char* filename = buffer;
		// �������� ��������
		original = cvLoadImage(filename, 0);


		printf("[i] image: %s\n", filename);
		assert(original != 0);

		original = img_resize(original, 500, 280);
		// ������� �����������
		//cvNamedWindow("original", 1);
		//cvShowImage("original", original);

		testMatch(original);
		if (testMatch(original)) {
			cv::Mat img;
			img=cv::imread(filename);
			char path[256]; 
			sprintf_s(path, "Good/Good_one%s.jpg", my_str);
			cv::imwrite(path, img);
		}

		// ����������� �������
		//cvReleaseImage(&original);
		// ������� ����
		//cvDestroyAllWindows();
	}
	system("pause");
	return 0;
}
