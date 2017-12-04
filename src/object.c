
#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "line.h"
#include "object.h"
#include "frame.h"


int classify_obj(FRAME_OBJ *frame)
{
	return 0;
}

int classify_by_colour(FRAME_OBJ *frame)
{
	int i,j;
	struct object *obj;

	for (i=0; i<frame->obj_cunt; i++){
		for(j=0; j < frame->cg_cnt; j++){
			if (is_similar_colour(obj->colour, frame->cls_obj[j].colour)){
				break;
			}
		}

		if (j >= frame->cg_cnt){
			frame->cls_obj[frame->cg_cnt].colour = obj->colour;
			frame->cls_obj[frame->cg_cnt].num = 1;
			frame->cls_obj[frame->cg_cnt].objs[frame->cls_obj[frame->cg_cnt].num] = obj;
		} else {
			frame->cls_obj[j].num++;
			frame->cls_obj[frame->cg_cnt].objs[frame->cls_obj[frame->cg_cnt].num] = obj;
		}
	}

	return 0;
}

int classify_by_shape(FRAME_OBJ *frame)
{
	int i;
	struct object *obj;

	for (i=0; i<frame->obj_cunt; i++){


	}

	return 0;
}

int classify_by_size(FRAME_OBJ *frame)
{
	int i;
	struct object *obj;

	for (i=0; i<frame->obj_cunt; i++){


	}

	return 0;
}


int shape_obj(FRAME_OBJ *frame)
{
	int i;
	struct object *obj;

	for (i=0; i<frame->obj_cunt; i++){
		obj = &frame->objs[i];
		generate_edge(obj->pix[0], 1000, obj->ledge, obj->redge);
		
		obj->height = obj->bottom - obj->top + 1;
		obj->width = obj->right - obj->left + 1;

		obj->centre.x = obj->left + (obj->width/2);
		obj->centre.y = obj->top + (obj->height/2);
	}

	return 0;
}

struct object* new_object(FRAME_OBJ *frame, PIXEL *p)
{
	struct object *obj = &frame->objs[frame->obj_cunt++];

	obj->pcunt = 0;
	
	obj->colour= p->colour;
	obj->pix[obj->pcunt++] = p;
	obj->height = 1;
	obj->width = 1;
	obj->top = obj->bottom = p->y;
	obj->left = obj->right = p->x;
	
	return obj;
}

int add_pixle_to_obj(struct object *obj, PIXEL *p)
{
	obj->pix[obj->pcunt++] = p;
	p->obj=obj;

	if (p->x < obj->left){
		obj->left = p->x;
	} else if (p->x > obj->right){
		obj->right = p->x;
	}

	if (p->y > obj->bottom){
		obj->bottom = p->y;
	}

	
	return 0;
}


int obj_parse_process(FRAME_OBJ *frame, char *yp)
{
	int i, j, k;
	unsigned char *line;
	PIXEL *current;
	PIXEL *ref[4];
	int ref_cunt = 0;;
	struct object *obj;
	unsigned char colour;
	
	for(i=0; i < frame->height; i++){
		line = yp + (i*frame->width);

		for (j = 0; j < frame->width; j++){
			//current = &frame->parry[j][i];
			current->x = j;
			current->y = i;
			current->colour = *(line+j);

			if (j == 0 && current->y == 0){
				new_object(frame, current);
			} else if(j == 0){
				ref[ref_cunt++] = &frame->parry[j][i-1];
				ref[ref_cunt++] = &frame->parry[j+1][i-1];
			} else if (current->y == 0){
				ref[ref_cunt++] = &frame->parry[j-1][i];
			} else {
				ref[ref_cunt++] = &frame->parry[j-1][i]; //left
				ref[ref_cunt++] = &frame->parry[j-1][i-1]; //left-up
				ref[ref_cunt++] = &frame->parry[j][i-1]; //left-up

				if (j < (frame->width-1)){
					ref[ref_cunt++] = &frame->parry[j+1][i-1]; //left-up
				}
			}

			if(ref_cunt > 4){
				printf("get error ref cunt:%d\n", ref_cunt);
				return -1;
			}

			for(k = 0; k < ref_cunt; k++){
				if (is_similar_colour(current->colour, ref[k]->colour)){
					add_pixle_to_obj(ref[k]->obj, current);
				}
			}

			if (k >= ref_cunt){
				new_object(frame, current);
			}
		}
	}

}

