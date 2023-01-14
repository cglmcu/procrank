all :
	$(CC) *.o -o procrank -I.

%.o : %.c
	gcc -Os -c $<

install :
	@cp procrank /usr/bin
	@chmod +s /usr/bin/procrank
