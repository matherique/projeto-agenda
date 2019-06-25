#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <typeinfo>
#define DB "teste.b"
using namespace std;

struct cliente {
  string nome = "matheus h";
  int dia = 2;
  int hora = 12;
};


void cadastrar(struct cliente dados) {
  ofstream arquivo(DB, ios_base::binary | ios_base::app);
  arquivo.write(reinterpret_cast<char*>(&dados.nome), sizeof(dados.nome));
  arquivo.close();
}

int main(void) {
  cliente teste;

  cadastrar(teste);

  ifstream arquivo(DB, ios_base::binary);
  cliente dados;

  arquivo.seekg(0, ios_base::end);

  long tamanho = arquivo.tellg();
  long numero_registros = tamanho / sizeof(dados);

  for (int i = 0; i < numero_registros; i++) {
//    char nome[51];
    c nome;
    int dia, hora;
    cout << i * sizeof(nome) << " - " << sizeof(nome) << endl;
    arquivo.seekg(i * sizeof(nome), ios_base::beg);
    arquivo.read(reinterpret_cast<char*>(&nome), sizeof(nome));

//    arquivo.seekg((i * sizeof(dados)) + sizeof(nome), ios_base::beg);
//    arquivo.read(reinterpret_cast<char*>(&dia), sizeof(dia));

//    arquivo.seekg((i * sizeof(dados)) + sizeof(nome) + sizeof(dia), ios_base::beg);
//    arquivo.read(reinterpret_cast<char*>(&hora), sizeof(hora));

    cout << "Nome: " << nome << endl;
    cout << "Data: " << dia << endl;
    cout << "Hora: " << hora << endl;
    cout << "=====================================================" << endl;
  }
  arquivo.close();

  return 0;
}
