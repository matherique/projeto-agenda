#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include "bancodados.h"
#include "ecra.h"

using namespace std;

int opcao = 0;
int rows, cols;

cliente c[31][10];

void mensagem(string mensagem) {
  position(rows - 3, 1);
  cout << mensagem << endl;
}

void atualizaLista(void) {
  int n = bancodados::qtdCadastrados();
  cliente clientes[n];
  bancodados::listar(clientes);

  for (int x = 0; x < n; x++) {
    for (int i = 0; i < 31; i++) {
      for (int j = 0; j < 10; j++) {
        if (clientes[x].dia == (i + 1) && clientes[x].hora == (j + 8) && clientes[x].status == true) {
          c[i][j] = clientes[x];
        }
      }
    }
  }
}

void cabecalho(void) {
  color(0, 14);
  cout << "*** AGENDA PARA MARCACAO DE ATENDIMENTO ***" << endl;
  color(0, 15);
  cout << "\n\n";
}

void exibirMenu(void) {
  int o;
  cabecalho();
  cout << "MENU PRINCIPAL" << endl;
  cout << "\n\n";
  cout << "[1] MARCAR ATENDIMENTO" << endl;
  cout << "[2] DESMARCAR ATENDIMENTO" << endl;
  cout << "[3] LISTAR MARCACOES DO DIA" << endl;
  cout << "[4] CLIENTES MARCADOS NO DIA" << endl;
  cout << "[5] MAPA DOS HORARIOS LIVRES" << endl;
  cout << "[6] DEBUG" << endl;
  cout << "[7] FIM DO PROGRAMA" << endl;
  cout << '\n';
  cout << "==> ";
  cin >> opcao;
  cin.ignore(80, '\n');
}

void voltar(void){
  position(rows - 2, 1);
  color(0, 14);
  cout << "Tecle <Enter> para ir ao menu";
  color(0, 15);
  cin.get();
  clear();
  return;
}

void pegaDia(int &dia) {
  bool valido = false;
  cout << "INFORME O DIA .....: ";

  while (!valido) {
    cin >> dia;
    cin.ignore(80, '\n');

    if (dia >= 1 && dia <= 31) break;

    mensagem("DIA INVALIDO");
    position(7, 22);
    clearline();
  }
}

void pegaHora(int &hora, int dia, bool validaOcupado = true) {
  bool valido = false;
  cout << "INFORME A HORA ....: ";

  while (!valido) {
    cin >> hora;
    cin.ignore(80, '\n');
    if (hora < 8 || hora > 17) {
      mensagem("HORA INVALIDA");
      position(8, 22);
      clearline();
    } else if (c[dia - 1][hora - 8].nome != "" && validaOcupado) {
      mensagem("HORARIO OCUPADO");
      position(8, 22);
      clearline();
    } else {
      valido = true;
    }
  }
}

void marcarAtendimento(void) {
  atualizaLista();
  char nome[51];
  cliente cad_cliente;

  cabecalho();
  cout << "MARCAR ATENDIMENTO" << endl;
  cout << "\n\n";

  pegaDia(cad_cliente.dia);
  pegaHora(cad_cliente.hora, cad_cliente.dia);

  cout << "INFORME O NOME ....: ";
  cin.getline(nome, sizeof(nome));

  cad_cliente.nome.assign(nome);

  bancodados::cadastrar(cad_cliente);


  mensagem("SUCESSO: HORARIO AGENDADO" );
  voltar();
}

void desmarcarAtendimento(void) {
  atualizaLista();
  char resp;
  cliente rm_cliente;

  cabecalho();
  cout << "DESMARCAR ATENDIMENTO" << endl;
  cout << "\n\n";

  pegaDia(rm_cliente.dia);
  pegaHora(rm_cliente.hora, rm_cliente.dia, false);

  int n = bancodados::qtdCadastrados();
  cliente clientes[n];
  bancodados::listar(clientes);

  int id_cliente = -1;
  for (int i = 0; i < n; i++) {
    if (clientes[i].status == true && clientes[i].dia == rm_cliente.dia && clientes[i].hora == rm_cliente.hora) {
      id_cliente = i;
    }
  }

  if (id_cliente >= 0) {
    cout << "HORAIO RESERVADO PARA " << clientes[id_cliente].nome << "."<< endl;
    cout << "DESMARCA? (S/N): ";
    cin.get(resp);
    cin.ignore(80, '\n');

    if (toupper(resp) == 'S') {
      cliente cliente_atualizado;
      cliente_atualizado.nome = clientes[id_cliente].nome;
      cliente_atualizado.dia = clientes[id_cliente].dia;
      cliente_atualizado.hora = clientes[id_cliente].hora;
      cliente_atualizado.status = false;
      bancodados::atualizar(cliente_atualizado, id_cliente);

      mensagem("HORARIO LIBERADO");
      voltar();
    }
  } else {
    mensagem("ESTE HORARIO ESTA LIBERADO");
    voltar();
  }

  clear();
}

