#ifndef EXPRESSOES_H
#define EXPRESSOES_H

#include "pilha.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

/*
    Biblioteca com o objeto Expressao Aritmética e atributos para
    criação da expressão Pós-Fixa, e a análise dessa expressão.
*/

struct Variavel     /// Estrutura para armazenamento das variáveis
{
    string nome;
    float valor;
};

class Expressao
{
    private:
        string exp;                 // Expressao aritmetica original
        Pilha <char> posFixa;       // Pilha para a expressao pos fixa
        Pilha <char> Operadores;    // Pilha para armazenar os operadores
        Pilha <string> Estatica;    // Pilha auxilixar para analise da pilha pos fixa
        Variavel *Vars;             // Vetor de váriáveis
        int quant_vars;             // Quantidade de variaveis usadas

    public:

    Expressao(string expressao)
    {
        exp = expressao;
    }

    void PosFixa()                  /// Analiza a expressão e gera a pilha da expressao pos-fixa
    {
        int tam = exp.length();
        for(int i=0; i < tam; i++)
        {
            if(eoperando(exp[i]))
            {
                posFixa.empilha(exp[i]);
            }
            else
            {
                if(exp[i] == '(')
                {
                    Operadores.empilha(exp[i]);
                }
                else if(exp[i] == ')')
                {
                    char aux = ' ';
                    while(aux != '(')
                    {
                        aux = Operadores.desempilha();
                        if(aux != '(')
                        {
                            posFixa.empilha(aux);
                        }
                    }
                }
                else
                {
                    int repetir = 1;
                    while(repetir)
                    {
                        char y = Operadores.analiza_topo();
                        if(!Operadores.vazia() && y != '(' && precedencia(y, exp[i]))
                            posFixa.empilha(Operadores.desempilha());
                        if(Operadores.vazia() || y == '(' || !precedencia(y, exp[i]))
                        {
                            Operadores.empilha(exp[i]);
                            repetir=0;
                        }
                    }
                }
            }
        }
        while(!Operadores.vazia())
        {
            posFixa.empilha(Operadores.desempilha());
        }
    }

    string resultado()             /// Analiza a expressão Pós-Fixa e retorna o resultado
    {
        posFixa.inverter();
        while(!posFixa.vazia())
        {
            char v = posFixa.desempilha();
            if(eoperando(v))
            {
                string aux = converterforstring(v);
                float valor = retorna_valor_var(aux);
                Estatica.empilha(converterforstring(valor));
            }
            else
            {
                string var1 = Estatica.desempilha();
                string var2 = Estatica.desempilha();
                string r = operacao(v, var2, var1);
                Estatica.empilha(r);
            }
        }
        return Estatica.analiza_topo();
    }

    void declara_var()             /// Analiza a expressao e solicita o valor de cada variavel usada
    {
        Vars = new Variavel[exp.length()];
        int c = 0, tam = exp.length();
        float v;

        cout << endl<< "   Declarando Valor das Variaveis: " << endl;
        cout << "   Pode-se usar valores flutuantes para cada variavel." << endl;
        for(int i=0; i < tam; i++)
        {
            if(eoperando(exp[i]))
            {
                if(!var_declarada(converterforstring(exp[i]), c))
                {
                    cout << "   " << exp[i] << " : ";
                    cin >> v;
                    Vars[c].nome = converterforstring(exp[i]);
                    Vars[c].valor = v;
                    c++;
                }
            }
        }
        quant_vars = c;
    }

    bool eoperando(char token)     /// Verifica se o caracter é um operado ou operador (False - Operador | True - Operando)
    {
        if(token == '+' || token == '-' || token == '*' || token == '/' || token == ' ' || token == '(' || token == ')' )
            return false;
        else
            return true;
    }

    int prioridade(char token)     /// Retorna a prioridade do operador
    {
        if(token == '+' || token == '-')
            return 1;               // Prioridade Media
        else if(token == '*' || token == '/')
            return 2;               // Maior Prioridade
        else
            return 0;               // Menor Prioridade
    }

    string operacao(char operador, string v1, string v2)   /// Retorna o resultado da operação entre os valores passados
    {
        float valor;
        float op1 = strtof((v1).c_str(),0); // Conversão string para float
        float op2 = strtof((v2).c_str(),0); // Conversão string para float

        switch(operador)    // Calcula a operação de acordo com o operador passado
        {
            case '+':
                valor =  op1 + op2;
            break;
            case '-':
                valor =  op1 - op2;
            break;
            case '*':
                valor =  op1 * op2;
            break;
            case '/':
                valor = op1 / op2;
            break;
        }
        return converterforstring(valor);       // Retorna o resultado em string para ser empilhado
    }

    bool precedencia(char token1, char token2)   /// Verifica se o operador token1 tem maior ou a mesma precedencia de token2
    {
        if(prioridade(token1) >= prioridade(token2))
            return true;
        else
            return false;
    }

    bool var_declarada(string var, int q)     /// Verifica se a variável passada já foi declarada
    {
        bool d = false;
        for(int i = 0; i < q; i++)
        {
            if(Vars[i].nome == var)
                d = true;
        }
        return d;
    }

    float retorna_valor_var(string var)      /// Retorna o valor da variável declarada
    {
        for(int i=0; i< quant_vars; i++)
            if(Vars[i].nome == var)
                return Vars[i].valor; // É garantido o retorno do valor, já que foi declarado pelo usuário antes da analise
    }

    string converterforstring(float valor)      /// Converte o valor float para string
    {
        return to_string(valor);
    }

    void imprimir_posfixa()         /// Imprime a Pilha Pos-Fixa
    {
        posFixa.imprimir();
    }

    void imprimir_operadores()      /// Imprime a Pilha de Operadores
    {
        Operadores.imprimir();
    }

    void imprime_vars()             /// Imprime a Pilha de Variaveis
    {
        for(int i=0; i< quant_vars; i++)
            cout << "     " << Vars[i].nome << " - " << Vars[i].valor << endl;
    }

    void imprimir_estatica()        /// Imprime a Pilha Estatica
    {
        Estatica.imprimir();
    }

};

#endif // EXPRESSOES_H

