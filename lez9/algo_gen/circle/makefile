all: esercizio9
esercizio9: main.o random.o
	g++ -o $@ $^
%.o: %.cxx %.h
	g++ -c $< -o $@ 
clean:
	rm *.o *~
resetfile:
	rm *.txt  
