# YOLO 批量处理 TUM、KITTI 数据集并保存检测结果

![](https://github.com/wuxiaolang/darknet/blob/master/gif/yolo_tum.gif?raw=true)

## 0. 主要工作：

+ 在 [**darknet.c**](https://github.com/wuxiaolang/darknet/blob/master/examples/darknet.c?1552372879559) 中添加了 `detect_tum_batch` 命令处理 **tum 和自制数据集**，添加 `detect_kitti_batch` 命令处理 **kitti 数据集**；
+ 在 [**detector.c**](https://github.com/wuxiaolang/darknet/blob/master/examples/detector.c?1552372948327) 中添加了**读取数据集图像**的函数 `test_detector_tum_batch()` 和 `test_detector_kitti_batch()`；
+ 在 [**image.c**](https://github.com/wuxiaolang/darknet/blob/master/src/image.c?1552373025166) 中添加了绘制与**保存结果**（txt 文件和绘制检测框的图像）的函数 `draw_save_detections()`。
+ 代码：[**https://github.com/wuxiaolang/darknet**](https://github.com/wuxiaolang/darknet)

---

## 1. 指令

### 1.1 **TUM 数据集**    
+ 指令：
```
./darknet detect_tum_batch [path_of_cfg] [path_of_weight] [path_of_dataset] [output_folder] [-thresh thresh]
```
+ 例如：
```
./darknet detect_tum_batch cfg/yolov3.cfg yolov3.weights /home/wu/data/dataset/rgbd_dataset_freiburg1_desk/ /home/wu/data/ -thresh 0.4
```
+ **注意**：请在 [output_folder] 下创建 `yolo_imgs` 和 `yolo_txts` 文件夹来存放绘制了检测框的图片和检测框 txt 信息。

### 1.2 **KITTI 数据集**    

+ 指令：
```
./darknet detect_kitti_batch [path_of_cfg] [path_of_weight] [path_of_dataset] [output_folder] [-thresh thresh]
```
&emsp;&emsp;例如：
```
./darknet detect_kitti_batch cfg/yolov3.cfg yolov3.weights /home/wu/data/dataset/kitti/color/07/ /home/wu/data/ -thresh 0.4
```

+ **注意**：
    + ① 请在 [output_folder] 下创建 `yolo_imgs` 和 `yolo_txts` 文件夹来存放绘制了检测框的图片和检测框 txt 信息；
    + ② 在 `test_detector_kitti_batch()` 函数中默认**采用的是 `image_2` kitti 彩色数据集**，如果使用 gray 数据集，可以将 `image_2` 改成 `image_0` 或 `image_1`。
+ **其他数据集**：可仿照改动的函数写。

---

## 2. 结果保存

### 2.1 txt 文件存储的内容

+ **以下所有的输出格式、内容可以在 `detector.c` 的 `test_detector_tum_batch()` 函数中修改。**
+ 输出的图片保存在 `output_folder/yolo_imgs` 路径下，文件名为：`[时间戳].jpg`，例如 `1905140001.223000.jpg`；
+ 输出的 txt 文件保存在 `output_folder/yolo_txts` 路径下，文件名为：`[时间戳].txt`，例如 `1905140001.223000.txt`；
+ **txt 保存格式**：类别 ID &emsp; 左上角.x &emsp; 左上角.y &emsp; 长 &emsp; 宽 &emsp; 置信度
    ```
    66   70    294   260   185    0.794691
    64   255   258   63     38    0.813716
    62   224   0     243   234    0.610995
    ```

### 2.2 输出文件的文件名

+ 在 **TUM 数据集**中，由于数据集图像是根据时间戳命名的，且 rgb.txt 中存储的也是时间戳，所以我将输出文件的文件名也由时间戳命名，例如：`1905140001.223000.jpg` 和 `1905140001.223000.txt`。
+ **KITTI 数据集**有图像是按序号命名的 `000001.png`，在 `times.txt` 文件中保存的是时间戳 `1.038752e-01`，所以在 KITTI 数据集处理函数中我写了两种存储方式：
    + **第一种是按序号命名**（默认情况），结果保存为：`000001.jpg` 和 `000001.txt`；
    + **第二种是按照时间戳命名**，结果保存为：`0.10387.jpg` 和 `0.10387.txt`；
    + 可在 `test_detector_kitti_batch()` 函数中选择
        ```cpp
        // 【方法 ①】： 以序号命名
        printf("文件序号： %06d\n", num);
        sprintf(output_file_name, "%06d", num);
        // // 【方法 ②】： 以时间戳命名
        // // 逐行读取 txt 文件的时间戳：1.036224e-01.
		// memset(szTest, 0, sizeof(szTest));
		// fgets(szTest, sizeof(szTest) - 1, fp_rgb_txt); // 包含了换行符
        // strncpy(output_file_name, szTest, 12);
        // // 将时间戳转换成十进制
        // double tmp_name = strtod(output_file_name, NULL);   // note strtod() 转换成 lf 十进制类型.
        // // 保留 5 位小数.
        // sprintf(output_file_name, "%.5lf", tmp_name);
        ```

---

## YOLO
+ 官网：https://pjreddie.com/darknet/yolo/
+ github：https://github.com/pjreddie/darknet

---
> 2019.03.11    
wuyanminmax@gmail.com
