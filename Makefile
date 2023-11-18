CFLAG = g++ -std=c++11 -O3 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment -Wall  -lm

Proj.o : Proj.cpp
	$(CFLAG) -o Proj.o Proj.cpp

run1: 
	./Proj.o < test1.in

run2: 
	./Proj.o < test2.in

clean:
	rm -f *.o Proj.o

clean2:
	rm -f *.o


