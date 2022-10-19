#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;


int main(int argc, char* argv[]) {
	//Load a grayscale image
	Mat image = imread(argv[1], IMREAD_GRAYSCALE);

	if (!image.data) {
		cout << "couldn't find the image" << endl;
		return -1;
	}
	//DIFFERENCE OPERATOR
	Mat difference_output = image.clone();

	int T = atoi(argv[2]);
	int gx, gy, G;
	for (int i = 0; i < image.rows - 1; i++) {
		for (int j = 0; j < image.cols - 1; j++) {
			gx = 1 * image.at<uchar>(i, j) - 1 * image.at<uchar>(i, j + 1); //for x axis - multiply the difference operator x pixel with the image pixels and add them
			gy = 1 * image.at<uchar>(i, j) - 1 * image.at<uchar>(i + 1, j); //for y axis
			G = abs(gx) + abs(gy);
			if (G > T)
				difference_output.at<uchar>(i, j) = 255; //make the relevant output pixel as white to differentiate the edge
			else
				difference_output.at<uchar>(i, j) = 0;//or else keep the pixel as black

		}
	}

	//SOBEL OPERATOR
	Mat sobel_output = image.clone();
	for (int i = 1; i < image.rows - 1; i++) {
		for (int j = 1; j < image.cols - 1; j++) {
			gx = 1 * image.at<uchar>(i + 1, j - 1) + 2 * image.at<uchar>(i + 1, j) + 1 * image.at<uchar>(i + 1, j + 1) - 1 * image.at<uchar>(i - 1, j - 1) - 2 * image.at<uchar>(i - 1, j) - 1 * image.at<uchar>(i - 1, j + 1);
			gy = 1 * image.at<uchar>(i - 1, j + 1) + 2 * image.at<uchar>(i, j + 1) + 1 * image.at<uchar>(i + 1, j + 1) - 1 * image.at<uchar>(i - 1, j - 1) - 2 * image.at<uchar>(i, j - 1) - 1 * image.at<uchar>(i + 1, j - 1);
			G = abs(gx) + abs(gy);
			if (G > T)
				sobel_output.at<uchar>(i, j) = 255;
			else
				sobel_output.at<uchar>(i, j) = 0;

		}
	}


	namedWindow("Image");
	imshow("Image", image);
	namedWindow("Difference Operator");
	imshow("Difference Operator", difference_output);
	namedWindow("Sobel Operator");
	imshow("Sobel Operator", sobel_output);
	waitKey(0);

	return 0;
}
