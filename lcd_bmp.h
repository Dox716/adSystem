#ifndef LCD_BMP_H
#define LCD_BMP_H

extern int *lcd_memory;
extern int lcd_fd;

// ��дһ������  �����������ʱ������x y���꣬�߶� ��� ������ɫ ���ڶ�Ӧ��λ����ʾ��Ӧ��ɫ�ľ���
void drwa_clolr(int x, int y, int width, int height ,int color);

/*****************************
	�������ܣ� ��lcd�豸
	
	����     �� ��
	����ֵ   ��
	
******************************/
int *open_lcd();
int show_bmp(int x, int y, char *pathname);
void close_lcd();

#endif //LCD_BMP_H


