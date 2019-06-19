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
char n[120];


void cadastrar (string nome) {
  fstream file("teste2.t", ios_base::out | ios_base::binary | ios_base::app);
  strcpy(n, nome.c_str());
  file.write(reinterpret_cast<char*>(&n), sizeof(n));
  file.close();
}

void listar(struct cliente lista[]) {
  fstream file2("teste2.t", ios_base::in | ios_base::binary );
  file2.seekg(0, ios_base::end);

  long TAMANHO = file2.tellg();
  long NR_REGS = TAMANHO / sizeof(n);

  for (int i = 0; i < NR_REGS; i++) {
    string nome;
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
  file2.close();
}

int getSize(void) {
  fstream file2("teste2.t", ios_base::in | ios_base::binary );
  file2.seekg(0, ios_base::end);
  long TAMANHO = file2.tellg();
  long NR_REGS = TAMANHO / sizeof(n);
  file2.close();
  return NR_REGS;
}

string addFillZero(int number) {
  string n = to_string(number);
  if (n.length() == 1) {
      return "0" + n;
  }
  return n;
}

string  convertStructToString( cliente dados) {
  string ret, nome, dia, hora;
  nome = dados.nome;
  dia = addFillZero(dados.dia);
  hora = addFillZero(dados.hora);

  return nome + dia + hora;
}

int main(void) {
  cliente teste;

  teste.nome = "camila";
  teste.dia = 1;
  teste.hora = 8;
  string result = convertStructToString(teste);
  cadastrar(result);
  int n = getSize();
  cliente lista[n];
  listar(lista);

  long qtd = sizeof(lista) / (32 + 4 + 4);
  for (int i = 0; i < qtd; i++) {
    cout << "Nome: " << lista[i].nome << endl;
    cout << "Data: " << lista[i].dia << endl;
    cout << "Hora: " << lista[i].hora << endl;
    cout << "=====================================================" << endl;
  }
  return 0;
}


