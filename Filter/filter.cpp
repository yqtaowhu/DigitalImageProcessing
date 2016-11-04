#include "opencv2/opencv.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/highgui/highgui.hpp"
#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
#include<iomanip>
using namespace cv;
using namespace std;
//添加椒盐噪声
void salt(Mat& image, int n) {
	for (int k = 0; k<n; k++) {
		int i = rand() % image.cols;	
		int j = rand() % image.rows;

		if (image.channels() == 1) {   //判断是一个通道
			image.at<uchar>(j, i) = 255;
		}
		else {
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}
}
//中值滤波
void medeanFilter(Mat& src, int win_size) {
	int rows = src.rows, cols = src.cols;
	int start = win_size/2;
	for (int m = start; m <rows - start; m++) {
		for (int n = start; n < cols - start; n++) {
			vector<uchar> model;
			for (int i = -start + m; i <= start + m; i++) {
				for (int j = -start + n; j <= start + n; j++) {
					//cout << int(src.at<uchar>(i, j)) << endl;
					model.push_back(src.at<uchar>(i, j));
				}
			}
			sort(model.begin(), model.end());     //采用快速排序进行
			src.at<uchar>(m, n) = model[win_size*win_size/2];
		}
	}
}
//均值滤波
void meanFilter(Mat& src, int win_size) {
	int rows = src.rows, cols = src.cols;
	int start = win_size / 2;
	for (int m = start; m <rows - start; m++) {
		for (int n = start; n < cols - start; n++) {
			int sum = 0;
			for (int i = -start + m; i <= start + m; i++) {
				for (int j = -start + n; j <= start + n; j++) {
					sum += src.at<uchar>(i, j);
				}
			}
			src.at<uchar>(m, n) = uchar(sum / win_size / win_size);
		}
	}
}

//生成高斯模板
const float pi = 3.1415;
vector<vector<float>> gaussTemplate(float sigma, int size) {
	int xcore = size / 2, ycore = size / 2;
	vector<vector<float>> res;
	float base = 1.0 / 2 / pi / sigma / sigma;
	for (int x = 0; x < size; x++) {
		vector<float>v;
		for (int y = 0; y < size; y++) {
			float t1 = (pow(x - xcore, 2) + pow(y - ycore, 2)) / 2.0 / sigma / sigma;
			float temp = base*exp(-t1);
			v.push_back(temp);
		}
		res.push_back(v);
	}
	return res;
}

//高斯滤波
void gaussFilter(Mat& src,int size,float sigma) {
	vector<vector<float>> gaussTem = gaussTemplate(sigma,size);
	int rows = src.rows, cols = src.cols;
	int start = size / 2;
	for (int m = start; m <rows - start; m++) {
		for (int n = start; n < cols - start; n++) {
			float sum = 0;
			for (int i = -start + m; i <= start + m; i++) {
				for (int j = -start + n; j <= start + n; j++) {
					//cout << gaussTem[i - m + start][j - n + start] << endl;
					sum += src.at<uchar>(i, j)*gaussTem[i-m+start][j-n+start];  //重点理解！！！
				}
			}
			src.at<uchar>(m, n) = uchar(sum);
		}
	}
}
int main(){
	Mat src = imread("lena.jpg");
	cvtColor(src, src,CV_BGR2GRAY);
	//中值滤波
	Mat dst;
	src.convertTo(dst, CV_8UC1);
	salt(dst, 3000);
	namedWindow("origin");
	imshow("origin", dst);
	medeanFilter(dst,3);
	namedWindow("median filter");
	imshow("median filter", dst);
	//均值滤波
	Mat dst1;
	src.convertTo(dst1, CV_8UC1);
	salt(dst1, 3000);
	meanFilter(dst1, 3);
	namedWindow("mean filter");
	imshow("mean filter", dst1);
	float sigma = 0.84089642; int size = 7;
	vector<vector<float>> gaussTem = gaussTemplate(0.84089642, 7);
	for (auto num : gaussTem) {
		for (auto c : num)
			cout <<setprecision(8)<<std::fixed << c<< setw(11);
		cout << endl;
		cout << endl;
	}
	Mat dst2;
	src.convertTo(dst2, CV_8UC1);
	salt(dst2, 3000);
	gaussFilter(dst2, 3, 1);
	namedWindow("gause");
	imshow("gause", dst2);
	Mat dst3;
	src.convertTo(dst3, CV_8UC1);
	salt(dst3, 3000);
	gaussFilter(dst3, 3, 0.6);
	namedWindow("gause2");
	imshow("gause2", dst3);
	waitKey();
	return 0;
}