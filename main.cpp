#include <iostream>
#include <cstdlib>
#include "expressoes.h"
using namespace std;

/*
    TRABALHO DE AEDS II
    ANÁLISE DE EXPRESSOES ARITMÉTICAS
    Reinaldo Junio Dias de Abreu
    Mirralis Dias Santana
    Ciência da Computação - IFNMG
    2019

    OBS:
    Trabalho realizado usando o sistema Linux Mint 18.1 LTS, com conpilador GNU GCC/G++ 7.3.0.
    Na linha 25 e 26 descomente o modo de limpesa da tela correspondente a seu sistema operacional.
*/

int main()
{
    string expr;
    char rep = 's';

    while(rep == 's' || rep == 'S')
    {
        system("clear");    // Limpa a tela em Sitemas Linux
        //system("cls");    // Limpa a tela em Sistemas Windows
        cout << endl << "   *********** Analizador de Expressoes Aritmeticas ************" << endl;
        cout << "   *                                                           *" << endl;
        cout << "   *      Operadores e Comandos Permitidos:                    *" << endl;
        cout << "   *          + -> Adicao            - -> Subtracao            *" << endl;
        cout << "   *          * -> Multiplicacao     / -> Divisao              *" << endl;
        cout << "   *        ( ) -> Parenteses                                  *" << endl;
        cout << "   *                                                           *" << endl;
        cout << "   *      E necessario o uso de variaveis na expressao.        *" << endl;
        cout << "   *                                                           *" << endl;
        cout << "   *************************************************************" << endl;
        cout << "   -> Digite a expressao: ";
        cin >> expr;      

        Expressao E(expr);      // Cria objeto da expressão
        E.PosFixa();            // Converte a expressão de infixa para posfixa
        E.declara_var();        // Declara as variáveis

        cout << endl << "   Expressao Pos-Fixa: ";
        E.imprimir_posfixa();  // Imprime a expressao pos-fixa

        cout << endl << "   Resultado: " << E.resultado() << endl;   // Imprime o resultado da expressao

        cout << endl << "   Deseja continuar (S/N)? ";
        cin >> rep;
    }

    return 0;
}
