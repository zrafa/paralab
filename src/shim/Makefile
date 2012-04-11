#gfortran44 -O2 -fno-underscoring -Wall -fPIC -shared -ldl -o shimf.so shimf.F90 dynamic_linking_loader.o 
# gcc -O2 -Wall  -fPIC -shared -ldl  -o shim.so shim.c callback.o
# gcc -O2 -Wall -fPIC  -c callback.c

C = gcc
GCCFLAGS = -O2  -Wall  -fPIC -I/usr/lib/openmpi/include -U_FORTIFY_SOURCE


# System dynamic linking loader library.
LIBDL =  -shared -ldl -lunwind

OBJ = callback.o clock.o

shim: $(OBJ) 
	$(C) $(GCCFLAGS) $(LIBDL) -o  $@.so  $@.c $(OBJ)

install:
	cp shim.so /home/oso/lib
	ls -l /home/oso/lib

CLEANFILES = *.o *.mod *.so

clean:; rm -f $(CLEANFILES)
 
cleanest: clean
	-rm -f example

%.o: %.c
	$(C) $(GCCFLAGS) -c $<

