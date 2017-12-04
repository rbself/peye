
#ifndef __COMMON_H__
#define __COMMON_H__


typedef struct st_place{
	int x;
	int y;
}PLACE;


struct peye{
	FILE *fp;
	int cur_id;
	int height;
	int width;
	int stride;
};

#define peye_assert(x) if(x) printf("%f %d asert!\n", __FILE__, __LINE__);
int is_similar_colour(unsigned char a, unsigned char b);

#endif

