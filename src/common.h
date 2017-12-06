
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

#define peye_assert(x) if(x) printf("%s %d asert!\n", __FILE__, __LINE__);
int is_similar_colour(unsigned char a, unsigned char b);

#if 0
#define pdbg(fmt,...) printf("(%s %d)"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define pdbg(fmt,...) 
#endif

#endif

