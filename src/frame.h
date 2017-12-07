

#ifndef __FRAME_H__
#define __FRAME_H__

#include "object.h"

struct st_frame{
	unsigned char *data;
	unsigned long long column[255];
	int height;
	int width;
	
	struct st_frame_obj *fobj;
	
};
int get_column(struct st_frame *frame);

#endif
