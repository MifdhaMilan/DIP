#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    Mat image = imread(argv[1]); //get image from command line, if 0 - exe file, if 1 - image name

    if (!image.data) {
        cout << "couldn't find the image!" << endl; //endl in use to print new line in mat
        return -1;
    }

    Mat gray(image.rows, image.cols, CV_8UC1, Scalar(0)); //CV_8UC1 - because gray scale, 1 scale image
    //convert BGR image to gray using opencv function, without using loops
    cvtColor(image, gray, COLOR_BGR2GRAY); //1st param - input image, 2nd - output image, 3rd - conversion method

    //copy the grey image to new high contrast image
    Mat constrastImg = gray.clone();

    /*int a = 103;
    int b = 234;*/
    int a = atoi(argv[2]); //get from command line
    int b = atoi(argv[3]);
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



    namedWindow("Image"); //give a name to window
    imshow("Image", image); //show the image on window
    namedWindow("Gray"); //give a name to window
    imshow("Gray", gray); //show the image on window
    namedWindow("Contrast Image"); //give a name to window
    imshow("Contrast Image", constrastImg); //show the image on window
    waitKey(0);

    return 0;
}