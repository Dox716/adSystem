#ifndef LCD_BMP_H
#define LCD_BMP_H

extern int *lcd_memory;
extern int lcd_fd;

// 编写一个函数  调用这个函数时，传入x y坐标，高度 宽度 传入颜色 ，在对应的位置显示对应颜色的矩形
void drwa_clolr(int x, int y, int width, int height ,int color);

/*****************************
	函数功能： 打开lcd设备
	
	参数     ： 无
	返回值   ：
	
******************************/
int *open_lcd();
int show_bmp(int x, int y, char *pathname);
void close_lcd();

#endif //LCD_BMP_H


