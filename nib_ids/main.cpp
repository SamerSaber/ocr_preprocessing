#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
using namespace std;
using namespace cv;

Mat get_green_channel_of_bgr(Mat & input)
{
	Mat bgr[3];   //destination array
	split(input,bgr);//split source

	return bgr[1];
}
int main(int argc, char * argv[])
{

	if (argc < 2)
	{
		cout << "please pass the image path as argument!! \n";
		return 1;
	}

	Mat input, inverted, green_channel, high_contrast_and_brightness, thresholded,adaptive_thresholded, opened, tophat;

	input = imread(argv[1]);
	resize(input,input,Size(2024, 1000));
	bitwise_not ( input, inverted );
	green_channel = get_green_channel_of_bgr(inverted);
	green_channel.convertTo(high_contrast_and_brightness, -1, 1.2, 0);
	Mat kernel = getStructuringElement(MORPH_ELLIPSE,Size(21,21));
	morphologyEx(high_contrast_and_brightness, tophat, MORPH_TOPHAT, kernel);
	threshold( tophat, thresholded, 25, 255,THRESH_TOZERO );
	adaptiveThreshold(thresholded, adaptive_thresholded,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,25,0);
	Mat kernel2 = getStructuringElement(MORPH_ELLIPSE,Size(3,3));
	morphologyEx(adaptive_thresholded, opened, MORPH_CLOSE, kernel2);
	bitwise_not ( adaptive_thresholded, adaptive_thresholded );

	//threshold( high_contrast_and_brightness, thresholded, 170, 255,THRESH_BINARY );
	imwrite("output.jpg", adaptive_thresholded);
	imwrite("input.jpg", input);
	imwrite("inverted.jpg", inverted);
	imwrite("green_channel.jpg", green_channel);
	imwrite("high_contrast_and_brightness.jpg", high_contrast_and_brightness);
	imwrite("tophat.jpg", tophat);
	imwrite("thresholded.jpg", thresholded);
	imwrite("adaptive_thresholded.jpg", adaptive_thresholded);
	imwrite("opened.jpg", opened);
	imshow("input", input);
	imshow("inverted", inverted);
	imshow("green_channel", green_channel);
	imshow("high_contrast_and_brightness", high_contrast_and_brightness);
	imshow("tophat", tophat);
	imshow("thresholded", thresholded);
	imshow("adaptive_thresholded", adaptive_thresholded);
	imshow("opened", opened);
	waitKey(0);


	return 0;
}
