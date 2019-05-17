#ifndef PILHADIM_H
#define PILHADIM_H

#include <cassert>
#include <iostream>

#define BLOCO 10

using namespace std;

/*
    Biblioteca com o objeto pilha DINAMICA e para qualquer tipo.
*/

template <class T>
class Pilha
{
    private:
        T *dados;
        int topo, capacidade;

    public:
        Pilha(int cap = BLOCO)        /// Aloca e inicializa a pilha
        {
            assert(cap>1);
            dados = new T[cap];
            topo = -1;
            capacidade = cap;
        }
        bool vazia()                /// Verifica se a pilha está vazia
        {
            //return (topo==-1);
            if(topo == -1)
                return true;
            else
                return false;

        }
        void realocar()         /// Realoca a pilha
        {
            T *aux = new T[capacidade+BLOCO];
            for(int i=0; i<capacidade; i++)
                aux[i] = dados[i];

            delete []dados;
            dados = aux;
            capacidade += BLOCO;
        }

        void empilha(T elem)      /// Acrescenta mais um valor no topo da pilha
        {
            if(topo+1 == capacidade)
            {
                realocar();
                dados[++topo] = elem;
            }
            else
            {
                dados[++topo] = elem;
            }
        }

        T desempilha()            /// Retorna e remove o valor do topo da pilha
        {
            assert(!vazia());
                return dados[topo--];
        }

        T analiza_topo()
        {
            if(!vazia())
            return dados[topo];

        }

        void inverter()             /// Inverte os dados da pilha
        {
            int p = top();
            for(int i = 0; i <= (top()+1)/2; i++)
            {
                    T aux1 = dados[i];
                    T aux2 = dados[p];
                    dados[i] = aux2;
                    dados[p] = aux1;
                    p--;
            }
        }

        int top()                   /// Retorna a posição do topo
        {
            return topo;
        }

        int cap()                   /// Retorna a capacidade
        {
            return capacidade;
        }

        void imprimir()             /// Imprime toda a pilha
        {
            if(vazia() != true)
            {
                cout << "[ ";
                for(int i = 0; i <= topo; i++)
                {
                    cout << dados[i] << " ";
                }
                cout << "]" << endl;
            }
            else
                cout << "Pilha Vazia!" << endl;
        }

        ~Pilha()                    /// Desaloca a pilha
        {
            if(dados)
            {
                delete []dados;
            }
        }
};
#endif // PILHADIM_H




