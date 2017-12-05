
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
		//generate_edge(obj->parry, obj->pcunt, &obj->ledge, &obj->redge);
		
		obj->height = obj->bottom - obj->top + 1;
		obj->width = obj->right - obj->left + 1;

		obj->centre.x = obj->left + (obj->width/2);
		obj->centre.y = obj->top + (obj->height/2);
		printf("obj: c: %d start: y:%d x:%d end: y:%d x:%d\n",obj->colour, obj->parry[0].y, obj->parry[0].x, obj->parry[obj->pcunt-1].y, obj->parry[obj->pcunt-1].x);
		if (i==0){
			int j=0, k;
			k = obj->parry[0].y;
			while (j < obj->pcunt){
				if(k != obj->parry[j].y) {
					printf("\n");
					k = obj->parry[j].y;
				}
				printf("y:%d x:%d  ", obj->parry[j].y, obj->parry[j].x);
				j++;
			}
		}
	}

	return 0;
}

struct object* new_object(FRAME_OBJ *frame, PIXEL *p)
{
	struct object *obj;

	//printf("add new obj x:%d y:%d c:%d.\n", p->x, p->y, p->colour);

	if (frame->obj_cunt > 1000-2){
		printf("no obj avlibe.\n");
		return  &frame->objs[frame->obj_cunt];
	}
	
	obj = &frame->objs[frame->obj_cunt++];

	obj->parry = malloc(sizeof(PLACE)*100000);

	init_line(&obj->ledge, 10000);
	init_line(&obj->redge, 10000);

	obj->colour= p->colour;
	obj->parry[obj->pcunt].x = p->x;
	obj->parry[obj->pcunt].y = p->y;
	obj->height = 1;
	obj->width = 1;
	obj->pcunt = 1;
	obj->top = obj->bottom = p->y;
	obj->left = obj->right = p->x;

	p->obj = obj;
	
	return obj;
}

int add_pixle_to_obj(struct object *obj, PIXEL *p)
{
	//printf("add pixel x:%d y:%d to c:%d.\n", p->x, p->y, p->colour);

	if (obj->pcunt > 1000-2){
		//printf("obj full %d\n\n", obj->pcunt);
		p->obj=obj;
		return 0;
	}

	obj->parry[obj->pcunt].x = p->x;
	obj->parry[obj->pcunt].y = p->y;
	obj->pcunt++;
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

	printf("%s %d\n", __FUNCTION__, __LINE__);
	for(i=400; i < 550; i++){
		line = yp + (i*frame->width);
		//printf("%s %d\n", __FUNCTION__, __LINE__);

		for (j = 0; j < frame->width-1; j++){
			//printf("%s %d\n", __FUNCTION__, __LINE__);
			current = &frame->parry[i][j];
			current->x = j;
			current->y = i;
			current->colour = *(line+j);
			ref_cunt = 0;
			//printf("%s %d\n", __FUNCTION__, __LINE__);

			if (j == 0 && i == 400){
				//printf("%s %d\n", __FUNCTION__, __LINE__);
				new_object(frame, current);
				continue;
			} else if(j == 0){
				//printf("%s %d\n", __FUNCTION__, __LINE__);
				ref[ref_cunt++] = &frame->parry[i-1][j];
				ref[ref_cunt++] = &frame->parry[i-1][j+1];
			} else if (i == 400){
				//printf("%s %d\n", __FUNCTION__, __LINE__);
				ref[ref_cunt++] = &frame->parry[i][j-1];
			} else {
				//printf("%s %d\n", __FUNCTION__, __LINE__);
				ref[ref_cunt++] = &frame->parry[i][j-1]; //left
				ref[ref_cunt++] = &frame->parry[i-1][j-1]; //left-up
				ref[ref_cunt++] = &frame->parry[i-1][j]; //left-up

				if (j < (frame->width-1)){
					//printf("%s %d\n", __FUNCTION__, __LINE__);
					ref[ref_cunt++] = &frame->parry[i-1][j+1]; //left-up
				}
			}
			//printf("%s %d\n", __FUNCTION__, __LINE__);

			if(ref_cunt > 4){
				printf("get error ref cunt:%d\n", ref_cunt);
				return -1;
			}
			//printf("%s %d\n", __FUNCTION__, __LINE__);

			for(k = 0; k < ref_cunt; k++){
				//printf("%s %d\n", __FUNCTION__, __LINE__);
				if (is_similar_colour(current->colour, ref[k]->colour)){
					//printf("%s %d\n", __FUNCTION__, __LINE__);
					add_pixle_to_obj(ref[k]->obj, current);
					//printf("%s %d\n", __FUNCTION__, __LINE__);
					break;
				}
			}
			//printf("%s %d\n", __FUNCTION__, __LINE__);

			if (k >= ref_cunt){
				//printf("%s %d\n", __FUNCTION__, __LINE__);
				new_object(frame, current);
			}
			//printf("%s %d\n", __FUNCTION__, __LINE__);
		}
	}

}

