#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include<windows.h>
//#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

void addDotToImage(Mat &M, int iRowDotCenter, int iColDotCenter, int dotSizePixel)
{
    int nImageRow = M.rows;
    int nImageCol = M.cols;  
    int nImageChan = M.channels();

    for (int iRowImage = 0; iRowImage < dotSizePixel; iRowImage++)
    {

        int iRow = iRowDotCenter + iRowImage - (dotSizePixel - 1) / 2;

        uchar* p;

        p = M.ptr<uchar>(iRow);

        for (int iColImage = 0; iColImage < dotSizePixel; iColImage++)
        {

            int iCol = iColDotCenter + iColImage - (dotSizePixel - 1) / 2;

            for (int iChan = 0; iChan < nImageChan; iChan++)
            {

                p[iCol * nImageChan + iChan] = 255;

            }

            

        }

    }
}


void addCrosshairToImage(Mat& M, int iRowCrosshairCenter, int iColCrosshairCenter, int crosshairSizePixel)
{
    int nImageRow = M.rows;
    int nImageCol = M.cols;
    int nImageChan = M.channels();

    for (int iRowImage = 0; iRowImage < crosshairSizePixel; iRowImage++)
    {

        int iRow = iRowCrosshairCenter + iRowImage - (crosshairSizePixel - 1) / 2;

        uchar* p;

        p = M.ptr<uchar>(iRow);

        int iCol = iColCrosshairCenter;

        for (int iChan = 0; iChan < nImageChan; iChan++)
        {

            p[iCol * nImageChan + iChan] = 255;

        }

        

    }

    

    int iRow = iRowCrosshairCenter;

    uchar* p;

    p = M.ptr<uchar>(iRow);

    for (int iColImage = 0; iColImage < crosshairSizePixel; iColImage++)
    {

        int iCol = iColCrosshairCenter + iColImage - (crosshairSizePixel - 1) / 2;

        for (int iChan = 0; iChan < nImageChan; iChan++)
        {

            p[iCol * nImageChan + iChan] = 255;

        }

    }    

}

void addBoxToImage(Mat& M, int iRowBoxCenter, int iColBoxCenter, int boxSizePixel)
{
    int nImageRow = M.rows;
    int nImageCol = M.cols;
    int nImageChan = M.channels();

    for (int iRowImage = 0; iRowImage < boxSizePixel; iRowImage++)
    {
        int iColLeft = iColBoxCenter - (boxSizePixel - 1) / 2;

        int iColRight = iColBoxCenter + (boxSizePixel - 1) / 2;

        int iRow = iRowBoxCenter + iRowImage - (boxSizePixel - 1) / 2;

        uchar* p;

        p = M.ptr<uchar>(iRow);

        for (int iChan = 0; iChan < nImageChan; iChan++)
        {

            p[iColLeft*nImageChan + iChan] = 255;

            p[iColRight*nImageChan + iChan] = 255;

        }
    

    }



    int iRowTop = iRowBoxCenter - (boxSizePixel - 1) / 2;

    uchar* p;

    p = M.ptr<uchar>(iRowTop);

    for (int iColImage = 0; iColImage < boxSizePixel; iColImage++)
    {

        int iCol = iColBoxCenter + iColImage - (boxSizePixel - 1) / 2;

        for (int iChan = 0; iChan < nImageChan; iChan++)
        {

            p[iCol * nImageChan + iChan] = 255;

            p[iCol * nImageChan + iChan] = 255;

        }

    }

    int iRowBottom = iRowBoxCenter + (boxSizePixel - 1) / 2;    

    p = M.ptr<uchar>(iRowBottom);

    for (int iColImage = 0; iColImage < boxSizePixel; iColImage++)
    {

        int iCol = iColBoxCenter + iColImage - (boxSizePixel - 1) / 2;

        for (int iChan = 0; iChan < nImageChan; iChan++)
        {

            p[iCol * nImageChan + iChan] = 255;

            p[iCol * nImageChan + iChan] = 255;

        }

    }

}

Mat findImageDiff(Mat& M1, Mat& M2)
{
    int nImageRow = M1.rows;
    int nImageCol = M1.cols;
    int nImageChan = M1.channels();

    Mat diffM(nImageRow, nImageCol, CV_8UC1, Scalar(0));

    uchar* p1;
    uchar* p2;
    uchar* diffP;

    for (int iRowImage = 0; iRowImage < nImageRow; iRowImage++)
    {
        for (int iColImage = 0; iColImage < nImageCol; iColImage++)
        {
            p1 = M1.ptr<uchar>(iRowImage);
            p2 = M2.ptr<uchar>(iRowImage);
            diffP = diffM.ptr<uchar>(iRowImage);

            double pixDiffVal = 0;

            pixDiffVal += pow(double(p1[iColImage * nImageChan]) - double(p2[iColImage * nImageChan]), 2.0);
            pixDiffVal += pow(double(p1[iColImage * nImageChan + 1]) - double(p2[iColImage * nImageChan + 1]), 2.0);
            pixDiffVal += pow(double(p1[iColImage * nImageChan + 2]) - double(p2[iColImage * nImageChan + 2]), 2.0);

            pixDiffVal = sqrt(pixDiffVal)/sqrt(3);

            diffP[iColImage] = UINT8 (pixDiffVal);

        }

        

    }



    return diffM;

}

