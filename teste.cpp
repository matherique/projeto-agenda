#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct cliente {
  string nome;
  int dia;
  int hora;
};

int main(void) {
  fstream file("teste2.t", ios_base::out | ios_base::binary | ios_base::app);
  string nome = "matheus henrique dos santos 2212";
  char n[120];

  strcpy(n, nome.c_str());
  file.write(reinterpret_cast<char*>(&n), sizeof(n));
  file.close();

  fstream file2("teste2.t", ios_base::in | ios_base::binary );
  file2.seekg(0, ios_base::end);
  long TAMANHO = file2.tellg();
  long NR_REGS = TAMANHO / sizeof(n);

  cliente lista[NR_REGS];

  for (int i = 0; i < NR_REGS; i++) {
    file2.seekg(i *  sizeof(n), ios_base::beg);
    file2.read(reinterpret_cast<char*>(&n), sizeof(n));
    nome.assign(n);
    string n = nome.substr(0, nome.length() - 4);
    int d = stoi(nome.substr(nome.length() - 4, 2));
    int h = stoi(nome.substr(nome.length() - 2));
    lista[i].nome = n;
    lista[i].dia = d;
    lista[i].hora = h;
  }

  long qtd = sizeof(lista) / (32 + 4 + 4);
  for (int i = 0; i < qtd; i++) {
    cout << "Nome: " << lista[i].nome << endl;
    cout << "Data: " << lista[i].dia << endl;
    cout << "Hora: " << lista[i].hora << endl;
    cout << "=====================================================" << endl;
  }


  file2.close();
  return 0;
}
