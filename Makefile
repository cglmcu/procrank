all :
	$(CC) *.c -marm -Os -o procrank -I.

install :
	@cp procrank /usr/bin
	@chmod +s /usr/bin/procrank
