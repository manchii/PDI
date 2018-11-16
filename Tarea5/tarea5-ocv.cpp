/*
* File:   main.cpp
* Author: sagar
*
* Created on 10 September, 2012, 7:48 PM
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <algorithm>

int main()
{
    // Using time point and system_clock
    std::chrono::time_point<std::chrono::system_clock> start, end;

    //generate random image
    const int image_size=512;

    cv::Mat image(cv::Size(image_size,image_size),CV_64F);
      //filter output image container
    cv::Mat dst1(cv::Size(image_size,image_size),CV_64F);
    cv::Mat dst2(cv::Size(image_size,image_size),CV_64F);
    cv::Mat dst3(cv::Size(image_size,image_size),CV_64F);


    cv::randn(image,(0,0,0),(1000,1000,1000));
    //header to csv file
    std::cout << "ksize" << "," << "filter2D(us)" << "," << "sepfilter(us)" << "," << "FTfilter(us)" << std::endl;;
    //iterate for multiple ksize
    for(int ksize=1;ksize<125;ksize+=8){
      std::chrono::duration<double,std::ratio<1,1000000> > elapsed_seconds;
      double acc_samp=0;
      //get kernels
      double sigma = ( ( (double) ksize) +2 )/6;
      cv::Mat kernel = cv::getGaussianKernel(ksize,sigma);
      cv::Mat kernel_2D = kernel*kernel.t();

      //filter 2D
      //iterate for multiple execution instances
      for(int i=0;i<100;i++){
        start = std::chrono::system_clock::now();
        cv::filter2D(image,dst1,-1,kernel_2D);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        acc_samp+=elapsed_seconds.count();
      }
      std::cout << ksize << "," << acc_samp/100;
      acc_samp=0;

      //filter 2D sep
      for(int i=0;i<100;i++){
        start = std::chrono::system_clock::now();
        cv::sepFilter2D(image,dst2,-1,kernel,kernel);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        acc_samp+=elapsed_seconds.count();
      }
      std::cout << "," << acc_samp/100;
      acc_samp = 0;
      //Frequency domain filter
      //create kernel
        //optimal sizes for image
      int u = cv::getOptimalDFTSize(image.cols);
      int v = cv::getOptimalDFTSize(image.rows);
      cv::Mat kernel_padded(cv::Size(u,v), CV_64F);
      kernel_padded = 0;
        //copy kernel
      kernel_2D.copyTo(kernel_padded(cv::Rect(u/2-ksize,v/2-ksize,ksize,ksize)));
        // copy the source image, on the border add zero values
      cv::Mat planes[] = { cv::Mat_< double> (kernel_padded), cv::Mat::zeros(kernel_padded.size(), CV_64F) };
        // create a complex filter
      cv::Mat complex_filter;
      cv::merge(planes, 2, complex_filter);
      cv::dft(complex_filter, complex_filter, cv::DFT_COMPLEX_OUTPUT);

      //complex filter calculation
      for(int i=0;i<100;i++){
        cv::Mat planes_i[] = { cv::Mat_< double> (image), cv::Mat::zeros(image.size(), CV_64F) };
        cv::Mat complex_image;
        start = std::chrono::system_clock::now();
        cv::merge(planes_i, 2, complex_image);
        // dft calculation
        cv::dft(complex_image, complex_image, cv::DFT_COMPLEX_OUTPUT);
        // mixing of spectrums

        cv::mulSpectrums(complex_image,complex_filter,complex_image, 0);

        //idft
        cv::dft(complex_image,dst3, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT);

        //leveling by s(x,y)=idft(u,v)/(N*M);
        dst3=dst3/(image_size*image_size);

        int cx = dst3.cols/2;
        int cy = dst3.rows/2;

        cv::Mat q0(dst3, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
        cv::Mat q1(dst3, cv::Rect(cx, 0, cx, cy));  // Top-Right
        cv::Mat q2(dst3, cv::Rect(0, cy, cx, cy));  // Bottom-Left
        cv::Mat q3(dst3, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

        cv::Mat tmp;                            // swap quadrants (Top-Left with Bottom-Right)
        q0.copyTo(tmp);
        q3.copyTo(q0);
        tmp.copyTo(q3);
        q1.copyTo(tmp);                     // swap quadrant (Top-Right with Bottom-Left)
        q2.copyTo(q1);
        tmp.copyTo(q2);
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        acc_samp+=elapsed_seconds.count();
      }
      std::cout << "," << acc_samp/100;
      // cv::imshow("filter2d",dst1);
      // cv::imshow("freq",dst3);
      // cv::waitKey();
      std::cout << std::endl;
    }

    return 0;

}
