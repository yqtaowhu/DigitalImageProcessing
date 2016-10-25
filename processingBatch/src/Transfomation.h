#pragma once
#include <iostream>
using namespace std;
using namespace cv;
static Mat org, dst, tmp, img;
class Transfomation {
private:
	int numbers;
	char* input,*output;
	
public:
	Transfomation(int num, char* in, char* out);
	void AffTrans (cv::Mat& src);							//����任
	void Mirror(cv::Mat& image);
	void Salt(int n);
    static void on_mouse(int event, int x, int y, int flags, void *ustc);          //������
	char *Clip();
	void Resize(int m,int n);

};

Transfomation::Transfomation(int num, char* in, char* out) {
	numbers = num;
	input = new char[strlen(in)+1];
	strcpy(input, in);
	output = new char[strlen(out) + 1];
	strcpy(output, out);
}

//��ӽ�������
void Transfomation::Salt(int n) {
	char filename[1001];
	char filename2[1001];
	for (int i = 1; i <= numbers; i++) {
		sprintf(filename, "%s\\%d.jpg", input, i);		// ��ͼƬ����������������1.jpg 2.jpg�ȣ������ļ�����
		org = imread(filename);				//filename��ʵ����һ��·��
		org.copyTo(img);
		org.copyTo(dst);
	    //imshow("img", org);//��ʾͼ��ԭͼ
		//�ӽ�������
		for (int k = 0; k<n; k++) {
			int i = rand() % img.cols;
			int j = rand() % img.rows;

			if (img.channels() == 1) {
				img.at<uchar>(j, i) = 255;
			}
			else {
				img.at<Vec3b>(j, i)[0] = 255;
				img.at<Vec3b>(j, i)[1] = 255;
				img.at<Vec3b>(j, i)[2] = 255;
			}
		}
		sprintf(filename2, "%s\\%d.jpg", output, i);
		imwrite(filename2, img);
		//imshow("img", img);//��ʾͼ��ԭͼ
	}
}

//�ı�ͼ��ߴ�
void Transfomation::Resize(int m,int n) {
	char filename[256];  
	char filename2[256];   
	for(int i=1;i<=numbers;i++) {
		sprintf(filename,"%s\\%d.jpg",input,i);
		img =imread(filename);
	//	imshow("img", img);
		Mat res;
		resize(img,res,Size(m,n)); 
		sprintf(filename2 ,"%s\\%d_resize.jpg" ,output,i);  
		imwrite(filename2, res);
	}
}
////void Transfomation::AffTrans()
//void Transfomation::AffTrans(cv::Mat& src)
//{
//	char* source_window = "Source image";
//	char* warp_window = "Warp";
//	char* warp_rotate_window = "Warp + Rotate";
//	Point2f srcTri[3];
//	Point2f dstTri[3];
//
//	Mat rot_mat( 2, 3, CV_32FC1 );
//	Mat warp_mat( 2, 3, CV_32FC1 );
//	//Mat src, warp_dst, warp_rotate_dst;
//	Mat  warp_dst, warp_rotate_dst;
//	/// ����Դͼ��
//	//src = imread( "dst.jpg", 1 );
//
//	/// ����Ŀ��ͼ��Ĵ�С��������Դͼ��һ��
//	warp_dst = Mat::zeros( src.rows, src.cols, src.type() );
//
//	/// ����Դͼ���Ŀ��ͼ���ϵ�������Լ������任
//	srcTri[0] = Point2f( 0,0 );
//	srcTri[1] = Point2f( src.cols - 1, 0 );
//	srcTri[2] = Point2f( 0, src.rows - 1 );
//
//	dstTri[0] = Point2f( src.cols*0.0, src.rows*0.33 );
//	dstTri[1] = Point2f( src.cols*0.85, src.rows*0.25 );
//	dstTri[2] = Point2f( src.cols*0.15, src.rows*0.7 );
//
//	/// ��÷���任
//	warp_mat = getAffineTransform( srcTri, dstTri );
//
//	/// ��Դͼ��Ӧ��������õķ���任
//	warpAffine( src, warp_dst, warp_mat, warp_dst.size() );
//
//	/** ��ͼ��Ť��������ת */
//
//	/// ������ͼ���е�˳ʱ����ת50����������Ϊ0.6����ת����
//	Point center = Point( warp_dst.cols/2, warp_dst.rows/2 );
//	double angle = -50.0;
//	double scale = 0.6;
//
//	/// ͨ���������תϸ����Ϣ�����ת����
//	rot_mat = getRotationMatrix2D( center, angle, scale );
//
//	/// ��ת��Ť��ͼ��
//	warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );
//	/// ��ʾ���
//	//namedWindow( source_window, CV_WINDOW_AUTOSIZE );
//	//imshow( source_window, src );
//	//namedWindow( warp_window, CV_WINDOW_AUTOSIZE );
//	//imshow( warp_window, warp_dst );
//	imwrite("bianhuan1.jpg",warp_dst);
//	//namedWindow( warp_rotate_window, CV_WINDOW_AUTOSIZE );
//	//imshow( warp_rotate_window, warp_rotate_dst );
//	imwrite("bianhuan2.jpg", warp_rotate_dst);
//	/// �ȴ��û������ⰴ���˳�����
//	waitKey(0);
//}
//void Transfomation::Mirror(cv::Mat& image)
//
//{
//	//Mat img=imread("dst.jpg",1);
//	unsigned char *pimg=new unsigned char[image.rows*image.cols*3],*pimg1=new unsigned char[image.rows*image.cols*3];
//	pimg=image.data;
//	for (int i=0;i<image.rows;i++)
//	{
//		for (int j=0;j<image.cols;j++)
//		{
//			pimg1[(i*image.cols+j)*3+0]=pimg[(i*image.cols+image.cols-j)*3+0];
//			pimg1[(i*image.cols+j)*3+1]=pimg[(i*image.cols+image.cols-j)*3+1];
//			pimg1[(i*image.cols+j)*3+2]=pimg[(i*image.cols+image.cols-j)*3+2];
//		}
//	}
//
//	Mat image1;
//	image1.create(image.rows,image.cols,CV_8UC3);
//	image1.data=pimg1;
//	imwrite("bianhuan3.jpg",image1);
//}