void findPeakDiffVal(Mat M, int& iRowPeak, int& iColPeak)
{
    int peakDiffVal = 0;

    iRowPeak = 0;
    iColPeak = 0;

    int nRowImage = M.rows;
    int nColImage = M.cols;

    uchar* p;

    

    for (int iRowImage = 0; iRowImage < nRowImage; iRowImage++)
    {
        p = M.ptr<uchar>(iRowImage);

        for (int iColImage = 0; iColImage < nColImage; iColImage++)
        {

            if (p[iColImage] > peakDiffVal) 
            {
                peakDiffVal = p[iColImage];

                iRowPeak = iRowImage;
                iColPeak = iColImage;

            }

        }

    }

}



int main()
{

    VideoCapture cap1(0); // Adjust the camera index as needed

    if (!cap1.open(1))
        return 0;

    Mat camera1Frame1;
    Mat camera1Frame2;

    cap1 >> camera1Frame1;

    imshow("Camera Image", camera1Frame1);

    waitKey(1);

    String windowName = "Calibration Window";

    int nImageRow = 1000;
    int nImageCol = 1800;

    int screenCalDotCornerOffset = 0;
    int screenCalDotSize = 1;

    int cameraCalDotSize = 7;

    // Display blank image.
    Mat M(nImageRow, nImageCol, CV_8UC1, Scalar(0));

    addDotToImage(M, screenCalDotCornerOffset, screenCalDotCornerOffset, screenCalDotSize);

    addDotToImage(M, nImageRow - 1 - screenCalDotCornerOffset, screenCalDotCornerOffset, screenCalDotSize);

    addDotToImage(M, screenCalDotCornerOffset, nImageCol - 1 - screenCalDotCornerOffset, screenCalDotSize);

    addDotToImage(M, nImageRow - 1 - screenCalDotCornerOffset, nImageCol - 1 - screenCalDotCornerOffset, screenCalDotSize);  

    addCrosshairToImage(M, 100, 100, 9);

    addBoxToImage(M, 100, 100, 13);

    imshow(windowName, M);

    printf("Maximize screen to desired display and press any keystroke in window to continue.\n");

    int key = waitKey(0); // Wait for a keystroke in the window  

    int iRowDotCenterStart = 100;

    int iRowDotCenter = iRowDotCenterStart;

    int iColDotCenterStart = 100;

    int iColDotCenter = iColDotCenterStart;

    bool isDotDisplayed = true;

    for (;;)
    {

        

        // Display image of screen with no dot.

        Mat M(nImageRow, nImageCol, CV_8UC1, Scalar(0));

        imshow(windowName, M);

        waitKey(1); // Wait for a keystroke in the window

        Sleep(50);

        // Capture image of screen.

        for (int iFrameCap = 0; iFrameCap < 10; iFrameCap++) {
            cap1 >> camera1Frame1;
        }

        // Display image of screen with dot.

        addDotToImage(M, iRowDotCenter, iColDotCenter, cameraCalDotSize);

        imshow(windowName, M);

        waitKey(1);

        Sleep(50);

        // Capture image of screen.

        for (int iFrameCap = 0; iFrameCap < 10; iFrameCap++) {
            cap1 >> camera1Frame2;
        }

        // Compare the two images. Subtract difference in values to find position of dot displayed on screen.


        Mat camera1FrameDiff = findImageDiff(camera1Frame1, camera1Frame2);

        

        int iRowPeak, iColPeak;

        findPeakDiffVal(camera1FrameDiff, iRowPeak, iColPeak);

        addBoxToImage(camera1FrameDiff, iRowPeak, iColPeak, 13);

        addBoxToImage(camera1Frame2, iRowPeak, iColPeak, 13);   

        addCrosshairToImage(camera1Frame2, iRowPeak, iColPeak, 9);

        printf("iRow Peak = % d\t iCol Peak = % d\n", iRowPeak, iColPeak);

        

        imshow("Camera1 Frame Diff", camera1FrameDiff);
        
        imshow("Camera1 Frame2", camera1Frame2);

        
        waitKey(1);

        Sleep(50);

        iRowDotCenter += 100;

        if (iRowDotCenter > nImageRow - 100)
        {
            iRowDotCenter = iRowDotCenterStart;

            iColDotCenter += 100;

            if (iColDotCenter > nImageCol - 100)
            {
                iColDotCenter = iColDotCenterStart;
            }
        }

    }
    
    return 0;
}