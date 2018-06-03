
all: 
	  gcc unibeam.c -o unibeam 
	  gcc unimake.c -o unimake

install: 
	   cp  unibeam  /usr/local/bin/unibeam 
	   cp  unimake   /usr/local/bin/unimake 

 


