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

	Mat input, inverted, green_channel, high_contrast_and_brightness, thresholded, opened, blackhat;

	input = imread(argv[1]);
	resize(input,input,Size(900, 640));
	bitwise_not ( input, inverted );
	green_channel = get_green_channel_of_bgr(inverted);
	green_channel.convertTo(high_contrast_and_brightness, -1, 3, 3);
	Mat kernel = getStructuringElement(MORPH_ELLIPSE,Size(31,31));
	morphologyEx(high_contrast_and_brightness, blackhat, MORPH_BLACKHAT, kernel);
	adaptiveThreshold(blackhat, thresholded,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY,25,0);
	Mat kernel2 = getStructuringElement(MORPH_ELLIPSE,Size(4,4));
	morphologyEx(thresholded, opened, MORPH_CLOSE, kernel2);
	bitwise_not ( thresholded, thresholded );

	//threshold( high_contrast_and_brightness, thresholded, 170, 255,THRESH_BINARY );
	imwrite("output.jpg", thresholded);
	imshow("input", input);
	imshow("inverted", inverted);
	imshow("green_channel", green_channel);
	imshow("high_contrast_and_brightness", high_contrast_and_brightness);
	imshow("blackhat", blackhat);
	imshow("thresholded", thresholded);
	imshow("opened", opened);
	waitKey(0);


	return 0;
}
