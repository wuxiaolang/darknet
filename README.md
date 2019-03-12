# YOLO 批量处理数据集并保存检测结果
## 0. 主要工作：
+ 在 `darknet.c` 中添加了 `detect_tum_batch` 命令；
+ 在 `detector.c` 中添加了读取数据集图片的函数 `test_detector_tum_batch()`；
+ 在 `image.c` 中添加了绘制与保存结果的函数 `draw_save_detections()`。
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
&emsp;&emsp;注意：请在 [output_folder] 下创建 `yolo_img` 和 `yolo_txt` 文件夹来存放绘制了检测框的图片和检测框 txt 信息。

+ **其他数据集**：可仿照下面的函数写，后续用到的时候再添加其他数据集命令。

## 2. 结果
+ 输出的图片保存在 `output_folder/yolo_img` 路径下；
+ 输出的图片保存在 `output_folder/yolo_txt` 路径下；
+ txt 保存格式（可修改）：类别  左上角.x 左上角.y 长 宽 置信度
```
    book	450	110	189	253	0.50
keyboard	70	294	260	185	0.79
    mouse	255	258	63	38	0.81
    laptop	3	46	238	310	0.41
tvmonitor	224	0	243	234	0.61
```
## YOLO
+ 官网：https://pjreddie.com/darknet/yolo/
+ github：https://github.com/pjreddie/darknet

---
> 2019.03.11    
wuyanminmax@gmail.com
