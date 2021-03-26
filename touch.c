#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdio.h>

static int touch_fd;

//打开触摸屏
int open_touch()
{
	
	touch_fd = open("/dev/input/event0", O_RDWR);
	if(touch_fd == -1)
	{
		perror("open touch error");
		return -1;
	}
	
	return 0;
}


//获取一对坐标
int get_xy(int *x, int *y)
{
	int pressure;
	struct input_event events;
	while(1)
	{
		read(touch_fd, &events, sizeof(events));
		if(events.type == EV_ABS)
		{
			if(events.code == ABS_X)
				*x = events.value*800/1024;//*x=events.value
			if(events.code == ABS_Y)
				*y = events.value*480/600;//*y=events.value
			/* if(events.code == ABS_PRESSURE)
			{
				pressure = events.value;
				if(pressure == 0) //手松开
				{
					printf("x = %d, y = %d\n", x, y);
				}
			} */
		}
		if(events.type == EV_KEY)
		{
			if(events.code == BTN_TOUCH)
			{	
				pressure = events.value;
				if(pressure == 0) //手松开
				{
					printf("x = %d, y = %d\n", *x, *y);
					return 0;
				}
			}
				
		}	
	}
		
}

//关闭触摸屏
void close_touch()
{
	close(touch_fd);
}

