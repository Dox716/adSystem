#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

int *lcd_memory;
int lcd_fd;


// 编写一个函数  调用这个函数时，传入x y坐标，高度 宽度 传入颜色 ，在对应的位置显示对应颜色的矩形
void drwa_clolr(int x, int y, int width, int height ,int color)
{
	int i,j;
	for(i=y; i<y+height;i++)
	{
		for(j = x; j < x+width; j++)
		{
			*(lcd_memory+i*800+j) = color; //颜色RGB值
		}
	}
	
}



/*****************************
	函数功能： 打开lcd设备
	
	参数     ： 无
	返回值   ：
	
******************************/
int *open_lcd()
{
	//1打开当前目录的a.txt  
	lcd_fd = open("/dev/fb0", O_RDWR);
	if(lcd_fd == -1)
	{
		perror("open a.txt error");
		return (void *)-1;
	}
	//1作映射
	lcd_memory = mmap(	NULL, 		//由系统自动分配空间
						800*480*4,	//映射空间大小
						PROT_READ|PROT_WRITE,//权限为可读可写
						MAP_SHARED,	//作为共享内存使用
						lcd_fd, 	//lcd有效文件描述符
						0);			//偏移量 
	
	
	if(lcd_memory == MAP_FAILED)
	{
		perror("map error");
		return (void *)-1;
	}
	
	return lcd_memory;
	
}


int show_bmp(int x, int y, char *pathname)
{
	int buf[800*480] = {0};
	int i = 0, j = 0;
	char bmpinforn[54] = {0};
	char bmpdata[800*480*4] = {0};
	char *p = bmpdata;
	char blue, red, green;
	int color = 0;
	int bmpwidth, bmpheight;
	int x_end, y_end;
	
			
	//2 打开图片
	int bmp_fd = open(pathname, O_RDONLY);
	if(bmp_fd == -1)
	{
		perror("open pig.bmp error");
		return -1;
	}
	
	//3读取属性信息
	read(bmp_fd, bmpinforn, 54);
	bmpwidth = bmpinforn[18] | bmpinforn[19] << 8;
	bmpheight = bmpinforn[22] | bmpinforn[23] << 8;
	
	printf("width=%d\nheight=%d\n", bmpwidth, bmpheight);
	
	x_end = x + bmpwidth;
	y_end = y + bmpheight-1;
	if(x_end > 800 || y_end >= 480)
	{
		printf("坐标位置不符或者图过大\n");
		return -1;
	}
	

	//4读取颜色数据
	read(bmp_fd, bmpdata, 800*480*4);
	
	//5整理颜色
	for(i = y_end; i >= y; i--)
	{	for(j = x; j < x_end; j++)  //描述显示屏像素位置
		{
			blue  = *p++;
			green = *p++;
			red   = *p++;
			
			color = blue << 0 | green << 8 | red << 16;
			//6写到lcd_memory
			*(lcd_memory+i*800+j) = color; //颜色RGB值
		}
	}	
	

	//7关闭文件
	close(bmp_fd);
	
}

void close_lcd()
{
	//取消映射
	munmap(lcd_memory, 800*480*4);
	//关闭lcd
	close(lcd_fd);
	
}




