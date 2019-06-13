#include <iostream>
#include <fstream>
#include <string>

#define DB "database.abc"

struct cliente {
  std::string nome;
  int dia;
  int hora;
};

void start(void) {
  std::fstream arquivo(DB, std::ios_base::in | std::ios_base::binary);
  if (!arquivo.good())
    std::fstream arquivo(DB, std::ios_base::out | std::ios_base::binary);
}

void cadastrar (struct cliente dados){
  std::ofstream arquivo(DB, std::ios_base::binary | std::ios_base::app );
  arquivo.write(reinterpret_cast<char*>(&dados), sizeof(cliente));
  arquivo.close();
}

void listar() {
  std::fstream arquivo(DB, std::ios_base::in | std::ios_base::binary);
  arquivo.seekg(0, std::ios_base::end);
  long tArquivo= arquivo.tellg();

  int tStruct = sizeof(struct cliente);
  long n = tArquivo / tStruct;

  std::cout << "numero de itens: " << n << std::endl;

  for (int i = 0; i < n; i++) {
    cliente teste;
    std::cout << i * tStruct << std::endl;
    // arquivo.seekg(i * tStruct, std::ios_base::beg);
    arquivo.seekg(i * sizeof(struct cliente), std::ios_base::beg);
    arquivo.read(reinterpret_cast<char*>(&teste), sizeof(struct cliente));
    std::cout << "nome: " << teste.nome << std::endl;
//    std::cout << '\n';
  }

  arquivo.close();
}
