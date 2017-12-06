
obj = line.o object.o peye.o common.o frame.o peye.o


peye:$(obj)
	gcc -o1 -o $@ $^ -lm

$(obj):%.o:%.c
	gcc -c $< -o $@

clean:
	rm *.o peye
