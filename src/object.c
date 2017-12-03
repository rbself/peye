#include <stdlib.h>
#include <stdio.h>

#include "common.h"


int shape_obj(struct object *obj)
{
	int i, j;
	PIXEL *p;
	PLACE *tl, *tr, *ml, *mr, *or, *ol;
	PLACE *lp, *rp;
	int line_num = 0;
	int ext_num;

	generate_edge(obj->pix[0], obj->ledge, obj->redge);

	return 0;
}

struct object* new_object(struct peye *eye, PLACE *p)
{
	struct object *obj = eye->objs[eye->obj_cunt++];

	obj->pcunt = 0;
	
	obj->colour= p->colour;
	obj->pix[obj->pcunt++] = p;
	obj->height = 1;
	obj->width = 1;
	obj->top = obj->bottom = p->y;
	obj->left = obj->right = p->x;
	
	return obj;
}

int add_pixle_to_obj(struct object *obj, PLACE *p)
{
	obj->pix[obj->pcunt++] = p;
	obj->
	p->obj=obj;

	if (p->x < obj->left){
		obj->left = p->x;
	} else if (p->x > obj->right){
		obj->right = p->x;
	}

	if (p->y > obj->bottom){
		obj->bottom = p->y;
	}

	obj->height = obj->bottom - obj->top + 1;
	obj->width = obj->right - obj->left + 1;

	obj->centre.x = obj->left + (obj->width/2);
	obj->centre.y = obj->top + (obj->height/2);
	
	return 0;
}

int is_similar_colour(unsigned a, unsigned b, unsigned t)
{
	if (abs(a-b)<=t){
		return 1;
	}
	
	return 0;
}

int obj_parse_process(struct peye *eye, char *yp)
{
	int i, j, k;
	unsigned char *line;
	PLACE *current;
	PLACE *ref[4];
	int ref_cunt = 0;;
	struct object *obj;
	
	for(i=0; i < eye->height; i++){
		line = yp + (i*eye->width);

		for (j = 0; j < eye->width; j++){
			current = &eye->parry[j][i];
			current->x = j;
			current->y = i;
			current->colour = *(line+j);

			if (current->x = 0 && current->y = 0){
				new_object(eye, current);
			} else if(current->x == 0){
				ref[ref_cunt++] = eye->parry[current->x][current->y-1];
				ref[ref_cunt++] = eye->parry[current->x+1][current->y-1];
			} else if (current->y == 0){
				ref[ref_cunt++] = eye->parry[current->x-1][current->y];
				if (is_similar_colour(current->colour, ref->colour, 0)){
					add_pixle_to_obj(ref->obj, current);
					break;
				}
				
				new_object(eye, current);
			} else {
				ref[ref_cunt++] = eye->parry[current->x-1][current->y]; //left
				ref[ref_cunt++] = eye->parry[current->x-1][current->y-1]; //left-up
				ref[ref_cunt++] = eye->parry[current->x][current->y-1]; //left-up

				if (current->x < (eye->width-1)){
					ref[ref_cunt++] = eye->parry[current->x+1][current->y-1]; //left-up
				}
			}

			if(ref_cunt > 4){
				printf("get error ref cunt:%d\n", ref_cunt);
				return -1;
			}

			for(k = 0; k < ref_cunt; k++){
				if (is_similar_colour(current->colour, ref[k]->colour, 0)){
					add_pixle_to_obj(ref[k]->obj, current);
				}
			}

			if (k > = ref_cunt){
				new_object(eye, current);
			}
		}
	}

}

