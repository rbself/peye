
#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "line.h"
#include "object.h"
#include "frame.h"

int combine_obj_line()
{

}


int source_init(struct peye *eye, char *filename)
{
	eye->width = 1280;
	eye->height = 720;

	eye->fp = fopen(filename, "rb");

	if (NULL == eye->fp){
		printf("open file error!\n");
		return -1;
	}
	return 0;
}

int get_one_frame(struct peye *eye, char *yp)
{
	int lenth;
	int ret;

	lenth = eye->height * eye->width;
	
	ret = fread(yp, 1, lenth, eye->fp);
	if (ret != lenth){
		printf("read %d content, less than %d.\n", ret, lenth);
		return -1;
	}

	fclose(eye->fp);
	return 0;
}

int eye_init()
{
	

}

void main()
{
	struct peye eye;
	int ret;
	struct st_frame frame;

	ret = source_init(&eye, "che.yuv");
	if(ret){
		printf("init error!\n");
		return;
	}

	frame.width = 1280;
	frame.height = 720;

	frame.data = malloc(1920*1080);

	ret = get_one_frame(&eye, frame.data);
	if(ret){
		printf("get_one_frame error!\n");
		return;
	}
	//get_column(&frame);

	frame.fobj = malloc(sizeof(struct st_frame_obj));

	frame.fobj->data = frame.data;
	frame.fobj->obj_cunt = 0;
	frame.fobj->width = 1280;
	frame.fobj->height = 720;

	obj_parse_process(frame.fobj, frame.data);
	shape_obj(frame.fobj);

	printf("find %d objs\n", frame.fobj->obj_cunt);
	
	return;
}



