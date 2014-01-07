bingw:main.o get_latest_image.o help.o
	gcc -o bingw main.o get_latest_image.o help.o
	chmod 777 bingw
	sudo cp bingw /usr/bin/
main.o:main.c bingw.h
	gcc -c main.c
change_latest_image.o:get_latest_image.c bingw.h
	gcc -c get_latest_image.c
help.o:help.c bingw.h
	gcc -c help.c

clean:
	rm bingw main.o get_latest_image.o help.o
	sudo rm /usr/bin/bingw
