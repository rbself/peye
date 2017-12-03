


int combine_obj_line()
{

}


int source_init(struct peye *eye, char *filename)
{
	eye->fp = fopen(filename, "rb");

	if (NULL == eye->fp){
		printf("open file error!\n");
		return -1;
	}
	return 0;
}

int get_one_frame(struct peye *eye, char *yp)
{
	int lenth;
	int ret;

	lenth = eye->height * eye->width;
	
	ret = fread(yp, lenth, 1, eye->fp);
	if (ret != lenth){
		printf("read %d content, less than %d.\n", ret, lenth);
		return -1;
	}
	return 0;
}

int eye_init()
{
	

}




