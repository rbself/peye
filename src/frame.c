
#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "line.h"
#include "object.h"
#include "frame.h"

int frame_init()
{

}

int get_column(struct st_frame *frame)
{
	int i,j;
	unsigned char c;
	memset(frame->column, 0, sizeof(frame->column));

	for (i = START_LINE; i < END_LINE; i++){
		for (j = 0; j < frame->width; j++){
			c = *(frame->data + i*frame->width + j);
			frame->column[c]++;
		}
	}
	for (i=0; i<255; i++)
	 printf("c:%d :%ld\n", i, frame->column[i]);
	printf("\n");
	return 0;
	
}
