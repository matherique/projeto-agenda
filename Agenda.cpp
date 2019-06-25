#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include "bancodados.h"
#include "ecra.h"

using namespace std;

int opcao = 0;
int rows, cols;


void mensagem(string mensagem) {
  position(rows - 3, 1);
  cout << mensagem << endl;
}

void cabecalho(void) {
  color(0, 14);
  cout << "*** AGENDA PARA MARCACAO DE ATENDIMENTO ***" << endl;
  color(0, 15);
  cout << "\n\n";
}

void exibirMenu(void) {
  cabecalho();
  cout << "MENU PRINCIPAL" << endl;
  cout << "\n\n";
  cout << "[1] MARCAR ATENDIMENTO" << endl;
  cout << "[2] DESMARCAR ATENDIMENTO" << endl;
  cout << "[3] LISTAR MARCACOES DO DIA" << endl;
  cout << "[4] CLIENTES MARCADOS NO DIA" << endl;
  cout << "[5] MAPA DOS HORARIOS LIVRES" << endl;
  cout << "[6] FIM DO PROGRAMA" << endl;
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

bool horarioOcupado(int dia, int hora) {
  int i = 0;
  bool ocupado = false;

  int n = bancodados::qtdCadastrados();
  cliente clientes[n];
  bancodados::listar(clientes);

  while (i < n){
    if (clientes[i].dia == dia && clientes[i].hora == hora && clientes[i].status == true) {
      ocupado = true;
      break;
    }
    i++;
  }
  return ocupado;
}

int pegaDia() {
  int dia;
  cout << "INFORME O DIA .....: ";

  while (true) {
    cin >> dia;
    cin.ignore(80, '\n');

    if (dia >= 1 && dia <= 31) break;

    mensagem("DIA INVALIDO");
    position(7, 22);
    clearline();
  }
  return dia;
}

int pegaHora() {
  int hora;
  cout << "INFORME A HORA ....: ";

  while (true) {
    cin >> hora;
    cin.ignore(80, '\n');
    if (hora >= 8 &&  hora <= 17) break;

    mensagem("HORA INVALIDA");
    position(8, 22);
    clearline();
//    if (hora < 8 || hora > 17) {
//      mensagem("HORA INVALIDA");
//      position(8, 22);
//      clearline();
//    } else {
//      valido = true;
//    }
  }

  return hora;
}

void marcarAtendimento(void) {
  char nome[51];
  int dia, hora;
  cliente cadastrarCliente;

  cabecalho();
  cout << "MARCAR ATENDIMENTO" << endl;
  cout << "\n\n";

  dia = pegaDia();
  hora = pegaHora();

  if (horarioOcupado(dia, hora)) {
    mensagem("HORARIO OCUPADO");
  } else {
    cout << "INFORME O NOME ....: ";
    cin.getline(nome, sizeof(nome));

    cadastrarCliente.nome.assign(nome);
    cadastrarCliente.dia = dia;
    cadastrarCliente.hora = hora;

    bancodados::cadastrar(cadastrarCliente);

    mensagem("SUCESSO: HORARIO AGENDADO" );
  }
  voltar();
}

void desmarcarAtendimento(void) {
  char resp;
  int dia, hora;

  cabecalho();
  cout << "DESMARCAR ATENDIMENTO" << endl;
  cout << "\n\n";

  dia = pegaDia();
  hora = pegaHora();

  int n = bancodados::qtdCadastrados();
  cliente clientes[n];
  bancodados::listar(clientes);

  int posicao = -1;
  for (int i = 0; i < n; i++) {
    if (clientes[i].status == true && clientes[i].dia == dia && clientes[i].hora == hora) {
      posicao = i;
    }
  }

  if (posicao >= 0) {
    cout << "HORAIO RESERVADO PARA " << clientes[posicao].nome << "."<< endl;
    cout << "DESMARCA? (S/N): ";
    cin.get(resp);
    cin.ignore(80, '\n');

    if (toupper(resp) == 'S') {
      cliente clienteAtualizar = clientes[posicao];
      clienteAtualizar.status = false;

      bancodados::atualizar(clienteAtualizar, posicao);

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
  int dia, horas[10];

  cabecalho();
  cout << "CLIENTES DO DIA" << endl;
  cout << "\n\n";

  dia = pegaDia();

  cout << '\n';
  cout << "LISTAGEM DE CLIENTES" << endl;
  cout << '\n';

  int n = bancodados::qtdCadastrados();
  cliente clientes[n];
  bancodados::listar(clientes);

  for (int i = 0; i < 10; i++)
    horas[i] = -1;

  for (int i = 0; i < n; i++) {
    int h = clientes[i].hora - 8;
    if (clientes[i].status == true && clientes[i].dia == dia) {
      horas[h] = i;
    }
  }

  for (int i = 0; i < 10; i++) {
    if (horas[i] >= 0) {
      int index = horas[i];
      cout << setw(3) << i + 8 << " HORAS   " << clientes[index].nome<< endl;
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

int main (void) {
  bancodados::start();
  getRowCols(rows, cols);
  clear();

  while (opcao != 6) {
    exibirMenu();
    clear();
    if (opcao != 6){
      switch (opcao){
        case  1: marcarAtendimento();        break;
        case  2: desmarcarAtendimento();     break;
        case  3: listarMarcacoesDia();       break;
        case  4: clientesMarcadosDia();      break;
        case  5: mapaHorarios();             break;
      }
    }
  }
  return 0;
}
