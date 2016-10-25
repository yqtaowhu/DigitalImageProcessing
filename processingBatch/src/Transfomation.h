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
	void AffTrans (cv::Mat& src);							//仿射变换
	void Mirror(cv::Mat& image);
	void Salt(int n);
    static void on_mouse(int event, int x, int y, int flags, void *ustc);          //鼠标操作
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

//添加椒盐噪声
void Transfomation::Salt(int n) {
	char filename[1001];
	char filename2[1001];
	for (int i = 1; i <= numbers; i++) {
		sprintf(filename, "%s\\%d.jpg", input, i);		// 将图片以数字命名：例如1.jpg 2.jpg等，放入文件夹下
		org = imread(filename);				//filename其实就是一个路径
		org.copyTo(img);
		org.copyTo(dst);
	    //imshow("img", org);//显示图像原图
		//加椒盐噪声
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
		//imshow("img", img);//显示图像原图
	}
}

//改变图像尺寸
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
//	/// 加载源图像
//	//src = imread( "dst.jpg", 1 );
//
//	/// 设置目标图像的大小和类型与源图像一致
//	warp_dst = Mat::zeros( src.rows, src.cols, src.type() );
//
//	/// 设置源图像和目标图像上的三组点以计算仿射变换
//	srcTri[0] = Point2f( 0,0 );
//	srcTri[1] = Point2f( src.cols - 1, 0 );
//	srcTri[2] = Point2f( 0, src.rows - 1 );
//
//	dstTri[0] = Point2f( src.cols*0.0, src.rows*0.33 );
//	dstTri[1] = Point2f( src.cols*0.85, src.rows*0.25 );
//	dstTri[2] = Point2f( src.cols*0.15, src.rows*0.7 );
//
//	/// 求得仿射变换
//	warp_mat = getAffineTransform( srcTri, dstTri );
//
//	/// 对源图像应用上面求得的仿射变换
//	warpAffine( src, warp_dst, warp_mat, warp_dst.size() );
//
//	/** 对图像扭曲后再旋转 */
//
//	/// 计算绕图像中点顺时针旋转50度缩放因子为0.6的旋转矩阵
//	Point center = Point( warp_dst.cols/2, warp_dst.rows/2 );
//	double angle = -50.0;
//	double scale = 0.6;
//
//	/// 通过上面的旋转细节信息求得旋转矩阵
//	rot_mat = getRotationMatrix2D( center, angle, scale );
//
//	/// 旋转已扭曲图像
//	warpAffine( warp_dst, warp_rotate_dst, rot_mat, warp_dst.size() );
//	/// 显示结果
//	//namedWindow( source_window, CV_WINDOW_AUTOSIZE );
//	//imshow( source_window, src );
//	//namedWindow( warp_window, CV_WINDOW_AUTOSIZE );
//	//imshow( warp_window, warp_dst );
//	imwrite("bianhuan1.jpg",warp_dst);
//	//namedWindow( warp_rotate_window, CV_WINDOW_AUTOSIZE );
//	//imshow( warp_rotate_window, warp_rotate_dst );
//	imwrite("bianhuan2.jpg", warp_rotate_dst);
//	/// 等待用户按任意按键退出程序
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
		sprintf(filename, "%s\\%d.jpg", input, i);		// 将图片以数字命名：例如1.jpg 2.jpg等，放入文件夹下
		org = imread(filename);				//filename其实就是一个路径
		org.copyTo(img);
		org.copyTo(dst);
		/*下面三句话是对图像进行截图处理*/
		namedWindow("img", 0);
		//cvResizeWindow("img",500,500);
		setMouseCallback("img", on_mouse, 0);//调用函数进行截图处理,是对img窗口中的图像进行处理
		imshow("img", img);//显示图像原图
		waitKey(0);
		namedWindow("dst", 0);
		imshow("dst", dst);
		sprintf(filename2, "%s\\%d.jpg", output, i);
		imwrite(filename2, dst);
	}
	return 0;
}

//鼠标响应操作
void Transfomation::on_mouse(int event, int x, int y, int flags, void *ustc)//event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号  
{
	static Point pre_pt = (-1, -1);//初始坐标  
	static Point cur_pt = (-1, -1);//实时坐标  
	char temp[16];
	if (event == CV_EVENT_LBUTTONDOWN)//左键按下，读取初始坐标，并在图像上该点处划圆  
	{
		org.copyTo(img);//将原始图片复制到img中  
		sprintf(temp, "(%d,%d)", x, y);
		pre_pt = Point(x, y);
		putText(img, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255), 1, 8);//在窗口上显示坐标  
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);//划圆  
		imshow("img", img);
	}
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//左键没有按下的情况下鼠标移动的处理函数  
	{
		img.copyTo(tmp);//将img复制到临时图像tmp上，用于显示实时坐标  
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = Point(x, y);
		putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));//只是实时显示鼠标移动的坐标  
		imshow("img", tmp);
	}
	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON))      //左键按下时，鼠标移动，则在图像上划矩形  
	{
		img.copyTo(tmp);
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = Point(x, y);
		putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		rectangle(tmp, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);//在临时图像上实时显示鼠标拖动时形成的矩形  
		imshow("img", tmp);
	}
	else if (event == CV_EVENT_LBUTTONUP)//左键松开，将在图像上划矩形  
	{
		org.copyTo(img);
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = Point(x, y);
		putText(img, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
		circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		rectangle(img, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);//根据初始点和结束点，将矩形画到img上  
		imshow("img", img);
		img.copyTo(tmp);
		//截取矩形包围的图像，并保存到dst中  
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