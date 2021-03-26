#ifndef TOUCH_H
#define TOUCH_H

//打开触摸屏
int open_touch();


//获取一对坐标
int get_xy(int *x, int *y);


//关闭触摸屏
void close_touch();


#endif //TOUCH_H