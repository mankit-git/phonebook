#include "head.h"
#include "show.h"

sqlite3 *db; 

int touch(int ts, struct coordinate *xyp)
{	
	struct input_event buf;
	bzero(&buf, sizeof(buf));
	while(1)
	{
		read(ts, &buf, sizeof(buf));
		if(buf.type == EV_ABS)
		{
			if(buf.code == ABS_X)
			{
				xyp->x = buf.value;
				printf("x: %d\n", xyp->x);
			}
			if(buf.code == ABS_Y)	
			{
				xyp->y = buf.value;
				printf("y: %d\n", xyp->y);
			}			
		}

		if(buf.type == EV_KEY)
		{
			if(buf.code == BTN_TOUCH && buf.value == 0)
				break;
		}
	}

	close(ts);

}

int judge(struct coordinate *xyp)
{
	if(200 <= xyp->x && xyp->x <= 320 && 120 <= xyp->y && xyp->y <= 360)
	{
		return 1;
	}
	else if(360 <= xyp->x && xyp->x <= 480 && 120 <= xyp->y && xyp->y <= 360)
	{
		return 2;
	}
	else if(520 <= xyp->x && xyp->x <= 640 && 120 <= xyp->y && xyp->y <= 360)
	{
		return 3;
	}
	else if(720 <= xyp->x && xyp->x <= 800 && 400 <= xyp->y && xyp->y <= 480)
		return 4;

}

int main(int argc, char **argv)
{
	struct fb_var_screeninfo vinfo;
	char *fbmemy = init_lcd(&vinfo);

	struct image_info imgfo;
	char *imgdata = load_bmp("phone.bmp", &imgfo);

	display_bmp(fbmemy, &vinfo, imgdata, &imgfo, 0, 0);

	struct phone_info ph;
	struct coordinate *xyp = calloc(1, sizeof(struct coordinate));

	int ret = sqlite3_open("phone.db", &db);
	if(ret)
	{
		perror("sqlite3_open() failed");
		return -1;
	}

	create_table(db);

	while(1)
	{
		int ts = open("/dev/input/event0", O_RDONLY);
		if(ts == -1)
		{
			perror("open() failed");
			exit(0);
		}
		touch(ts, xyp);
		int n = judge(xyp);
		switch(n)
		{
			case 1:
				sqlite3_insert(db, &ph);
				display(db);
				break;
			case 2:
				sqlite3_del(db);
				display(db);
				break;
			case 3:
				sqlite3_update(db);
				display(db);
				break;
			case 4:
				exit(0);
		}
	}
	sqlite3_close(db);
	return 0;
}
