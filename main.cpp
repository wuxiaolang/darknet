#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "YOLOv3SE.h"

using namespace std;
using namespace cv;

void Yolo3Test(std::string imgfile_, std::string cfgfile_, std::string weightfile_, std::string nameslist_);

int main ( int argc, char** argv )
{
    // if ( argc != 3 )
    // {
    //     cout<<"usage: feature_extraction img1 img2"<<endl;
    //     return 1;
    // }

    //-- 读取图像
    cv::Mat img_1 = imread ( "/home/wu/code/YoloTest/1.png", CV_LOAD_IMAGE_COLOR );
    cv::Mat img_2 = imread ( "/home/wu/code/YoloTest/2.png", CV_LOAD_IMAGE_COLOR );

    cv::imshow ( "原图", img_1 );
    //cv::waitKey(100);

    // 加载文件.
    string imgfile = "/home/wu/code/YoloTest/tum.png";
    string datacfg = "/home/wu/soft/darknet/cfg/coco.data";
    string cfgfile = "/home/wu/soft/darknet/cfg/yolov3.cfg";
    string weightfile = "/home/wu/soft/darknet/yolov3.weights";
    string nameslist = "/home/wu/soft/darknet/data/coco.names";

    Yolo3Test(imgfile, cfgfile, weightfile, nameslist);

    return 0;
}

void Yolo3Test(std::string imgfile_, std::string cfgfile_, std::string weightfile_, std::string nameslist_)
{
	YOLOv3 detector;
    // 加载网络.
    detector.Create(weightfile_, cfgfile_, nameslist_);
	//detector.Create("/home/wu/soft/darknet/yolov2.weights", "/home/wu/soft/darknet/cfg/yolov2.cfg", "/home/wu/soft/darknet/data/coco.names");
	//detector.Create("darknet53_416_random_10000.weights", "darknet53_voc.cfg", "voc2007.names");
	//detector.Create("darknet19.weights", "darknet19.cfg", "voc2007.names");

    // 产生类别颜色.
	std::vector<cv::Scalar> colors;
	for (int i = 0; i < 80; i++)
        colors.push_back(cv::Scalar(rand() % 256, rand() % 256, rand() % 256));
		//colors.push_back(cv::Scalar(rand() % 127 + 128, rand() % 127 + 128, rand() % 127 + 128));

    // 加载待处理的图像.
    cv::Mat img = cv::imread(imgfile_);
	
    // 进行检测.
    double start = clock();
	auto boxes = detector.Detect(img, 0.5F);            // 传入 opencv 格式的图像.
    //auto boxes = detector.Detect(imgfile_, 0.5F);     // 传入图像路径.
	double t = (clock() - start) / CLOCKS_PER_SEC;
    std::cout << "FPS : " << 1.0 / t << "\t" << t << std::endl;

    // 绘制结果.
	for (auto&box : boxes) 
    {
		cv::putText(img,                            /* 目标图像 */
                    detector.Names(box.m_class),    /* 文字内容 */
                    box.tl(),                       /* 检测框左上角位置（文字左下角的位置） */
                    cv::FONT_HERSHEY_DUPLEX  ,      /* 字体 */
                    1.0,                            /* 大小 */
                    colors[box.m_class],            /* 类别颜色 */
                    2);                             /* 粗细 */
		cv::rectangle(  img,                        /* 目标图像 */
                        box,                        /* 框 */
                        colors[box.m_class],        /* 类别颜色 */
                        2);                         /* 粗细 */

        // NOTE 检测信息.
        std::cout << detector.Names(box.m_class) << " " << box.m_class << " " << box.x << " " << box.y << " " 
                  << box.width << " " << box.height << " " << std::endl;
        /**
         * keyboard  66 199 257 193 51 
         * mouse     64 377 320 31 39 
         * cup       41 442 293 51 63 
         * tvmonitor 62 232 93 156 141 
         * remote    65 44 260 38 57
         */
	}
    cv::imwrite("original.jpg", img);

    cv::imshow("frame", img);
    cv::waitKey(0);
	cv::destroyAllWindows();
    detector.Release();
}