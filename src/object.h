

#ifndef __OBJECT_H
#define __OBJECT_H
#include "common.h"
#include "line.h"

#define MAX_OBJ_PLACE_NUM 100000
#define MAX_OBJ_NUM 1000

#define MAX_HEIGHT 1080
#define MAX_WIDTH  1920

#define START_LINE 400
#define END_LINE   555

enum{
	OBJ_COLOUR_TYPE,
	OBJ_SHAPE_TYPE,
	OBJ_SIZE_TYPE,
	OBJ_MAX_TYPE
};

typedef struct st_pixel{
	unsigned char colour;
	struct object *obj;
	struct st_pixel *ref;
}PIXEL;


struct object{
	unsigned char colour;
	PLACE *parry;
	PLACE centre;
	int height;
	int width;
	int pcunt;
	int no;
	int top;
	int	left;
	int right;
	int bottom;
	LINE ledge;
	LINE redge;
};


struct colour_group{
	unsigned char colour;
	unsigned char res1;
	unsigned char res2[2];
	int num;
	struct object *objs[MAX_OBJ_NUM];
};

typedef struct st_frame_obj{
	int height;
	int width;
	int id;
	unsigned char *data;
	int obj_cunt;
	struct object objs[MAX_OBJ_NUM];
	PIXEL parry[MAX_HEIGHT][MAX_WIDTH];
	struct colour_group cls_obj[255];
	int cg_cnt;
}FRAME_OBJ;


int obj_parse_process(FRAME_OBJ *frame, char *yp);
int add_pixle_to_obj(struct object* obj, int y, int x);
struct object* new_object(FRAME_OBJ *frame, unsigned char c);
int shape_obj(FRAME_OBJ *frame);
int classify_by_size(FRAME_OBJ *frame);
int classify_by_shape(FRAME_OBJ *frame);
int classify_by_colour(FRAME_OBJ *frame);
int classify_obj(FRAME_OBJ *frame);

#endif

