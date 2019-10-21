all: esercizio5
esercizio5: main.o funzioni.o
	g++ -o $@ $^
%.o: %.cxx %.h
	g++ -c $< -o $@ 
clean:
	rm *.o *~
resetfile:
	rm *.txt  
