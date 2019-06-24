#include <iostream>
#include <fstream>
#include <string>

#define DB "database.b"
#define TAMANHO_CHAR 120

struct cliente {
  std::string nome;
  int dia;
  int hora;
  bool status = true;
};

namespace bancodados {
  void start(void) {
    std::fstream arquivo(DB, std::ios_base::in | std::ios_base::binary);
    if (!arquivo.good())
      std::fstream arquivo(DB, std::ios_base::out | std::ios_base::binary);

    arquivo.close();
  }

  // Adiciona 0 caso seja 1 digito somente
  std::string _adicionaZero(int number) {
    std::string n = std::to_string(number);
    if (n.length() == 1) {
        return "0" + n;
    }
    return n;
  }

  // retorna a quantidade de itens cadastrados no arquivo
  int qtdCadastrados(void) {
    char dados[TAMANHO_CHAR];

    std::fstream arquivo(DB, std::ios_base::in | std::ios_base::binary);
    arquivo.seekg(0, std::ios_base::end);

    long tamanho = arquivo.tellg();
    long numero_registros = tamanho / sizeof(dados);

    arquivo.close();
    return numero_registros;
  }

  // convert struct para string para cadastrar
  std::string _converteStructParaString( cliente dados) {
    std::string ret, nome, dia, hora, status;

    nome = dados.nome;
    dia = _adicionaZero(dados.dia);
    hora = _adicionaZero(dados.hora);
    status = (dados.status) ? '1' : '0';

    return nome + dia + hora + status;
  }

  // cadastra struct convertendo para char
  void cadastrar (struct cliente dadosCliente){
    char dados[TAMANHO_CHAR];
    std::string dadosCadastro = _converteStructParaString(dadosCliente);

    strcpy(dados, dadosCadastro.c_str());

    std::ofstream arquivo(DB, std::ios_base::binary | std::ios_base::app );
    arquivo.write(reinterpret_cast<char*>(&dados), sizeof(dados));
    arquivo.close();
  }

  // lista todos clientes cadastrados por passagem de parametro por referencia
  void listar(struct cliente clientes[], bool debug = false) {
    char dados[TAMANHO_CHAR];
    std::ifstream arquivo(DB, std::ios_base::binary);

    arquivo.seekg(0, std::ios_base::end);

    long tamanho = arquivo.tellg();
    long numero_registros = tamanho / sizeof(dados);

    for (int i = 0; i < numero_registros; i++) {
      std::string c;
      arquivo.seekg(i * sizeof(dados), std::ios_base::beg);
      arquivo.read(reinterpret_cast<char*>(&dados), sizeof(dados));

      c.assign(dados);

      std::string nome = c.substr(0, c.length() - 5);
      int dia = stoi(c.substr(c.length() - 5, 2));
      int hora = stoi(c.substr(c.length() - 3, 2));
      int status = stoi(c.substr(c.length() - 1));

      clientes[i].nome = nome;
      clientes[i].dia = dia;
      clientes[i].hora = hora;
      clientes[i].status = (status == 1) ? true : false;


      if (debug) {
        std::cout << "Nome: " << nome << std::endl;
        std::cout << "Data: " << dia << std::endl;
        std::cout << "Hora: " << hora << std::endl;
        std::cout << "Status: " << status << std::endl;
        std::cout << "=====================================================" << std::endl;
      }
    }

    return;
  }

  // atualiza uma determinada linha do arquivo
  void atualizar(struct cliente dadosCliente, int pos) {
    char dados[TAMANHO_CHAR];
    std::string dadosCadastro = _converteStructParaString(dadosCliente);

    strcpy(dados, dadosCadastro.c_str());

    std::fstream arquivo(DB, std::ios_base::in | std::ios_base::out | std::ios_base::binary );
    arquivo.seekg(pos * sizeof(dados), std::ios_base::beg);
    arquivo.write(reinterpret_cast<char*>(&dados), sizeof(dados));
    arquivo.close();
  }
}
