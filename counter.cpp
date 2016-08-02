//This program outputs the number of faces detected on an image
//It receives the path to an image as a command line argument
//Will print on the standard output the number of faces detected
//Will return 0 if at least 1 face is detected
//Will return 1 if no faces are detected
//Will return 2 if some system call fails

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

int main( int argc, char **argv )
{

  if(argc != 2)
  {
    std::cerr << "USE: " << argv[0] << " path-to-image" << std::endl;
    return 2;
  }
std::string faceCascadeName = "/usr/share/opencv/lbpcascades/lbpcascade_frontalface.xml";
  
cv::CascadeClassifier faceCascade;
  //Load the classifiers
  if (!faceCascade.load( faceCascadeName ))
  {
    std::cerr << "Could not load face classifier" << std::endl;
    return 2; 
  }


  //The captured frame
  cv::Mat frame;
  frame = cv::imread(argv[1]);
  if(frame.empty())
  {
    std::cerr << "Could not load image " << argv[1] << std::endl;
    return 2;
  }

  //This will contain the output of the face detector
  std::vector<cv::Rect> faces;

  //Preprocess the image
  cv::Mat frameGray;
  cv::cvtColor( frame, frameGray, CV_BGR2GRAY );
  cv::equalizeHist( frameGray, frameGray );

  //Detect the face
  faceCascade.detectMultiScale( frameGray, faces, 1.1, 2, 0, cv::Size(80,80));

  std::cout << "{\"count\":\""<<faces.size()<<"\"}";

  //If no faces are detected return 1
	//  if (faces.size() == 0) return 1;

  //Number of detected faces was greater than 0.
  return 0;
  
}
