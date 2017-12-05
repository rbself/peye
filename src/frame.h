

#ifndef __FRAME_H__
#define __FRAME_H__

#include "object.h"

struct st_frame{
	char *data;
	int height;
	int width;
	struct st_frame_obj *fobj;
	
};

#endif
