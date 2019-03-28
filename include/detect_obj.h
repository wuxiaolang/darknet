#pragma once 

// #ifndef DETECT_OBJ_H
// #define DETECT_OBJ_H

extern "C"{
#include "darknet.h"
}

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv/highgui.h>

typedef struct {
    detection * dets;
    int nboxes ;
} detect_result ;

/*
use this class to detect the object from image(iplimage)
*/

class detect_obj {
public:
    explicit detect_obj();
    virtual  ~detect_obj();
    //load the trained yolo net 
    bool load_net(char *datacfg, char *cfgfile, char *weightfile, char *nameslist) ;
    // use the yolo net to detect the object before call this function, 
    //  you must called the load_net function 
    detect_result  to_detection(IplImage *_img ,float _nms , float _thresh, float _hier_thresh ) ; 

    
   /* detect_obj & operator = ( const detect_obj & _obj){
        if (&_obj ==this)
        {return *this;} };*/
protected:
    char **names ;
    image **alphabet ;
    network *net ;
    layer l_last ; 
};

// #endif