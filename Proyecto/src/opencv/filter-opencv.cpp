#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <chrono>


int main(int argc, const char * argv[]) {


    cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double,std::ratio<1,1000> > elapsed_seconds;



    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5),cv::Point(2,2));   // Use the default structuring element (kernel) for erode and dilate

    cv::Mat maxImage(800,480,0);
    // Perform max filtering on image using dilate



    std::vector<double> time_samples;
    time_samples.reserve(100);
    for(int i=0; i<100; i++){ //final
      start = std::chrono::system_clock::now();
      cv::dilate(image, maxImage, kernel);
      end = std::chrono::system_clock::now();
      elapsed_seconds = end - start;
      time_samples.push_back(elapsed_seconds.count());
    }

    double mean=0;
    double N = 0;
    for(std::vector<double>::iterator it = time_samples.begin(); it != time_samples.end(); ++it){
      mean += *it;
      N++;
    }
    mean=mean/N;

    double var = 0;
    double elem = 0;
    for(std::vector<double>::iterator it = time_samples.begin(); it != time_samples.end(); ++it){
      elem = ((*it)-mean);
      elem = elem*elem;
      var += elem;
    }
    var = sqrt(var/(N-1));


    cv::imshow( "Display swindow", image );                // Show our image inside it.

    cv::imshow( "Display window", maxImage );                // Show our image inside it.

    cv::waitKey(0); // Wait for a keystroke in the window
    std::cout << image.rows*image.cols << " , " <<  mean << " , " << var << std::endl;

    return 0;
}
