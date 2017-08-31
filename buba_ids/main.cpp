#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
using namespace std;
using namespace cv;

Mat get_red_channel_of_bgr(Mat & input)
{
	Mat bgr[3];   //destination array
	split(input,bgr);//split source

	return bgr[0];
}
int main(int argc, char * argv[])
{

	if (argc < 2)
	{
		cout << "please pass the image path as argument!! \n";
		return 1;
	}

	Mat input, inverted, blue_channel, high_contrast_and_brightness, thresholded,adaptive_thresholded,out, opened,closed, blackhat;

	input = imread(argv[1]);
	resize(input,input,Size(3500, 1500));
	bitwise_not ( input, inverted );
	blue_channel = get_red_channel_of_bgr(inverted);
	blue_channel.convertTo(high_contrast_and_brightness, -1, 1.7, -2);
	threshold( high_contrast_and_brightness, thresholded, 215, 255,THRESH_TOZERO );
	adaptiveThreshold(thresholded, adaptive_thresholded,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,27,0);
	Mat kernel2 = getStructuringElement(MORPH_CROSS,Size(1,1));
	morphologyEx(adaptive_thresholded, opened, MORPH_OPEN, kernel2);
//	Mat kernel = getStructuringElement(MORPH_CROSS,Size(2,2));
//	morphologyEx(opened, closed, MORPH_CLOSE, kernel);
	bitwise_not ( opened, out );

	//threshold( high_contrast_and_brightness, thresholded, 170, 255,THRESH_BINARY );


	imwrite("input.jpg", input);
	imwrite("inverted.jpg", inverted);
	imwrite("blue_channel.jpg", blue_channel);
	imwrite("high_contrast_and_brightness.jpg", high_contrast_and_brightness);
	imwrite("adaptive_thresholded.jpg", adaptive_thresholded);
	imwrite("thresholded.jpg", thresholded);
	imwrite("opened.jpg", opened);
	imwrite("out.jpg", out);


	imwrite("output.jpg", out);
	imshow("input", input);
	imshow("inverted", inverted);
	imshow("blue_channel", blue_channel);
	imshow("high_contrast_and_brightness", high_contrast_and_brightness);
	imshow("adaptive_thresholded", adaptive_thresholded);
	imshow("thresholded", thresholded);
	imshow("opened", opened);
	imshow("out", out);

	waitKey(0);


	return 0;
}
