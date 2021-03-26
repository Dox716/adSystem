#include <stdio.h>
#include <stdlib.h>
#include "touch.h"
#include "lcd_bmp.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define RUN   0
#define STOP  1
#define PAUSE 2

int searchmp3_video(char *dirpaht,char buf[][64],char *types);
char mp3mame[100][64] = {0};
char videomame[100][64] = {0};  //  "./muisc/xxx.mp3"

int music_states;


int music()
{ //����ǰ���ŵĸ���λ��
    int i=0;
	music_states = STOP;
	char cmd[128] = {0};
	int music_total = searchmp3_video(".",mp3mame,".mp3");
	printf("music_total=%d\n",music_total);
	int x,y;
	//��ʾ����������
	show_bmp(0, 0, "./maininterface.bmp");
	
	while(1)
	{
		get_xy(&x, &y);
		if(x > 15 && y > 440 && x < 106 && y < 478 && music_states == STOP)
		{
			//���Ÿ���
			printf("����\n");
			sprintf(cmd, "mplayer %s &", mp3mame[i]); //����ض���
			system(cmd);
			music_states = RUN;
			continue;
		}
		if(x > 578 && y > 440 && x < 673 && y < 478)
		{
			//��һ��
			printf("��һ��\n");
			system("killall -9 mplayer");
			if(i == music_total-1)
			{
				i = -1; // �ص���0�׸�
			}
			sprintf(cmd, "mplayer %s &", mp3mame[++i]); //����ض���
			system(cmd);
			music_states = RUN;
			continue;
		}
		if(x > 464 && y > 440 && x < 561 && y < 478)
		{
			//��һ��
			printf("��һ��\n");
			system("killall -9 mplayer");
			if(i == 0)
			{
				i = music_total; // �ص���0�׸�
			}
			sprintf(cmd, "mplayer %s &", mp3mame[--i]); //����ض���
			system(cmd);
			music_states = RUN;
			continue;
		}
		if(x > 242 && y > 440 && x < 333 && y < 478 && music_states == RUN)
		{
			//��ͣ
			printf("��ͣ\n");
			system("killall -19 mplayer");
			music_states = PAUSE;
			continue;
		}
		if(x > 352 && y > 440 && x < 445 && y < 478 && music_states == PAUSE)
		{
			//����
			printf("����\n");
			system("killall -18 mplayer");
			music_states = RUN;
			continue;
		}
		if(x > 127 && y > 440 && x < 222 && y < 478)
		{
			//�˳�
			printf("����\n");
			system("killall -9 mplayer");
			music_states = STOP;
			return 0;
		}
	}
}

int video()
{ //����ǰ���ŵĸ���λ��
    int j=0; 
	music_states = STOP;
	char cmd[128] = {0};
	int video_total = searchmp3_video(".",videomame,".avi");
	printf("video_total=%d\n",video_total);
	int x,y;
	//��ʾ����������
	show_bmp(0, 0, "./maininterface.bmp");
	
	while(1)
	{
		get_xy(&x, &y);
		if(x > 15 && y > 440 && x < 106 && y < 478 && music_states == STOP)
		{
			//���Ÿ���
			printf("����\n");
			sprintf(cmd, "./mplayer -quiet -geometry 11:8 -zoom -x 660 -y 410 %s &",videomame[j]); //����ض���
			system(cmd);
			music_states = RUN;
			continue;
		}
		if(x > 578 && y > 440 && x < 673 && y < 478)
		{
			//��һ��
			printf("��һ��\n");
			system("killall -9 maplayer");
			if(j == video_total-1)
			{
				j = -1; // �ص���0�׸�
			}
			sprintf(cmd, "./mplayer -quiet -geometry 11:8 -zoom -x 660 -y 410 %s &",videomame[++j]); //����ض���
			system(cmd);
			music_states = RUN;
			continue;
		}
		if(x > 464 && y > 440 && x < 561 && y < 478)
		{
			//��һ��
			printf("��һ��\n");
			system("killall -9 mplayer");
			if(j == 0)
			{
				j = video_total; // �ص���0�׸�
			}
			sprintf(cmd, "./mplayer -quiet -geometry 11:8 -zoom -x 660 -y 410 %s &",videomame[--j]); //����ض���
			system(cmd);
			music_states = RUN;
			continue;
		}
		if(x > 242 && y > 440 && x < 333 && y < 478 && music_states == RUN)
		{
			//��ͣ
			printf("��ͣ\n");
			system("killall -19 mplayer");
			music_states = PAUSE;
			continue;
		}
		if(x > 352 && y > 440 && x < 445 && y < 478 && music_states == PAUSE)
		{
			//����
			printf("����\n");
			system("killall -18 mplayer");
			music_states = RUN;
			continue;
		}
		if(x > 127 && y > 440 && x < 222 && y < 478)
		{
			//�˳�
			printf("����\n");
			system("killall -9 mplayer");
			music_states = STOP;
			return 0;
		}
	}
}

//�������ֺ���Ƶ
int searchmp3_video(char *dirpaht,char buf[][64],char *types)
{
	struct dirent *ep;
	int i = 0;
	int j = 0;
	DIR *dp = opendir(dirpaht);
	if(dp == NULL)
	{
		perror("open dir error");
		return -1;
	}
	
	while((ep = readdir(dp)) !=NULL)
	{
		if((strstr(ep->d_name, types)) != NULL)
		{
		sprintf(buf[i++], "%s/%s", dirpaht, ep->d_name);
		printf("%s\t", buf[i-1]);
		}
	}
       return i;
}
