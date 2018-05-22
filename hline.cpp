#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <math.h>
using namespace cv;
using namespace std;

#define PI 3.14159265

void help()
{
 cout << "\nThis program demonstrates line finding with the Hough transform.\n"
         "Usage:\n"
         "./houghlines <image_name>, Default is pic1.jpg\n" << endl;
}

int main(int argc, char** argv)
{
 const char* filename = argc >= 2 ? argv[1] : "lane.jpeg";

 Mat src = imread(filename, 0);
 if(src.empty())
 {
     help();
     cout << "can not open " << filename << endl;
     return -1;
 }

 Mat dst, cdst;
 Canny(src, dst, 50, 200, 3);
 cvtColor(dst, cdst, CV_GRAY2BGR);
 float x=0;
 float y=0;


 //if 0
  // vector<Vec2f> lines;
  // HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );

  // for( size_t i = 0; i < lines.size(); i++ )
  // {
  //    float rho = lines[i][0], theta = lines[i][1];
  //    Point pt1, pt2;
  //    double a = cos(theta), b = sin(theta);
  //    double x0 = a*rho, y0 = b*rho;
  //    pt1.x = cvRound(x0 + 1000*(-b));
  //    pt1.y = cvRound(y0 + 1000*(a));
  //    pt2.x = cvRound(x0 - 1000*(-b));
  //    pt2.y = cvRound(y0 - 1000*(a));
  //    line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
  // }
 // #else
  vector<Vec4i> lines;
  HoughLinesP(dst, lines, 1, CV_PI/180, 100, 50, 10 );
  for( size_t i = 0; i < lines.size(); i++ )
  {
    Vec4i l = lines[i];
    y= l[3]-l[1];
    x=l[2]-l[0];
    if (  pow(x,2)+pow(y,2)>25000   )  
      {  printf(" %f \n",abs(atan(y/x)) ); 
        if(  abs(atan(y/x)) > 1*PI/18 )

            line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
            
      }
  }
 // #endif
 imshow("source", src);
 imshow("source", dst);
 imshow("detected lines", cdst);

 waitKey();

 return 0;
}