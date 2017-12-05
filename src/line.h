
#ifndef __LINE_H__
#define __LINE_H__
#include "common.h"

enum{
	OBLIQUE_STRAIGHT_LINE,
	PLANE_STRAIGHT_LINE,
	VERTICAL_STRAIGHT_LINE,
	CYCLO_LINE,

};

typedef struct st_line{
	PLACE *arry;
	PLACE *start;
	PLACE *end;
	PLACE *vertex[20];
	int num;
	int type;
}LINE;

int set_line_type(LINE *line);
int generate_edge(PLACE *pix, int pixcnt, LINE *ledge, LINE *redge);
int line_reach_place(PLACE *src, PLACE *aim);
int is_line_continuous(PLACE *a, PLACE *b);
int init_line(LINE *line, int arrynum);

#endif

