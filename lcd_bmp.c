#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

int *lcd_memory;
int lcd_fd;


// ��дһ������  �����������ʱ������x y���꣬�߶� ��� ������ɫ ���ڶ�Ӧ��λ����ʾ��Ӧ��ɫ�ľ���
void drwa_clolr(int x, int y, int width, int height ,int color)
{
	int i,j;
	for(i=y; i<y+height;i++)
	{
		for(j = x; j < x+width; j++)
		{
			*(lcd_memory+i*800+j) = color; //��ɫRGBֵ
		}
	}
	
}



/*****************************
	�������ܣ� ��lcd�豸
	
	����     �� ��
	����ֵ   ��
	
******************************/
int *open_lcd()
{
	//1�򿪵�ǰĿ¼��a.txt  
	lcd_fd = open("/dev/fb0", O_RDWR);
	if(lcd_fd == -1)
	{
		perror("open a.txt error");
		return (void *)-1;
	}
	//1��ӳ��
	lcd_memory = mmap(	NULL, 		//��ϵͳ�Զ�����ռ�
						800*480*4,	//ӳ��ռ��С
						PROT_READ|PROT_WRITE,//Ȩ��Ϊ�ɶ���д
						MAP_SHARED,	//��Ϊ�����ڴ�ʹ��
						lcd_fd, 	//lcd��Ч�ļ�������
						0);			//ƫ���� 
	
	
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
	
			
	//2 ��ͼƬ
	int bmp_fd = open(pathname, O_RDONLY);
	if(bmp_fd == -1)
	{
		perror("open pig.bmp error");
		return -1;
	}
	
	//3��ȡ������Ϣ
	read(bmp_fd, bmpinforn, 54);
	bmpwidth = bmpinforn[18] | bmpinforn[19] << 8;
	bmpheight = bmpinforn[22] | bmpinforn[23] << 8;
	
	printf("width=%d\nheight=%d\n", bmpwidth, bmpheight);
	
	x_end = x + bmpwidth;
	y_end = y + bmpheight-1;
	if(x_end > 800 || y_end >= 480)
	{
		printf("����λ�ò�������ͼ����\n");
		return -1;
	}
	

	//4��ȡ��ɫ����
	read(bmp_fd, bmpdata, 800*480*4);
	
	//5������ɫ
	for(i = y_end; i >= y; i--)
	{	for(j = x; j < x_end; j++)  //������ʾ������λ��
		{
			blue  = *p++;
			green = *p++;
			red   = *p++;
			
			color = blue << 0 | green << 8 | red << 16;
			//6д��lcd_memory
			*(lcd_memory+i*800+j) = color; //��ɫRGBֵ
		}
	}	
	

	//7�ر��ļ�
	close(bmp_fd);
	
}

void close_lcd()
{
	//ȡ��ӳ��
	munmap(lcd_memory, 800*480*4);
	//�ر�lcd
	close(lcd_fd);
	
}