char* Transfomation::Clip(){
	char filename[1001];
	char filename2[1001];
	for (int i = 1; i <= numbers; i++) {
		sprintf(filename, "%s\\%d.jpg", input, i);		// ��ͼƬ����������������1.jpg 2.jpg�ȣ������ļ�����
		org = imread(filename);				//filename��ʵ����һ��·��
		org.copyTo(img);
		org.copyTo(dst);
		/*�������仰�Ƕ�ͼ����н�ͼ����*/
		namedWindow("img", 0);
		//cvResizeWindow("img",500,500);
		setMouseCallback("img", on_mouse, 0);//���ú������н�ͼ����,�Ƕ�img�����е�ͼ����д���
		imshow("img", img);//��ʾͼ��ԭͼ
		waitKey(0);
		namedWindow("dst", 0);
		imshow("dst", dst);
		sprintf(filename2, "%s\\%d.jpg", output, i);
		imwrite(filename2, dst);
	}
	return 0;
}

//�����Ӧ����
void Transfomation::on_mouse(int event, int x, int y, int flags, void *ustc)//event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���  
{
	static Point pre_pt = (-1, -1);//��ʼ����  
	static Point cur_pt = (-1, -1);//ʵʱ����  
	char temp[16];
	if (event == CV_EVENT_LBUTTONDOWN)//������£���ȡ��ʼ���꣬����ͼ���ϸõ㴦��Բ  
	{
		org.copyTo(img);//��ԭʼͼƬ���Ƶ�img��  
		sprintf(temp, "(%d,%d)", x, y);
		pre_pt = Point(x, y);
		putText(img, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255), 1, 8);//�ڴ�������ʾ����  
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//��Բ  
		imshow("img", img);
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//���û�а��µ����������ƶ��Ĵ�����  
	{
		img.copyTo(tmp);//��img���Ƶ���ʱͼ��tmp�ϣ�������ʾʵʱ����  
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = Point(x, y);
		putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));//ֻ��ʵʱ��ʾ����ƶ�������  
		imshow("img", tmp);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))      //�������ʱ������ƶ�������ͼ���ϻ�����  
	{
		img.copyTo(tmp);
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = Point(x, y);
		putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		rectangle(tmp, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);//����ʱͼ����ʵʱ��ʾ����϶�ʱ�γɵľ���  
		imshow("img", tmp);
	}
	else if (event == CV_EVENT_LBUTTONUP)//����ɿ�������ͼ���ϻ�����  
	{
		org.copyTo(img);
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = Point(x, y);
		putText(img, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		rectangle(img, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);//���ݳ�ʼ��ͽ����㣬�����λ���img��  
		imshow("img", img);
		img.copyTo(tmp);
		//��ȡ���ΰ�Χ��ͼ�񣬲����浽dst��  
		int width = abs(pre_pt.x - cur_pt.x);
		int height = abs(pre_pt.y - cur_pt.y);
		if (width == 0 || height == 0) {
			printf("width == 0 || height == 0");
			return;
		}
		dst = org(Rect(min(cur_pt.x, pre_pt.x), min(cur_pt.y, pre_pt.y), width, height));
		namedWindow("dst");
		imshow("dst", dst);
		//waitKey(0);
	}
}