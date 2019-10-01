#include"grafo.h"

Grafo::Grafo(int V, bool digrafo){
	this->V = V;
	this->digrafo = digrafo;
	adj.resize(V);

	for(int i = 0; i < V; i++){
        adj[i].resize(V);
    }
}

void Grafo::adicionarVertice(){
	++V;
	adj.resize(V);
	for(int i = 0; i < V; i++){
        adj[i].resize(V);
    }
}

void Grafo::removerVertice(int v){
	if(v < V){
		V--;
		for(int i = 0; i < V; i++){
			vector<int>::iterator it = adj[i].begin() + v;
			adj[i].erase(it);
		}
		vector<vector<int>>::iterator it2 = adj.begin() + v;
		adj.erase(it2);
	}
	else{
		cout << "Vertice nao existe";
	}
}

void Grafo::adicionarAresta(int v1, int v2) {
	if(this->digrafo){
		adj[v1][v2]++;
	}
	else{
		adj[v1][v2]++;
		adj[v2][v1]++;
	}
}

void Grafo::removerAresta(int v1, int v2){
	if(this->digrafo){
		if(adj[v1][v2] != 0){
			adj[v1][v2]--;
		}
		else{
			cout << "\nErro! Aresta nao existe.\n";
		}
	}
	else{
		if(adj[v1][v2] != 0){
			adj[v1][v2]--;
			adj[v2][v1]--;
		}
		else{
			cout << "\nErro! Aresta nao existe.\n";
		}
	}
}

int Grafo::obterGrau(int v) {
	int grau = 0;
	for(int i = 0; i < V; i++){
		grau += adj[v][i];
	}
	return grau;
}

void Grafo::print(){
	cout << endl;
	for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            cout << " " << adj[i][j];
        }
        cout << endl;
    }
	cout << endl;
}