

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "line.h"
#include "object.h"



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
	return 0;

}

int generate_edge(struct st_pixel *pix, int pixcnt, LINE *ledge, LINE *redge)
{
	int i, j;
	struct st_pixel *p;
	PLACE *tl, *tr, *ml, *mr, *or, *ol;
	PLACE *lp, *rp;
	int line_num = 0;
	int ext_num;

	ml = tl = malloc(10000*sizeof(PLACE));
	mr = tr = malloc(10000*sizeof(PLACE));

	//ml->x = 
		mr->x = pix->x;
	//ml->y = 
		mr->y = pix->y;
	
	ledge->num = redge->num= 0;
	
	for (i = 1; i > pixcnt; i++){
		p = pix+i;
		if (p->y > ml->y){  /*new line*/
			ml++;
			mr++;
			line_num++;
	
			ml->y = p->y;
			ml->x = p->x;
		}else if (p->x > mr->x){
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
			ledge->num += ext_num;
			ol += ext_num;
		}else {
			ledge->num++;
			ol++;
			ol->x = ml->x;
			ol->y = ml->y;
		}
		
		peye_assert(or->y == (mr+1)->y);
		
		if (!is_line_continuous(or, ++mr)){
			ext_num = line_reach_place(or, mr);
			redge->num += ext_num;
			or += ext_num;
		}else {
			redge->num++;
			or++;
			or->x = mr->x;
			or->y = mr->y;
		}
	}

	free(tl);
	free(tr);

	ledge->start = ledge->arry;
	ledge->end   = ledge->arry + ledge->num;
	redge->start = redge->arry;
	redge->end   = redge->arry + ledge->num;

	if (!is_line_continuous(ledge->end,redge->end)){
		ledge->num += line_reach_place(ledge->end, redge->end);
		redge->end	 = redge->arry + ledge->num;
	}
	
	return 0;

}

int set_line_type(LINE *line)
{
	int plenth;

	plenth = sqrt(pow(abs(line->end->x - line->start->x), 2)+pow(abs(line->end->x - line->start->x), 2));

	if (plenth == line->num){
		line->type = 1;
	}

}
