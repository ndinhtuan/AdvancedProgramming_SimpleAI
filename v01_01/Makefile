#makefile
build_main:
	g++ main.cpp util.cpp -o main.out
build_data:
	g++ data_processing.cpp util.h util.cpp -o data_processing.out
run:
	chmod +x main.out
	./main.out
clean:
	rm -rf *.o main.out
