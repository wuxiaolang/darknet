# YOLO 批量处理数据集并保存检测结果
![](https://github.com/wuxiaolang/darknet/blob/master/gif/yolo_tum.gif?raw=true)
## 0. 主要工作：
+ 在 [**darknet.c**](https://github.com/wuxiaolang/darknet/blob/master/examples/darknet.c?1552372879559) 中添加了 `detect_tum_batch` 命令；
+ 在 [**detector.c**](https://github.com/wuxiaolang/darknet/blob/master/examples/detector.c?1552372948327) 中添加了**读取数据集图片**的函数 `test_detector_tum_batch()`；
+ 在 [**image.c**](https://github.com/wuxiaolang/darknet/blob/master/src/image.c?1552373025166) 中添加了绘制与**保存结果**的函数 `draw_save_detections()`。
+ 代码：[**https://github.com/wuxiaolang/darknet**](https://github.com/wuxiaolang/darknet)

## 1. 指令与效果
+ **TUM 数据集**    
指令：
```
./darknet detect_tum_batch [path_of_cfg] [path_of_weight] [path_of_dataset] [output_folder] [-thresh thresh]
```
&emsp;&emsp;例如：
```
./darknet detect_tum_batch cfg/yolov3.cfg yolov3.weights /home/wu/data/dataset/rgbd_dataset_freiburg1_desk/ /home/wu/data/ -thresh 0.4
```
&emsp;&emsp;注意：请在 [output_folder] 下创建 `yolo_imgs` 和 `yolo_txts` 文件夹来存放绘制了检测框的图片和检测框 txt 信息。

+ **其他数据集**：可仿照改动的函数写，后续用到的时候再添加其他数据集命令。

## 2. 结果
+ **以下所有的输出格式、内容可以在 `detector.c` 的 `test_detector_tum_batch()` 函数中修改。**
+ 输出的图片保存在 `output_folder/yolo_imgs` 路径下，文件名为：`[时间戳].jpg`，例如 `1905140001.223000.jpg`；
+ 输出的 txt 文件保存在 `output_folder/yolo_txts` 路径下，文件名为：`[时间戳].txt`，例如 `1905140001.223000.txt`；
+ txt 保存格式：类别 ID &emsp; 左上角.x &emsp; 左上角.y &emsp; 长 &emsp; 宽 &emsp; 置信度
    ```
    66   70    294   260   185    0.794691
    64   255   258   63     38    0.813716
    62   224   0     243   234    0.610995
    ```

## YOLO
+ 官网：https://pjreddie.com/darknet/yolo/
+ github：https://github.com/pjreddie/darknet

---
> 2019.03.11    
wuyanminmax@gmail.com

