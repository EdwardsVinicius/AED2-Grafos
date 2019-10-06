#include"grafo.h"

Grafo::Grafo(int V, bool digrafo){
	this->V = V;
	this->digrafo = digrafo;
	
	adj.resize(V);
	vertices.resize(V);

	this->auxResizeVertice();
}

void Grafo::adicionarVertice(){
	V++;
	adj.resize(V);
	vertices.resize(V);

	this->auxResizeVertice();
}

void Grafo::removerVertice(int v){
	if(v < V){
		V--;
		for(int i = 0; i < V; i++){
			vector<int>::iterator it = adj[i].begin() + v;
			adj[i].erase(it);
		}

		for(int i = 0; i < A; i++){
			if(arestas[i].origem == v || arestas[i].destino == v){
				vector<Aresta>::iterator it = arestas.begin() + i;
				arestas.erase(it);
			}
		}

		vector<vector<int>>::iterator it = adj.begin() + v;
		adj.erase(it);

		vector<int>::iterator it2 = vertices.begin() + v;
		vertices.erase(it2);
	}
	else{
		cout << "Vertice nao existe";
	}
}

void Grafo::adicionarAresta(int v1, int v2, int peso) {
	A++;
	arestas.resize(A);

	int i = A - 1;
	arestas[i].origem = v1;
	arestas[i].destino = v2;
	arestas[i].peso = peso;

	if(this->digrafo){
		adj[v1][v2]+=peso;
	}
	else{
		adj[v1][v2]+=peso;
		adj[v2][v1]+=peso;
	}
}

void Grafo::removerAresta(int v1, int v2){
	A--;

	for(int i = 0; i < A; i++){
		if(arestas[i].origem == v1 && arestas[i].destino == v2){
			vector<Aresta>::iterator it = arestas.begin() + i;
			arestas.erase(it);
		}
	}

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

void Grafo::printMatriz(){
	cout << "Matriz de Adjacencia"<< endl;
	for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
	cout << endl;
}

void Grafo::printVertices(){
	cout << "Vertices" << endl;
	for(int i = 0; i < V; i++){
		cout << vertices[i] << " ";
	}
	cout << endl << endl;
}

void Grafo::printArestas(){
	cout << "Arestas" << endl;
	for(int i = 0; i < A; i++){
		cout << arestas[i].origem << " --> " 
		<< arestas[i].destino << "\t peso: "
		<< arestas[i].peso << endl;
	}
	cout << endl;
}

void Grafo::printAll(){
	this->printMatriz();
	this->printVertices();
	this->printArestas();
}

void Grafo::buscaProfudindade(int v){
	vector<int> pilha;
	bool visitados[V]; // vetor de visitados
 
	// marca todos como não visitados
	for(int i = 0; i < V; i++)
		visitados[i] = false;
 
	while(true)
	{
		if(!visitados[v])
		{
			cout << "Visitando vertice " << v << " ...\n";
			visitados[v] = true; // marca como visitado
			pilha.push_back(v); // insere "v" na pilha
		}
 
		bool achou = false;
		vector<int>::iterator it;
 
		// busca por um vizinho não visitado
		for(it = adj[v].begin(); it != adj[v].end(); it++)
		{
			if(!visitados[*it])
			{
				achou = true;
				break;
			}
		}
 
		if(achou)
			v = *it; // atualiza o "v"
		else
		{
			// se todos os vizinhos estão visitados ou não existem vizinhos
			// remove da pilha
			pilha.pop_back();
			// se a pilha ficar vazia, então terminou a busca
			if(pilha.empty())
				break;
			// se chegou aqui, é porque pode pegar elemento do topo
			vector<int>::iterator it = pilha.end();
			v = *it;
		}
	}
}


void Grafo::bellmanFord(int origem){
	int distancia[V];
	int predecessor[V];

	for (int i = 0; i < V; i++){
        distancia[i] = INF;
		predecessor[i] = -1;
	}
    distancia[origem] = 0;

	for (int i = 1; i <= V - 1; i++) { 
        for (int j = 0; j < A; j++){
            int u = arestas[j].origem;
            int v = arestas[j].destino;
            int peso = arestas[j].peso;

            if (distancia[u] != INF && distancia[u] + peso < distancia[v]) 
                distancia[v] = distancia[u] + peso;
				predecessor[v] = u;
        }
    }

	for (int i = 0; i < A; i++) { 
        int u = arestas[i].origem;
        int v = arestas[i].destino;
        int peso = arestas[i].peso;

        if (distancia[u] != INF && distancia[u] + peso < distancia[v]){ 
            printf("Grafo tem ciclo negativo"); 
            return;
        } 
    }


	cout << "BellmanFord" << endl;
	this->printSolution(distancia, predecessor);
	

}

void Grafo::dijkstra(int origem){
	int distancia[V];
	int predecessor[V];
	bool visitado[V]; 

	for (int i = 0; i < V; i++){
        distancia[i] = INF;
		predecessor[i] = -1;
		visitado[i] = false;
	}
    distancia[origem] = 0;

	for (int count = 0; count < V - 1; count++) { 
        int u = this->distanciaMin(distancia, visitado); 
  
        visitado[u] = true; 
  
        for (int v = 0; v < V; v++) 
            if (!visitado[v] && adj[u][v] && distancia[u] != INF
                && distancia[u] + adj[u][v] < distancia[v]){

                distancia[v] = distancia[u] + adj[u][v];
				predecessor[v] = u;
			}
    }

	cout << "Dijkstra" << endl;
	this->printSolution(distancia, predecessor);

}

void Grafo::auxResizeVertice(){
	for(int i = 0; i < V; i++){
        adj[i].resize(V);
		vertices[i] = i;
    }
}

void Grafo::printSolution(int distancia[], int predecessor[]){
	cout << "Vertice   Distancia da origem	Predecessor\n" << endl; 
    for (int i = 0; i < V; ++i)
        cout << i << " \t\t " << distancia[i] << " \t\t " << predecessor[i] << endl; 
	cout << endl;
}

int Grafo::distanciaMin(int distancia[], bool visitado[]){
	int min = INF;
	int minIndex; 
  
    for (int v = 0; v < V; v++){
        if (visitado[v] == false && distancia[v] <= min){
            min = distancia[v];
			minIndex = v;
		}
	}
	
	return minIndex;
}