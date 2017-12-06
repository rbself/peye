/*


*/


#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "line.h"
#include "object.h"



int is_similar_colour(unsigned char a, unsigned char b)
{
	if (abs(a-b)<=10){
		return 1;
	}
	
	return 0;
}

