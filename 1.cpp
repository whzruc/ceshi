#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
void color(Mat img,int x,int y)
{
       int color_Bule=img.at<cv::Vec3b>(y, x)[0];
		 int color_Green=img.at<cv::Vec3b>(y, x)[1];
		 int color_Red=img.at<cv::Vec3b>(y, x)[2];
		if(color_Bule==0&&color_Green==0&&color_Red==0)
		cout<<"黑";
		else if(color_Bule==0&&color_Green==0&&color_Red==255)
		cout<<"红";
		else if(color_Bule==0&&color_Green==255&&color_Red==0)
		cout<<"绿";
		else if(color_Bule==0&&color_Green==255&&color_Red==255)
		cout<<"黄";
		else if(color_Bule==255&&color_Green==0&&color_Red==0)
		cout<<"蓝";
        else
        {
            cout<<"未知";
        }
        cout<<color_Bule<<" "<<color_Green<<" "<<color_Red;
        // cout.put(color_Bule)<<" ";
        // cout.put(color_Green)<<" ";
        // cout.put(color_Red)<<" ";

        

}



int main(int argc, char** argv)
{
    Mat src = imread(argv[1]);
    Mat src_gray,binary ;
    if (src.empty()) {
        printf("Could not load image...");
        return -1;
    }
    namedWindow("Input Image",WINDOW_NORMAL);
    imshow("Input Image",src);

    //二值化
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    threshold(src_gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    binary = ~binary;
    namedWindow("binary",WINDOW_NORMAL);
    imshow("binary", binary);
    //canny检测
    Mat img_canny;
    Canny(src,img_canny,45,127,3,false);
    namedWindow("canny",WINDOW_NORMAL);
    imshow("canny",img_canny);


    //发现轮廓
    vector<vector<Point>> contours;
    vector<Point> point;
    vector<Vec4i> hireachy;
    Mat imageContours=src.clone();

    findContours(img_canny, contours, hireachy, RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point());

    //绘制出所有轮廓
    for (int t = 0; t < contours.size(); t++)
    {

        int epsilon = 0.01*arcLength(contours[t], true);
        approxPolyDP(contours[t], point, epsilon, true);
         Moments moment;
          moment = moments(contours[t]);
           int x = (int)(moment.m10 / moment.m00);
           int y = (int)(moment.m01 / moment.m00);
       


        if(point.size()==3)
        {
           // cout<<t<<"  "<<"三角形"<<"  "<<color[t]<<endl;
            cout<<t<<"  "<<"三角形"<<"  ";
            color(src,x,y);
            cout<<endl;
        }
        else if (point.size() == 4)
        {
            //cout<<t<<"  "<<"矩形"<<"  "<<color[t]<<endl;
            cout<<t<<"  "<<"矩形"<<"    ";
            color(src,x,y);
            cout<<endl;
        }
        else if(point.size()>10)
        {
            //cout<<t<<"  "<<"圆形"<<"  "<<color[t]<<endl;
            cout<<t<<"  "<<"圆形"<<"    ";
            color(src,x,y);
            cout<<endl;
        }
        //cout<<point.size()<<endl;
        //cout<<x<<"  "<<y<<endl;
        
        int color_Bule=src.at<cv::Vec3b>(y, x)[0];
        switch (color_Bule)
        {
        case 0:
            color_Bule=255;
            break;
        case 255:
            color_Bule=0;
            break;
        
        default:
            break;
        }
		 int color_Green=src.at<cv::Vec3b>(y, x)[1];
         switch (color_Green)
        {
        case 0:
            color_Green=255;
            break;
        case 255:
            color_Green=0;
            break;
        
        default:
            break;
        }
		 int color_Red=src.at<cv::Vec3b>(y, x)[2];
         switch (color_Red)
        {
        case 0:
            color_Red=255;
            break;
        case 255:
            color_Red=0;
            break;
        
        default:
            break;
        }
         

        drawContours(imageContours,contours,t,Scalar(color_Bule,color_Green,color_Red),20,8,hireachy);
        //imageContours.setTo(Scalar(255, 255, 255, 0));
        //cv::circle(imageContours,Point(x,y),100,Scalar(255,255,255),-1);
        char buf[256];
        sprintf(buf, "%d", t);
        //putText(imageContours, buf,Point(x,y), CV_FONT_HERSHEY_SCRIPT_COMPLEX, 5, Scalar(0, 0, 0), 4, 8);
        putText(imageContours, buf,Point(x-500,y-300), CV_FONT_HERSHEY_SCRIPT_COMPLEX, 5, Scalar(0, 0, 0), 4, 8);
    }
        namedWindow("Contours Image",WINDOW_NORMAL);
        imshow("Contours Image",imageContours); //轮廓

    waitKey(0);

    return 0;
}
