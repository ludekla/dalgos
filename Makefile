CMD = main
DIR = src
LDIR = src/p03_algos
LIB_A = ch12_sort
# LIB_B = ch10_parcel
#LF = -lm # library flag for math.h
INC = -I include/p03_algos

bin/main: bin/main.o bin/$(LIB_A).o # bin/$(LIB_B).o
	gcc -o $@ $^

bin/main.o: $(DIR)/$(CMD).c
	gcc -o $@ $(INC) -c $^ 

bin/$(LIB_A).o: $(LDIR)/$(LIB_A).c
	gcc -o $@ $(INC) -c $^

#bin/$(LIB_B).o: $(LDIR)/$(LIB_B).c
#	gcc -o $@ $(INC) -c $^data

clean:
	rm bin/*
