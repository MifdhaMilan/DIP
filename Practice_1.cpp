#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

Mat drawHistogram(Mat gray) {
    int histogram[256];

    //initialize array elements
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    //number of pixels for each value in original image
    for (int y = 0; y < gray.rows; y++) {
        for (int x = 0; x < gray.cols; x++) {
            histogram[(int)gray.at<uchar>(y, x)]++; //find how many no.of pixels for each intensity currently
        }
    }

    //Print number of pixels for each intensity value
    for (int i = 0; i < 256; i++)
        cout << i << ":" << histogram[i] << endl;

    int histogram_height = 400;
    int histogram_width = 512; //use any value you wish
    int bin_w = cvRound((double)histogram_width / 256);


    //Draw the histogram for B,G and R
    Mat histImage(histogram_height, histogram_width, CV_8UC1, Scalar(255, 255, 255)); //create a window to draw the histogram

    //Find the maximum number of pixels from histogram array
    int max = histogram[0];
    for (int i = 1; i < 256; i++) {
        if (max < histogram[i]) {
            max = histogram[i];
        }
    }

    //Normalize the histogram between 0 and histogram height
    for (int i = 0; i < 256; i++) {
        histogram[i] = ((double)histogram[i] / max) * histogram_height;
    }

    //Draw the lines of histogram
    for (int i = 0; i < 256; i++) {
        //line ( histImage, Point pt1, Point pt2,color , thickness, lineType, shift)
        line(histImage, Point(bin_w * (i), histogram_height), Point(bin_w * (i), histogram_height - histogram[i]), Scalar(0, 0, 0), 1, 8, 0);
    }
    return histImage;
}

Mat contrastStretching(Mat gray, int a, int b) {
    //copy the grey image to new high contrast image
    Mat constrastImg = gray.clone();

    int c = 5;
    int d = 250;
    //int the command line - Project1 low_contrast_girl.jpg 103 234 - pass like this
    int x;
    int out;

    for (int i = 0; i < gray.rows; i++) {
        for (int j = 0; j < gray.cols; j++) {
            x = (int)gray.at<uchar>(i, j);
            if (x >= 0 && x <= a)
                out = int((c / a) * x);
            else if (a < x && x <= b)
                out = int(((d - c) / (b - a)) * (x - a) + 5);
            else if (x > b && x <= 255)
                out = int(((255 - d) / (255 - b)) * (x - b) + 250);

            //convert the int value to uchar and apply it to the high contrast image
            constrastImg.at<uchar>(i, j) = uchar(out);
        }
    }
    return constrastImg;

}

int main(int argc, char* argv[]) {
    Mat image = imread(argv[1]); //get image from command line, if 0 - exe file, if 1 - image name

    if (!image.data) {
        cout << "couldn't find the image!" << endl; //endl in use to print new line in mat
        return -1;
    }

    Mat gray(image.rows, image.cols, CV_8UC1, Scalar(0)); //CV_8UC1 - because gray scale, 1 scale image
    //convert BGR image to gray using opencv function, without using loops
    cvtColor(image, gray, COLOR_BGR2GRAY); //1st param - input image, 2nd - output image, 3rd - conversion method


    //histogram drawing for original image
    Mat histImage = drawHistogram(gray);
     
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);

    Mat contrastImage = contrastStretching(gray, a, b);

    Mat histContrastImage = drawHistogram(contrastImage);

    imwrite("output_gray_image_histogram.jpg", histImage);
    imwrite("output_contrast_image.jpg", contrastImage);
    imwrite("output_contrast_image_histogram.jpg", histContrastImage);
 

    namedWindow("Image");
    imshow("Image", image);
    namedWindow("Gray");
    imshow("Gray", gray);
    namedWindow("Histogram");
    imshow("Histogram", histImage);
    namedWindow("Contrast Image"); 
    imshow("Contrast Image", contrastImage); 
    waitKey(0);

    return 0;
}