#include <opencv.hpp>
#include <iostream> 

using namespace cv;
using namespace std;

Mat h;
Point getHandCenter(const Mat& mask, double& radius);
int getFingerCount(const Mat& mask, Point center, double radius);

int count(Mat image) {
	Mat image_cvt, result;
	cvtColor(image, image_cvt, CV_BGR2YCrCb);
	inRange(image_cvt, Scalar(0, 133, 77), Scalar(255, 173, 127), image_cvt);

	imshow("image", image_cvt);
	//erode(image_cvt, image_cvt, Mat(), Point(-1, -1), 1);

	
	double radius;
	Point center = getHandCenter(image_cvt, radius);
	h = image;
	// cout << "�չٴ� �߽��� ��ǥ:" << center << ", ������:" << radius << endl;

	//�չٴ� �߽��� �׸���
	circle(image, center, 2, Scalar(0, 255, 0), -1);

	//�չٴ� ���� �׸���

	circle(image, center, int (radius) , Scalar(255, 0, 0), 2);
	imshow("Original Image With Hand Center", image);

	int num = getFingerCount(image_cvt, center, radius);
	return num;


}

int main() {
	Mat image, image_cvt,image_e,image_d,markers,result;

	//VideoCapture capture("rockpaper.mp4");
	VideoCapture capture(0);
	capture >> image;
	while (true) {
		if (!capture.read(image)) break;
		resize(image, image, Size(image.cols/2, image.rows/2));
		Mat left = image(Rect(0, 0, image.cols/2, image.rows));
		Mat right= image(Rect(image.cols/2, 0, image.cols / 2, image.rows));

	int num1 = count(left); //���� �÷��̾��� �հ�����
	//putText(left, to_string(num1), Point(100, 100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
	int num2 = count(right); //������ �÷��̾��� �հ��� �� 
	//putText(right, to_string(num2), Point(100, 100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);

	string string1 = "Win";
	string string2 = "Lose";
	string string3 = "Draw";
	string string4 = "scissor";
	string string5 = "rock";
	string string6 = "paper";

	//num1�� �����϶�
	if (num1 == 2) {
		putText(left, string4, Point(60, left.cols-20), FONT_HERSHEY_SIMPLEX, 1, Scalar(200,0, 200), 2);
		if (num2 >= 4 ) {
			putText(left, string1, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string2, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string6, Point(60, right.cols - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 0, 200), 2);
		}
		if (num2 == 0) {
			putText(left, string2, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string1, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string5, Point(60, right.cols - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 0, 200), 2);
		}
		if (num2 == 2) {
			putText(left, string3, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string3, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string4, Point(60, right.cols - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 0, 200), 2);
		}
	}
	//num1�� �ָ��϶�
	else if (num1 == 0) {
		putText(left, string5, Point(60, left.cols - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 0, 200), 2);
		if (num2 >= 4) {
			putText(left, string2, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string1, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string6, Point(60, right.cols - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 0, 200), 2);
		}
		if (num2 == 0) {
			putText(left, string3, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string3, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string5, Point(60, right.cols - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 0, 200), 2);
		}
		if (num2 == 2) {
			putText(left, string1, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string2, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string4, Point(60, right.cols - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 0, 200), 2);
		}
	}
	//num1�� ���ڱ��϶�
	else if (num1 >= 4) {
		putText(left, string6, Point(60, left.cols - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 0, 200), 2);
		if (num2 >= 4) {
			putText(left, string3, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string3, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string6, Point(60, right.cols - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 0, 200), 2);
		}
		if (num2 == 0) {
			putText(left, string1, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string2, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string5, Point(60, right.cols - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 0, 200), 2);
		}
		if (num2 == 2) {
			putText(left, string2, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string1, Point(60, 40), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 200, 200), 4);
			putText(right, string4, Point(60, right.cols - 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(200, 0, 200), 2);
		}
	}
	imshow("Original Image With FingerCount", image);
	waitKey(1);
	//waitKey(1000 / capture.get(CAP_PROP_FPS));
	}	
	return 0;
}

Point getHandCenter(const Mat& mask, double& radius) {//�����߽��� ã�� �Լ�
	Mat dst;
	distanceTransform(mask, dst, CV_DIST_L2, 5);  
												  //�Ÿ� ��ȯ ��Ŀ��� ���� ���� ū �ȼ��� ��ǥ��, ���� ���´�.
	int maxIdx[2];    //��ǥ ���� ���� �迭

	minMaxIdx(dst, NULL, &radius, NULL, maxIdx, mask);   //�ּҰ��� ������
	return Point(maxIdx[1], maxIdx[0]);

}
int getFingerCount(const Mat& mask, Point center, double radius) {
	//�հ��� ������ ���� ���� �� �׸���
	double scale = 2.0;
	Mat cImg(mask.size(), CV_8U, Scalar(0));
	circle(cImg, center, (radius*scale) , Scalar(255,0,0));
	imshow("cImg", cImg);

	Mat sub;
	sub = cImg - mask;
	imshow("sub",sub );
	vector<vector<Point>> contours;
	findContours(sub, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	int num = contours.size(); //countours ���� ����
	// cout << num << endl;
	return num - 1; //�ո�� ������ �� ���� 
	
}






