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

float gain=1;
bool update=false;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
  switch (event) {
    case cv::EVENT_MOUSEWHEEL:
      if(cv::getMouseWheelDelta(flags)>0){
        gain=std::max(0.0f,gain-0.1f);
      }else{
        gain=std::min(1.0f,gain+0.1f);
      }
      std::cout<<"gain :"<<gain<<std::endl;
      update=true;
    break;
  }
}



int main() {
cv::VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.

if (!stream1.isOpened()) { //check if video device has been initialised
std::cout << "cannot open camera";
}
cv::namedWindow("cam");
cv::setMouseCallback("cam", CallBackFunc, NULL);

float brightness=0;
float saturation=0.5;

stream1.set(CV_CAP_PROP_BRIGHTNESS,brightness);
stream1.set(CV_CAP_PROP_SATURATION,saturation);
stream1.set(CV_CAP_PROP_GAIN,gain);

//unconditional loop
bool ok= true;
while (ok) {
  cv::Mat cameraFrame;
  stream1.read(cameraFrame);
  cv::imshow("cam", cameraFrame);
  int key = cv::waitKey(5);
  switch(key){
    case 81:
      brightness=std::min(1.0f,brightness+0.1f);
      stream1.set(CV_CAP_PROP_BRIGHTNESS,brightness);
      std::cout<<"brightness: "<<brightness<<std::endl;
    break;
    case 83:
      brightness=std::max(0.0f,brightness-0.1f);
      stream1.set(CV_CAP_PROP_BRIGHTNESS,brightness);
      std::cout<<"brightness: "<<brightness<<std::endl;     
    break;
    case 82:
      saturation=std::min(1.0f,saturation+0.1f);
      stream1.set(CV_CAP_PROP_SATURATION,saturation);
      std::cout<<"saturation: "<<saturation<<std::endl;
    break;
    case 84:
      saturation=std::max(0.0f,saturation-0.1f);
      stream1.set(CV_CAP_PROP_SATURATION,saturation);
      std::cout<<"saturation: "<<saturation<<std::endl;
    break;
    case 'x':
      ok=false;
      break;
//    default:
//    std::cout<<key<<std::endl;
  }
  if(update){
    stream1.set(CV_CAP_PROP_GAIN,gain);
    update=false;
  }
}
return 0;
}