void listarMarcacoesDia(void) {
  int dia, i, horas[10];

  cabecalho();
  cout << "CLIENTES DO DIA" << endl;
  cout << "\n\n";

  pegaDia(dia);

  cout << '\n';
  cout << "LISTAGEM DE CLIENTES" << endl;
  cout << '\n';

//  int n = bancodados::qtdCadastrados();
//  cliente clientes[n];
//  bancodados::listar(clientes);
//  // TODO: Muita gambibarra, preciso ver um jeito melhor de fazer isso
//  for (i = 0; i < n; i++) {
//    if (clientes[i].status == true && clientes[i].dia == dia) {
//      horas[clientes[i].hora - 8] = i * (-1);
//    }
//  }

  for (i = 0; i < 10; i++) {
    if (c[dia - 1][i].nome != "") {
      cout << setw(3) << i + 8 << " HORAS   " << c[dia - 1][i].nome<< endl;
    } else {
      cout << setw(3) << i + 8 << " HORAS" << endl;
    }
  }
  voltar();
}

void clientesMarcadosDia (void) {
  int dia;
  char nm[TAMANHO_CHAR];
  string nome;

  cabecalho();
  cout << "HORARIOS DE UM CLIENTE" << endl;
  cout << "\n\n";

  cout << "ENTRE O NOME DO CLIENTE: ";
  cin.getline(nm, sizeof(nm));

  nome.assign(nm);

  cout << '\n';
  cout << "HORARIOS PARA O CLIENTE " << nome << endl;
  cout << '\n';


  int n = bancodados::qtdCadastrados();
  cliente clientes[n];
  bancodados::listar(clientes);

  for (int i = 0; i < n; i++) {
    if (clientes[i].status == true && clientes[i].nome.compare(nome) >= 0) {
      cout << " DIA " << clientes[i].dia << " AS " << clientes[i].hora << " HORAS " << endl;
    }
  }

  voltar();
}

void mapaHorarios (void) {
  int n = bancodados::qtdCadastrados();

  cliente clientes[n];
  bancodados::listar(clientes);

  int horarios[31][10];
  for (int i = 0; i < 31; i++) {
    for (int j = 0; j < 10; j++) {
      horarios[i][j] = 0;
    }
  }

  for (int i = 0; i < n; i++) {
    if (clientes[i].status == true) {
      int a = clientes[i].dia - 1;
      int b = clientes[i].hora - 8;
      horarios[a][b] = 1;
    }
  }

  cabecalho();
  cout << "MAPA DOS HORARIOS OCUPADOS" << endl;
  cout << "\n\n";

  cout << setiosflags(ios::right);
  cout << setw(5) << " HORA" << setw(11) << "1" << setw(10) << "2" << setw(11) << "3 " << endl;
  cout << setw(5) << "" << setw(11) << "1234567890" << setw(10) << "1234567890" << setw(10) << "12345678901" << endl;

  for (int j = 0; j < 10; j++) {
    cout << setw(5) << j + 8 << " ";
    for (int i = 0; i < 31; i++) {
      if (horarios[i][j] == 0)
        cout << ".";
      else
        cout << "*";
    }
    cout << endl;
  }

  voltar();
}

void debug(void) {
  for (int i = 0; i < 31; i++) {
    for (int j = 0; j < 10; j++) {
      if(c[i][j].nome != "") {
        if (c[i][j].status) {
            cout << "ATIVADO ";
        } else  {
          cout << "DESATIVADO ";
        }
        cout << "c[" << i << "][" << j << "] =  nome: " << c[i][j].nome << " dia: " << i + 1 << " hora: " << j + 8 << endl;
        cout << "========================================================================" << endl;
      }
    }
  }

  voltar();
}

int main (void) {
  bancodados::start();
  getRowCols(rows, cols);
  clear();

  while (opcao != 7) {
    exibirMenu();
    clear();
    if (opcao != 7){
      switch (opcao){
        case  1: marcarAtendimento();        break;
        case  2: desmarcarAtendimento();     break;
        case  3: listarMarcacoesDia();       break;
        case  4: clientesMarcadosDia();      break;
        case  5: mapaHorarios();             break;
        case  6: debug();             break;
      }
    }
  }
  return 0;
}
