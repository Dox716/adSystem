#include <stdio.h>
#include <stdlib.h>
#include "touch.h"
#include "lcd_bmp.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "appmp3.h"



int main()
{
	open_lcd();
	open_touch();
	int n;
	int x,y;
	show_bmp(0, 0, "./start.bmp");
	while(1)
	{
		get_xy(&x, &y);
	if(x > 57 && y > 252 && x < 232 && y < 354)n=1;
	else if(x > 480 && y > 247 && x < 683 && y < 343)n=2;
	if(n==1)music();
	else if(n==2)video();
	else printf("error\n");
	}
	close_lcd();
	return 0;
}