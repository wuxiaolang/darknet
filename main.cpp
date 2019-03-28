extern "C"{
#include "darknet.h"
}

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "opencv2/opencv.hpp" 
#include <opencv/highgui.h>
#include "detect_obj.h"

void video_test() ; 

int main(int argc,char **argv)
{
    std::cout << "111" << std::endl;
    video_test();
    return 0 ;    
}
//use this function to process video for detecting object
void video_test()
{
    std::cout << "222" << std::endl;
    detect_obj * detect_yolo = new detect_obj();

    detect_yolo->load_net("/home/wu/code/YoloTest/darknet/cfg/coco.data",
       "/home/wu/code/YoloTest/darknet/cfg/yolov3-tiny.cfg", "/home/wu/code/YoloTest/darknet/yolov3-tiny.weights", 
       "/home/wu/code/YoloTest/darknet/data/coco.names");

    // if(detect_yolo->load_net("/home/wu/soft/darknet/cfg/coco.data", \
    //   "/home/wu/soft/darknet/cfg/yolov2.cfg", "/home/wu/soft/darknet/yolov2.weights",\
    //   "/home/wu/soft/darknet/data/coco.names")) 
    //     return ;

    std::cout << "333" << std::endl;
    
    // CvCapture * capture = cvCreateFileCapture("/home/wu/Videos/tum_raw.mp4");
    // IplImage * frame ;
    // unsigned short count = 0 ;
    // while (1){
    //     count ++ ;

    //    frame = cvQueryFrame(capture);
    //    if (count%3==0)
    //    {
    //         detect_result result = detect_yolo->to_detection(frame,0.45,0.5,0.5) ; 
    //         free_detections(result.dets, result.nboxes);
    //    }
    //   // char c = cvWaitKey(33);
    //    //if(c==27) break ;
    // }

    cv::Mat img = cv::imread ( "/home/wu/code/YoloTest/1.png", CV_LOAD_IMAGE_COLOR );
    IplImage* frame = new IplImage(img);

    detect_result result = detect_yolo->to_detection(frame,0.45,0.5,0.5) ; 

    // NOTE result.dets 包括了检测结果：类别，置信度和检测框位置（box b = dets[i].bbox;）


    free_detections(result.dets, result.nboxes);

    //cvReleaseCapture(&capture);
}