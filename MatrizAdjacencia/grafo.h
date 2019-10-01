#include<iostream>
#include<vector>

using namespace std;

class Grafo {
private:
	int V;
	vector< vector<int> > adj;
	bool digrafo;

public:
	Grafo(int V, bool digrafo);

	void adicionarVertice();
	void removerVertice(int v);

	void adicionarAresta(int v1, int v2);
	void removerAresta(int v1, int v2);
	
	int obterGrau(int v);
	void print();
};