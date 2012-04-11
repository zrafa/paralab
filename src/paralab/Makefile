CPP = g++
CFLAGS = -O2 -Wall


OBJ = dnode.o main.o nnode.o node.o rnode.o trace.o

paralab: $(OBJ) 
	$(CPP) $(CFLAGS) -o paralab $(OBJ)

all: paralab

clean:; rm -f *.o paralab
 
%.o: %.cc
	$(CPP) $(CFLAGS) -c $<
