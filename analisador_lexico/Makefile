CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

all: goianinha

# Gerar o código C++ a partir do arquivo .l usando Flex
lex.yy.cc: goianinha.l
	flex -+ -o lex.yy.cc goianinha.l

# Compilar o código gerado pelo Flex
lex.yy.o: lex.yy.cc
	$(CXX) $(CXXFLAGS) -c lex.yy.cc

# Compilar o programa principal
analisador_lexico.o: analisador_lexico.cpp tokens.h
	$(CXX) $(CXXFLAGS) -c analisador_lexico.cpp

# Linking
goianinha: lex.yy.o analisador_lexico.o
	$(CXX) $(CXXFLAGS) -o goianinha lex.yy.o analisador_lexico.o

clean:
	rm -f lex.yy.cc *.o goianinha