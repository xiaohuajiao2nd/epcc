mycrack: main.o crack.o crc64.o hash_table.o
	mpic++ -fopenmp -o mycrack main.o crack.o crc64.o hash_table.o

main.o: main.cpp crc64.h hash_table.h types.h crack.h
	mpic++ -fopenmp -c main.cpp

crack.o: crack.cpp crack.h hash_table.h crc64.h
	mpic++ -fopenmp -c crack.cpp

hash_table.o: hash_table.cpp hash_table.h
	mpic++ -fopenmp -c hash_table.cpp

crc64.o: crc64.cpp crc64.h
	mpic++ -fopenmp -c crc64.cpp

clean:
	rm mycrack main.o crack.o hash_table.o crc64.o
