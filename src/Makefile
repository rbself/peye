
obj = line.o object.o peye.o common.o frame.o peye.o


peye:$(obj)
	gcc -lm -o $@ $^

$(obj):%.o:%.c
	gcc -c $< -o $@
