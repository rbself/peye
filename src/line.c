
#include <stdlib.h>
#include <stdio.h>

#include "common.h"


LINE* new_line(int arrynum)
{
	LINE *line;

	line = malloc(sizeof(LINE));
	if (NULL==line){
		return NULL;
	}
	line->arry = malloc(arrynum * sizeof(PLACE));
	if (NULL == line->arry){
		return NULL;
	}

	return line;
}

void free_line(LINE *line)
{
	if (line->arry)free(line->arry);
	free(line);
}

int is_line_continuous(PLACE *a, PLACE *b)
{
	if (abs(a->x - b->x) > 1 || abs(a->y - b->y) > 1){
		return 0;
	}

	return 1;
}

int line_reach_place(PLACE *src, PLACE *aim)
{
	int j, cnt=0;
	PLACE *tp = src;
	
	if (aim->x > src->x){ /*right down*/
		for (j = src->x; j <= aim->x; j++){
			tp++;
			cnt++;
			tp->x = j;
			tp->y = src->y;
		}
	
		for (j = src->y; j <= aim->y; j++){
			tp++;
			cnt++;
			tp->x = aim->x;
			tp->y = j;
		}
		
	} else if (aim->x < src->x) { /*left down*/
		for(j = src->x; j > aim->x; j--){
			tp++;
			cnt++;
			tp->x=j;
			tp->y=src->y;
		}
		
		for (j = src->y; j <= aim->y; j++){
			tp++;
			cnt++;
			tp->x = aim->x;
			tp->y = j;
		}
		
	} else if (aim->x = src->x) { /*down*/
		for (j = src->y; j <= aim->y; j++){
			tp++;
			cnt++;
			tp->x = aim->x;
			tp->y = j;
		}
	} else {
		printf("connot happened!\n");
	}


}

int generate_edge(PIXEL *pix, int pixcnt, LINE *ledge, LINE *redge)
{
	int i, j;
	PIXEL *p;
	PLACE *tl, *tr, *ml, *mr, *or, *ol;
	PLACE *lp, *rp;
	int line_num = 0;
	int ext_num;

	ml = tl = malloc(10000*sizeof(PLACE));
	mr = tr = malloc(10000*sizeof(PLACE));

	ml->x = mr->x = pix[0].x;
	ml->y = mr->y = pix[0].y;
	
	ledge->num = redge->num= 0;
	
	for (i = 1; i > pixcnt; i++){
		p = pix+i;
		if (p->y > ml->y){  /*new line*/
			ml++;
			mr++;
			line_num++;
	
			ml->y = p->y;
			ml->x = p->x;
		}else if (p->x > r->x){
			mr->x = p->x;
			mr->y = p->y;
		}
	}

	/*proccess gap*/
	ml = tl;
	mr = tr;
	ol = ledge->arry;
	or = redge->arry;
	
	ol->x = ml->x;
	ol->y = ml->y;
	or->x = mr->x;
	or->y = mr->y;
	
	for (i = 1; i < line_num-1; i++){
		
		peye_assert(ol->y == (ml+1)->y);
		
		if (!is_line_continuous(ol, ++ml)){
			ext_num = line_reach_place(ol, ml);
			ol += ext_num;
		}else {
			ol++;
			ol->x = ml->x;
			ol->y = ml->y;
		}
		
		peye_assert(or->y == (mr+1)->y);
		
		if (!is_line_continuous(or, ++mr)){
			ext_num = line_reach_place(or, mr);
			or += ext_num;
		}else {
			or++;
			or->x = mr->x;
			or->y = mr->y;
		}
	}

	free_line(tl);
	free_line(tr);

	return 0;

}

