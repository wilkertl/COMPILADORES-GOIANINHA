CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

all: teste_tabela_simbolos

teste_tabela_simbolos: teste_tabela_simbolos.o tabela_simbolos.o
	$(CXX) $(CXXFLAGS) -o teste_tabela_simbolos teste_tabela_simbolos.o tabela_simbolos.o

teste_tabela_simbolos.o: teste_tabela_simbolos.cpp tabela_simbolos.h
	$(CXX) $(CXXFLAGS) -c teste_tabela_simbolos.cpp

tabela_simbolos.o: tabela_simbolos.cpp tabela_simbolos.h
	$(CXX) $(CXXFLAGS) -c tabela_simbolos.cpp

clean:
	rm -f *.o teste_tabela_simbolos