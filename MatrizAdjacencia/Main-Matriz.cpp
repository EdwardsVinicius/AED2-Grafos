#include"grafo.h"

using namespace std;

int main() {
    Grafo grafo(4, true);

    grafo.adicionarAresta(0, 1);
    grafo.adicionarAresta(0, 2);
    grafo.adicionarAresta(0, 3);
    grafo.adicionarAresta(1, 3);
    grafo.adicionarAresta(2, 3);
    grafo.adicionarAresta(3, 2);

    grafo.print();

    return 0;
}