/*
* File:   main.cpp
* Author: sagar
*
* Created on 10 September, 2012, 7:48 PM
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <algorithm>

const unsigned char color = 0;

cv::Mat img = cv::Mat(480,640,CV_8U,255);
cv::Point last_pos(0,0);
void line(cv::Mat& img, const unsigned char & color,const cv::Point& from, const cv::Point& to){
  int x0,y0,x1,y1;
  std::cout << from << to << std::endl;
  x0=from.x; y0=from.y; x1=to.x, y1=to.y;
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2; // error value e_xy

  while(true){  /* loop */
    if(!((y0)>img.rows or (x0)>img.cols or (y0<0) or (x0<0) )) {
      img.at<unsigned char > (y0,x0) = color;
    }
    std::cout << x0 << "  "<< y0 << std::endl;
    if ((x0 == x1 && y0 == y1)) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}


void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
  cv::Point pos(x,y);
  switch (event) {
    case cv::EVENT_LBUTTONDOWN:
    if((last_pos!=pos)){
      std::cout << pos << std::endl;
      line(img,color,last_pos,pos);
    }
    last_pos=pos;
    break;
  }
}

int main() {



cv::namedWindow("lines");
cv::setMouseCallback("lines", CallBackFunc, NULL);
//unconditional loop
bool ok= true;
cv::Point pos;
while (ok) {
  cv::imshow("lines", img);
  int key = cv::waitKey(5);
  switch(key){
    case 'x':
      ok=false;
      break;
    case 'w':
      pos=cv::Point(240,-320);
      if((last_pos!=pos)){
        std::cout << pos << std::endl;
        line(img,color,last_pos,pos);
      }
      last_pos=pos;
      break;
    case 'a':
      pos=cv::Point(-240,320);
      if((last_pos!=pos)){
        std::cout << pos << std::endl;
        line(img,color,last_pos,pos);
      }
      last_pos=pos;
      break;
    case 's':
      pos=cv::Point(240,980);
      if((last_pos!=pos)){
        std::cout << pos << std::endl;
        line(img,color,last_pos,pos);
      }
      last_pos=pos;
      break;
    case 'd':
      pos=cv::Point(710,320);
      if((last_pos!=pos)){
        std::cout << pos << std::endl;
        line(img,color,last_pos,pos);
      }
      last_pos=pos;
        break;
  }
}
return 0;
}
