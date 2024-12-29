all: Laba3
clean:
	rm -f Laba3 *.o
Laba3: main.c Sorts.c 
	gcc -o Laba3 main.c Sorts.c 
start:
	@echo "Running with arguments: $(args)"
	./Laba3 $(args)