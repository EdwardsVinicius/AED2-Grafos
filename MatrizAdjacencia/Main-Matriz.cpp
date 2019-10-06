#include"grafo.h"

using namespace std;

int main() {
    Grafo grafo(5, true);

    grafo.adicionarAresta(0, 1, -1);
    grafo.adicionarAresta(0, 2, 4);
    grafo.adicionarAresta(1, 2, 3);
    grafo.adicionarAresta(1, 3, 2);
    grafo.adicionarAresta(1, 4, 2);
    grafo.adicionarAresta(3, 2, 5);
    grafo.adicionarAresta(3, 1, 1);
    grafo.adicionarAresta(4, 3, -3);

    grafo.printAll();
    grafo.bellmanFord(0);
    grafo.dijkstra(0);

    return 0;
}