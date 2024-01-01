// OpenCvExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <iostream>
#include <chrono>


//#include <graphics.h> 
#include <thread>

//#include "chrono_io"


using namespace cv;
using namespace std;

#include <fstream>

// Function to capture frames from Camera 1
void captureCamera1(VideoCapture& cap1, long long clockTicsPerTimeDiff, long long nextCaptureClockTic) {
    Mat frame1;
    while (true) {

        while (std::chrono::system_clock::now().time_since_epoch().count() < nextCaptureClockTic) {
            
            int junkVal = 0;
            for (int iJunkVal = 0; iJunkVal < 100; iJunkVal++) {
                junkVal++;
            }

        }

        cap1.grab();

        cap1.retrieve(frame1);
        cap1.retrieve(frame1);



       
        if (frame1.empty()) {
            cerr << "Failed to capture frame from Camera 1\n";
            break;
        }
        // Process or display frame1 as needed
        imshow("Camera 1", frame1);
        if (waitKey(30) == 27) // Press Esc to exit
            break;

        nextCaptureClockTic += clockTicsPerTimeDiff;
    }
}

// Function to capture frames from Camera 2
void captureCamera2(VideoCapture& cap2, long long clockTicsPerTimeDiff, long long nextCaptureClockTic) {
    Mat frame2;
    while (true) {

        while (std::chrono::system_clock::now().time_since_epoch().count() < nextCaptureClockTic) {

            int junkVal = 0;
            for (int iJunkVal = 0; iJunkVal < 100; iJunkVal++) {
                junkVal++;
            }

        }

        cap2.grab();

        cap2.retrieve(frame2);
        cap2.retrieve(frame2);

        if (frame2.empty()) {
            cerr << "Failed to capture frame from Camera 2\n";
            break;
        }
        // Process or display frame2 as needed
        imshow("Camera 2", frame2);
        if (waitKey(30) == 27) // Press Esc to exit
            break;

        nextCaptureClockTic += clockTicsPerTimeDiff;
    }
}


int main() {

    double desiredTimeBetweenCapSec = 5.0;

    long long clockTicsPerTimeDiff = (long long)round(desiredTimeBetweenCapSec * (double)std::chrono::system_clock::period::den / (double)std::chrono::system_clock::period::num);

    long long elaspsedTimeDiffPeriods = std::chrono::system_clock::now().time_since_epoch().count() / clockTicsPerTimeDiff;

    long long nextCaptureClockTic = (elaspsedTimeDiffPeriods + 1) * clockTicsPerTimeDiff;

    // Open two video captures for the cameras
    VideoCapture cap1(0); // Adjust the camera index as needed
    VideoCapture cap2(2); // Adjust the camera index as needed

    // Check if the cameras opened successfully
    if (!cap1.isOpened() || !cap2.isOpened()) {
        cerr << "Error opening cameras\n";
        return -1;
    }

    // Create threads for capturing frames
    thread thread1(captureCamera1, ref(cap1), clockTicsPerTimeDiff, nextCaptureClockTic);
    thread thread2(captureCamera2, ref(cap2), clockTicsPerTimeDiff, nextCaptureClockTic);

    // Wait for threads to finish
    thread1.join();
    thread2.join();

    // Release video captures
    cap1.release();
    cap2.release();

    destroyAllWindows();

    return 0;
}


//int main(int argc, char** argv)
//{
//    typedef std::chrono::high_resolution_clock Clock;
//
//    VideoCapture cap1;
//    VideoCapture cap2;
//
//    long long currSystemClock = 0;
//    long long prevSystemClock = 0;
//
//    // Desired image capture time diff
//    double imageCaptTimeDiffSec = 1.0;
//
//    double desiredTimeBetweenCapSec = 10.0;
//
//    long long clockTicsPerTimeDiff = (long long) round(desiredTimeBetweenCapSec * (double)std::chrono::system_clock::period::den / (double)std::chrono::system_clock::period::num);
//
//    long long elaspsedTimeDiffPeriods = std::chrono::system_clock::now().time_since_epoch().count() / clockTicsPerTimeDiff;
//
//    long long nextCaptureClockTic = (elaspsedTimeDiffPeriods + 1) * clockTicsPerTimeDiff;
//
//
//
//
//
//    //std::cout << std::chrono::system_clock::period::num << " / " << std::chrono::system_clock::period::den << std::endl;
//
//
//    
//    // open the default camera, use something different from 0 otherwise;
//    // Check VideoCapture documentation.
//    if (!cap1.open(0))
//        return 0;
//    if (!cap2.open(2))
//        return 0;
//    for (;;)
//    {
//
//        Mat frame1;
//        Mat frame2;
//
//
//        currSystemClock = std::chrono::system_clock::now().time_since_epoch().count();
//
//        while (std::chrono::system_clock::now().time_since_epoch().count() < nextCaptureClockTic) {
//            std::this_thread::sleep_for(100us);
//        }
//
//        long long preGrapSystemClock = std::chrono::system_clock::now().time_since_epoch().count();
//                
//        cap1.grab();
//        cap2.grab();
//        
//        long long postGrapSystemClock = std::chrono::system_clock::now().time_since_epoch().count();
//
//        nextCaptureClockTic += clockTicsPerTimeDiff;
//        
//        //Mat frame1;
//        cap1.retrieve(frame1);
//        cap1.retrieve(frame1);    
//        cap1.retrieve(frame1);
//        //Mat frame2;
//        cap2.retrieve(frame2);
//        cap2.retrieve(frame2);
//        cap1.retrieve(frame1);
//
//        long long postRetrieveSystemClock = std::chrono::system_clock::now().time_since_epoch().count();
//
//
//        long long grabTimeTics = postGrapSystemClock - preGrapSystemClock;
//
//        long long retrieveTimeTics = postRetrieveSystemClock - preGrapSystemClock;
//
//        //std::cout << std::chrono::system_clock::period::num << " / " << std::chrono::system_clock::period::den << std::endl;
//
//        std::cout << "Grab Time Tics :" << grabTimeTics << endl;
//
//        std::cout << "Retrieve Time Tics :" << retrieveTimeTics << endl;
//
//
//
//
//
//        
//        
//        //Mat frame1;
//        //cap1 >> frame1;
//        //Mat frame2;
//        //cap2 >> frame2;
//        if (frame1.empty()) break; // end of video stream
//        if (frame2.empty()) break;
//
//        imshow("Capture 1", frame1);
//        imshow("Capture 2", frame2);
//        if (waitKey(10) == 27) break; // stop capturing by pressing ESC 
//    }
//    // the camera will be closed automatically upon exit
//    // cap.close();
//    return 0;
//    
//    //std::string image_path = "starry_night.jpg";
//    //
//    //fstream my_file;
//    //my_file.open(image_path, ios::in);
//    //if (!my_file) {
//    //    cout << "File could not be opened!";
//    //}
//    //else {
//    //    cout << "File created successfully!";
//    //    my_file.close();
//    //}
//
//    //Mat image;
//    //image = imread(image_path, IMREAD_COLOR); // Read the file
//    //if (image.empty()) // Check for invalid input
//    //{
//    //    cout << "Could not open or find the image" << std::endl;
//    //    return -1;
//    //}
//    //namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
//    //imshow("Display window", image); // Show our image inside it.
//    //waitKey(0); // Wait for a keystroke in the window
//    //return 0;
//}
