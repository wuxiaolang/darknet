# cpp 调用（YOLOv3_SpringEdition）
+ YOLOv3 Windows and Linux DLL library with CMAKE：https://github.com/springkim/YOLOv3_SpringEdition 
+ 编译的时候一个小警告
  ```cpp
  /home/wu/code/ORB_yolo/YOLOv3SE.h: In constructor ‘BoxSE::BoxSE(int, float, int, int, int, int, std::__cxx11::string)’:
  /home/wu/code/ORB_yolo/YOLOv3SE.h:49:44: warning: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
     char* lb[5] = { "th","st","nd","rd","th" };
                                              ^
  /home/wu/code/ORB_yolo/YOLOv3SE.h:49:44: warning: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
  /home/wu/code/ORB_yolo/YOLOv3SE.h:49:44: warning: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
  /home/wu/code/ORB_yolo/YOLOv3SE.h:49:44: warning: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
  /home/wu/code/ORB_yolo/YOLOv3SE.h:49:44: warning: ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
  ```
  + 解决：将 `char* lb[5] = { "th","st","nd","rd","th" };` 改成 `char const *lb[5] = { "th","st","nd","rd","th" };`
