
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
		//if (obj->pcunt < 100){
		//	continue;
		//}
		generate_edge(obj->parry, obj->pcunt, &obj->ledge, &obj->redge);
		
		obj->height = obj->bottom - obj->top + 1;
		obj->width = obj->right - obj->left + 1;

		obj->centre.x = obj->left + (obj->width/2);
		obj->centre.y = obj->top + (obj->height/2);
		pdbg("obj: c: %d start: y:%d x:%d end: y:%d x:%d\n",obj->colour, obj->parry[0].y, obj->parry[0].x, obj->parry[obj->pcunt-1].y, obj->parry[obj->pcunt-1].x);
		if (i<57){
			int j, k;
			j=0;
			k = obj->parry[0].y;
			while (j < obj->pcunt){
				if(k != obj->parry[j].y) {
					pdbg("\n");
					k = obj->parry[j].y;
				}
				pdbg("[y:%d x:%d c:%d ] ", obj->parry[j].y, obj->parry[j].x, frame->parry[obj->parry[j].y][obj->parry[j].x].colour);
				j++;
			}
		}
		printf("ledge: \n");
		print_line(&obj->ledge);
		printf("redge: \n");
		print_line(&obj->redge);
	}

	return 0;
}

struct object* new_object(FRAME_OBJ *frame, unsigned char c)
{
	struct object *obj;

	//pdbg("add new obj x:%d y:%d c:%d.\n", p->x, p->y, p->colour);

	if (frame->obj_cunt > MAX_OBJ_NUM-2){
		pdbg("no obj avlibe.\n");
		return  NULL;
	}
	
	obj = &frame->objs[frame->obj_cunt];
	obj->parry = malloc(sizeof(PLACE)*MAX_OBJ_PLACE_NUM);
	obj->no = frame->obj_cunt;

	init_line(&obj->ledge, 10000);
	init_line(&obj->redge, 10000);

	obj->colour = c;
	obj->height = 0;
	obj->width = 0;
	obj->pcunt = 0;
	frame->obj_cunt++;
	pdbg("new object cnt:%d\n", frame->obj_cunt);
	return obj;
}

int add_pixle_to_obj(struct object* obj, int y, int x)
{
	if (obj->pcunt > MAX_OBJ_PLACE_NUM-2){
		return 0;
	}
	pdbg("add %d %d to %d obj at %d\n", y, x,obj->no, obj->pcunt);
	obj->parry[obj->pcunt].x = x;
	obj->parry[obj->pcunt].y = y;
	obj->pcunt++;

	if (x < obj->left){
		obj->left = x;
	} else if (x > obj->right){
		obj->right = x;
	}

	if (y > obj->bottom){
		obj->bottom = y;
	}
	
	return 0;
}


int obj_parse_process(FRAME_OBJ *frame, char *yp)
{
	int i, j, k, ref_sml;
	unsigned char *line;
	PIXEL *current;
	PIXEL *ref[4];
	int ref_cunt = 0;;
	struct object *obj;
	unsigned char div_c, tmp_c;

	pdbg("%s %d\n", __FUNCTION__, __LINE__);
	for(i=START_LINE; i < END_LINE; i++){
		line = yp + (i*frame->width);

		for (j = 0; j < frame->width; j++){
			current = &frame->parry[i][j];
			current->colour = *(line+j);
			ref_cunt = 0;
			pdbg("start y:%d x:%d c:%d \n", i, j, current->colour);
			if (j == 0 && i == START_LINE){
				obj = new_object(frame, current->colour);
				if (obj){
					add_pixle_to_obj(obj, i, j);
					current->obj = obj;
				}
				continue;
			} else if(j == 0){
				ref[ref_cunt++] = &frame->parry[i-1][j];
				ref[ref_cunt++] = &frame->parry[i-1][j+1];
				pdbg("ref:[%d %d] [%d %d]\n", i-1, j, i-1, j+1);
			} else if (i == START_LINE){
				ref[ref_cunt++] = &frame->parry[i][j-1];
				pdbg("ref:[%d %d]\n", i, j-1);
			} else {
				ref[ref_cunt++] = &frame->parry[i][j-1];      /*left*/
				ref[ref_cunt++] = &frame->parry[i-1][j-1];    /*left-up*/
				ref[ref_cunt++] = &frame->parry[i-1][j];      /*lup*/
				pdbg("ref:[%d %d] [%d %d] [%d %d]", i, j-1, i-1, j-1, i-1, j);

				if (j < (frame->width-1)){
					ref[ref_cunt++] = &frame->parry[i-1][j+1]; /*left-up*/
					pdbg(" [%d %d]", i-1, j+1);
				}
				pdbg("\n");
			}

			if(ref_cunt > 4){
				pdbg("get error ref cunt:%d\n", ref_cunt);
				return -1;
			}
			
			div_c=100;
			ref_sml = 0;

			for(k = 0; k < ref_cunt; k++){
				tmp_c = abs(current->colour-ref[k]->colour);
				if(div_c > tmp_c){
					div_c = tmp_c;
					ref_sml = k;
				}
			}

			if (div_c < 10){
					pdbg("use ref %d\n", ref_sml);
					if (ref[ref_sml]->obj){
						add_pixle_to_obj(ref[ref_sml]->obj, i, j);
						current->obj = ref[ref_sml]->obj;
					}
			} else {
				obj = new_object(frame, current->colour);
				if (obj){
					add_pixle_to_obj(obj, i, j);
					current->obj = obj;
				}
			}
		}
	}

}

