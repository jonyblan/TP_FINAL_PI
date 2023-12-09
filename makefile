COMPILER=gcc
OUTPUT_FILE=bikeSharingMON.out
FRONT=bikeSharingMON.c

all: programa

programa: $(FRONT) stationADT.o bstADT.o htmlTable.o
	$(COMPILER) -o $(OUTPUT_FILE) $(FRONT) stationADT.o bstADT.o htmlTable.o

stationADT.o: stationADT.c
	$(COMPILER) -c stationADT.c

bstADT.o: bstADT.c
	$(COMPILER) -c bstADT.c

htmlTable.o: htmlTable.c
	$(COMPILER) -c htmlTable.c

clean:
	rm -f *.o
