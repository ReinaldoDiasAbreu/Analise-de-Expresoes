# Arquivo Makefile

all: expressao clean
	@echo "Compilação Concluída!"
	@echo "Pare executar digite: ./expressao"

expressao: main.o
	g++ -g -Wall main.o -o expressao

clean:
	rm *.o
