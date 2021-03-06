// Algoritmo de PRIM.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<sstream>
#include <algorithm>
#include<queue>

std::ifstream arquivo;
struct node {
	int id;
	long valor;
	std::vector<int> vizinhos;
	std::vector<long> distancia;
	node* Pai;
	bool terminou;
};

class comp
{
public:
	bool operator() (const node& lhs, const node&rhs) const
	{
		return (lhs.valor>rhs.valor);
	}
};


std::priority_queue<node, std::vector<node>, comp > filaPrioridade;
std::vector<node> vertices;
int  numVertices;

void printar() {
	std::cout << std::endl << "Vertices: ";
	for (int i = 0; i < vertices.size(); i++) {
		std::cout << "Id:" << vertices[i].id << std::endl;
		std::cout << "Valor:" << vertices[i].valor << std::endl;
		for (int j = 0; j < vertices[i].vizinhos.size(); j++) {
			std::cout << " Vizinhos:" << vertices[i].vizinhos[j] << std::endl;
		}
		for (int j = 0; j < vertices[i].distancia.size(); j++) {
			std::cout << " Distancia:" << vertices[i].distancia[j] << std::endl;
		}
		std::cout << "--------------------------------------------------------------" << std::endl;
	}
}




int criaGrafo() {
	std::string arquivoname;
	std::cout << "PRIM:" << std::endl << "Digite o nome do arquivo(ex. exemplo.txt): ";
	std::cin >> arquivoname;
	arquivo.open(arquivoname);
	if (!arquivo.is_open()) {
		return -1;
	}
	int i, j, aux;
	std::string stringer, num;
	node no, zero;
	std::getline(arquivo, stringer);
	numVertices = std::stoi(stringer);
	for (i = 0; i < numVertices; i++) {
		if (i == 0) {
			no.valor = 0;
		}
		else {
			no.valor = LONG_MAX;
			no.terminou = 0;
		}
		no.id = i;
		no.Pai = NULL;
		vertices.push_back(no);
		no = zero;
	}
	int col, linha;
	col = 1;
	linha = 0;
	while (!arquivo.eof()) {
		std::stringstream a;
		std::getline(arquivo, stringer);
		a << stringer;
		aux = col;
		while (a >> num) {
			vertices[linha].vizinhos.push_back(col);
			vertices[col].vizinhos.push_back(linha);
			vertices[linha].distancia.push_back(std::stoi(num));
			vertices[col].distancia.push_back(std::stoi(num));
			col++;
		}
		linha++;
		aux++;
		col = aux;
	}

}


int main() {
	int i;
	int tamArvoreMin = 0;
	criaGrafo();
	for (i = 0; i < vertices[0].vizinhos.size(); i++) {
		vertices[vertices[0].vizinhos[i]].Pai = &vertices[0];
		tamArvoreMin += vertices[0].distancia[i];
		vertices[vertices[0].vizinhos[i]].valor = vertices[0].distancia[i];
		filaPrioridade.push(vertices[vertices[0].vizinhos[i]]);
	}
	vertices[0].terminou = 1;
	while (filaPrioridade.size() != 0) {
		int indice;
		indice = filaPrioridade.top().id;
		filaPrioridade.pop();
		for (int i = 0; i < vertices[indice].vizinhos.size(); i++) {
			if (vertices[vertices[indice].vizinhos[i]].terminou == 0 && vertices[indice].distancia[i] < vertices[vertices[indice].vizinhos[i]].valor) {
				if (vertices[vertices[indice].vizinhos[i]].Pai == NULL) {
					tamArvoreMin += vertices[indice].distancia[i];
				}
				else {
					tamArvoreMin -= vertices[vertices[indice].vizinhos[i]].valor;
					tamArvoreMin += vertices[indice].distancia[i];
				}	
				vertices[vertices[indice].vizinhos[i]].Pai = &vertices[indice];
				vertices[vertices[indice].vizinhos[i]].valor = vertices[indice].distancia[i];
				filaPrioridade.push(vertices[vertices[indice].vizinhos[i]]);
			}
			vertices[indice].terminou = 1;			
		}
	}
	std::cout << tamArvoreMin << std::endl;
	system("pause");

}