/**
 * @file test_baft.cpp
 * @brief Main program for testing BAFT
 * @date Nov 27, 2014
 * @author Jonas T. Arnfred
 */

#include "./src/utils.h"
#include "./src/baft.h"

// System
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;

/* ************************************************************************* */
int main(int argc, char *argv[]) {

  cv::Mat img;

  if (argc != 2) {
    cerr << "Error introducing input arguments!" << endl;
    cerr << "The format needs to be: ./test_baft img" << endl;
    return -1;
  }

  string imgFile = argv[1];

  // Open the input image
  img = imread(imgFile, 1);

  // Create KAZE object
  Ptr<Feature2D> dbaft = BAFT::create();

  // Timing information
  double t1 = 0.0, t2 = 0.0;
  double takaze = 0.0;

  // Detect BAFT features in the input image
  vector<cv::KeyPoint> kpts;
  cv::Mat desc;

  t1 = cv::getTickCount();
  dbaft->detectAndCompute(img, cv::noArray(), kpts, desc, false);
  t2 = cv::getTickCount();
  takaze = 1000.0*(t2-t1) / cv::getTickFrequency();

  draw_keypoints(img, kpts);

  // Show the detected BAFT features
  cv::imshow("BAFT", img);
  cv::waitKey(0);

  int nr_kpts = kpts.size();

  cout << "BAFT Results" << endl;
  cout << "********************" << endl;
  cout << "# Keypoints:    \t" << nr_kpts << endl;
  cout << "Time (ms):      \t" << takaze << endl;
  cout << endl;

  return 0;
}

