#include "detect_obj.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern "C"{
#include "darknet.h"
}

detect_obj::detect_obj()
{
    //initilizing the member variable
    names = nullptr  ;
    alphabet =NULL;
    net = NULL ; 
    //make_window("predictions", 512, 512, 0);
}
detect_obj::~detect_obj()
{   
    if(*names) delete *names;
    if (names) delete names ;
    if (*alphabet) delete *alphabet ;
    if (alphabet) delete alphabet ;
    if (net) delete net ;
}
/*****************************************************
name:bool detect_obj::load_net(char *datacfg, char *cfgfile, char *weightfile,char * nameslist)

input:
datacfg the info about data
cfgfile the architecture of model 
weightfile the parameters of the model 
nameslist the classes of data 

output:
bool if load the net correctly return true ,otherwise return false

function:load the network of yolo 
*********************************************************/
bool detect_obj::load_net(char *datacfg, char *cfgfile, char *weightfile, char *nameslist)
{
    //printf("222111\n");
    list *options = read_data_cfg( datacfg ) ; 
    // char *name_list = option_find_str(options,"names","data/names.list");
    char *name_list = "/home/wu/soft/darknet/data/coco.names";
    //printf("222222\n");
    names = get_labels(name_list) ;         // 读取有问题,可修改 coco.data 中的路径，或者直接赋值.
    //printf("222333\n");
    alphabet = load_alphabet();             // 加载字符有问题，在 load_alphabet 函数中指定字符路径.
    //printf("222444\n");
    net = load_network(cfgfile, weightfile, 0);
    //printf("222555\n");
    set_batch_network(net,1);
    //printf("222666\n");
    srand(2222222);
    // TODO 使用自己在 network.c 中定义的 get_layer 函数会出现 Segmentation fault (core dumped) 的问题.
    //l_last = get_layer(net, net->n-1);
    //printf("l_last:%d\n", net->layers[23].classes);
    // TODO 直接获取各层信息，无法获取，输出均为 0.
    l_last = net->layers[net->n-1] ; 
    printf("l_last: %d\n", l_last.classes);
    return true ;
}
/*****************************************************
name:bool detect_obj::to_detection(IplImage *_img,float _nms , float _thresh, float _hier_thresh )

input:
IplImage the image used to detect the object 
_nms if not zero ,will use this value to do nms operation
_thresh  the thresh of whether object or not 
_hier_thresh the same meaning with thresh ,i am not comprehensize 

output:
detect_result the object boxes and the classes ,the numbers of boxes

function:use the yolo model to detect object in object ,you must call net_load 
before call this function
*********************************************************/
detect_result detect_obj::to_detection(IplImage *_img,float _nms , float _thresh, float _hier_thresh )
{
    // int h = _img->height ;
    // int w = _img->width ;
    // int c = _img->nChannels ;
    // image im = make_image(w,h,c) ; 
    // unsigned char *data = (unsigned char *)_img->imageData ;

    // int step = _img->widthStep;

    // int i,j,k;
    // for (i = 0 ;i<h;++i){
    //     for(k=0;k<c;++k){
    //         for(j=0;j<w;++j){
    //             im.data[k*w*h+i*w + j] = data[i*step + j*c + k]/255. ;  
    //         }
    //     }
    // }

    image im = load_image_color("/home/wu/code/YoloTest/tum.png",0,0);

    image sized = letterbox_image(im ,net->w,net->h) ; 

    double time ; 
    float *X = sized.data ;
    time = what_time_is_it_now();
    network_predict(net,X);
    printf("Predicted in %f seconds.\n",what_time_is_it_now()-time) ; 

    int nboxes = 0 ;

    detection *dets = get_network_boxes(net,
                                        im.w,im.h,
                                        _thresh,
                                        _hier_thresh,
                                        0,1,
                                        &nboxes);
    printf("nboxes:%d\n", nboxes);

    // TODO 这里手动将 l_last.classes 用 80 代替.
    //if(_nms) do_nms_sort(dets,nboxes,l_last.classes,_nms);
    if(_nms) do_nms_sort(dets,nboxes,80 ,_nms);

    // 保存结果.
    detect_result result ;
    result.dets = dets ;
    result.nboxes = nboxes ;

    //for test
    // draw_detections(im, 
    //                 dets, 
    //                 nboxes, 
    //                 _thresh, 
    //                 names, 
    //                 alphabet, 
    //                 l_last.classes);
    
    // TODO 手动将 l_last.classes 用 80 代替.
    draw_detections(im, 
                    dets, 
                    nboxes, 
                    _thresh, 
                    names, 
                    alphabet, 
                    80);

    save_image(im, "/home/wu/code/YoloTest/predictions");
    
    //show_image(im, "predictions");
    free_image(im) ;
    free_image(sized) ; 
    //for test end 
    return result ;
}
