typedef struct st_pixel{
	int x;
	int y;
	unsigned char colour;
	struct object *obj;
}PIXEL;

typedef struct st_place{
	int x;
	int y;
}PLACE;

typedef struct st_line{
	PLACE *arry;
	int num;
	int type;
}LINE;

struct object{
	char colour;
	PIXEL pix[];
	PLACE centre;
	int height;
	int width;
	int pcunt;
	int top;
	int	left;
	int right;
	int bottom;
	LINE ledge;
	LINE redge;
};

struct peye{
	FILE *fp;
	int cur_id;
	int height;
	int width;
	int stride;
	int obj_cunt;
	struct object objs[];
	PLACE parry[1920][1080];
};

#define peye_assert(x) if(x) printf("%f %d asert!\n", __FILE__, __LINE__);

