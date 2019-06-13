#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

struct cliente {
  string nome;
  int data;
  int hora;
};

int main(void) {
  fstream file("teste.t", ios::out | ios::binary);
  char nome[10] = "matherique";
  file.write(reinterpret_cast<char*>(&c), sizeof(c));

}
