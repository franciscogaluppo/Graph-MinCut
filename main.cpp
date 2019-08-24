/*
 * Trabalho Prático 2
 * Pesquisa Operacional 2019/1 - UFMG
 * 
 * Francisco Galuppo Azevedo
 * 2017014960
 *
 * Utiliza o algoritmo de Stoer-Wagner:
 * A Simple Min-Cut Algorithm, por MECHTHILD STOER e FRANK WAGNER 
*/

#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

#define INF 2147483647

using namespace std;

// Variáveis globais
int nv;
vector<bool> deletado;
vector<vector<int>> equivalente;

// st corte
pair<int,int> minimumCutPhase(vector<vector<int>> &g, int a)
{
	int n = g.size();

	// Cria vetores
	vector<bool> A (n, false);
	A[a] = true;

	vector<int> w (n, 0);

	// Calcula os pesos iniciais dos vértices
	for(int u = 0; u < n; u++)
		if(!deletado[u])
			w[u] = g[a][u];

	// Enquanto A <> V
	int prev = a;
	for(int i = 1; i < nv; i++)
	{
		// Acha o vértice mais "justo"
		int z = -1;
		for(int j = 0; j < n; j++)
			if(!deletado[j] && !A[j] && (z < 0 || w[j] > w[z]))
				z = j;
		
		A[z] = true;

		// Se for o caso, funde z e prev
		if(i == nv-1)
		{
			// Atualiza os pesos das arestas
			for(int j = 0; j < n; j++)
				g[j][prev] = g[prev][j] += g[z][j];

			// Marca prev como prev U z
			deletado[z] = true;
			for(auto u: equivalente[z])
				equivalente[prev].push_back(u);

			nv--;
			return make_pair(z, w[z]);
		}

		prev = z;

		// Atualiza os pesos
		for(int j = 0; j < n; j++)
			if(!A[j] && !deletado[j])
				w[j] += g[z][j];
	}
}

// Mínimo st corte
pair<vector<int>, int> minimumCut(vector<vector<int>> g, int a)
{
	// Valores
	int min = INF;
	vector<int> cut;
	pair<int,int> val;

	// Acha o mínimo dentre todos os st-cortes
	while(nv > 1)
	{
		val = minimumCutPhase(g, a);
		if(val.second < min)
		{
			min = val.second;
			cut = equivalente[val.first];
		}
	}

	return make_pair(cut, min);
}

int main()
{
	ios_base::sync_with_stdio(false);
	
	// Leitura das dimensões
	int n, m;
	cin >> n >> m;
	nv = n;

	// Leitura das arestas
	vector<vector<int>> g (n, vector<int> (n, 0));
	
	{
		int u, v, w;
		for(int i = 0; i < m; i++)
		{
			cin >> u >> v >> w;
			g[u][v] = g[v][u] = w;
		}
	}

	// Vértices restantes 
	vector<int> v (n);
	iota(v.begin(), v.end(), 0);

	// Reseta o vetor de deletados
	deletado.resize(n, false);
	equivalente.resize(n);
	for(int i = 0; i < n; i++)
		equivalente[i].push_back(i);

	// Calcula o corte e escreve saída
	pair<vector<int>, int> cut =  minimumCut(g, 0);
	cout << cut.first.size() << endl;
	for(auto u: cut.first)
		cout << u << " ";
	cout << endl << cut.second << endl;

	return 0;
}
