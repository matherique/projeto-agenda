#include <windows.h>
#include <iostream>
#include "bancodados.h"
#include "ecra.h"
#include <string>
using namespace std;

int opcao = 0;
int rows, cols;

struct cliente {
  string nome;
  int dia;
  int hora;
};

void exibirMenu(void) {
  int o;
  color(0, 14); cout << "*** AGENDA PARA MARCACAO DE ATENDIMENTO ***" << endl; color(0, 15);
  cout << "\n\n";
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
  color(0, 14); cout << "Tecle <Enter> para ir ao menu"; color(0, 15);
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
    if (dia < 1 || dia > 31) {
      position(rows - 3, 1);
      cout << "Dia invalido";
      position(7, 22);
      clearline();
    } else {
      valido = true;
    }
  }
}

void pegaHora(int &hora) {
  bool valido = false;
  cout << "INFORME A HORA ....: ";
  while (!valido) {
    cin >> hora;
    cin.ignore(80, '\n');
    if (hora < 8 || hora > 17) {
      position(rows - 3, 1);
      cout << "Hora invalida";
      position(8, 22);
      clearline();
    } else {
      valido = true;
    }
  }
}

void marcarAtendimento(void) {
  int dia, hora;
  char nome[51];
  cliente cad_cliente;

  color(0, 14); cout << "*** AGENDA PARA MARCACAO DE ATENDIMENTO ***" << endl; color(0, 15);
  cout << "\n\n";
  cout << "MARCAR ATENDIMENTO" << endl;
  cout << "\n\n";

  pegaDia(cad_cliente.dia);
  pegaHora(cad_cliente.hora);

  cout << "INFORME O NOME ....: ";
  cin.getline(nome, sizeof(nome));
  cad_cliente.nome.assign(nome);

//  debug
//  cout << "Dia: |" << cad_cliente.dia << "|" << endl;
//  cout << "Hora: |" << cad_cliente.hora << "|" << endl;
//  cout << "Nome: |" << cad_cliente.nome << "|" << endl;


  position(rows - 3, 1);
  cout << "SUCESSO: HORARIO AGENDADO" << endl;
  voltar();
}


int main (void) {
  getRowCols(rows, cols);
  while (opcao != 6) {
    exibirMenu();
    clear();
    if (opcao != 6){
      switch (opcao){
        case  1: marcarAtendimento();        break;
        //case  2: desmarcarAtendimento();     break;
        //case  3: listarMarcacoesDia();       break;
        //case  4: clientesMarcadosDia();      break;
        //case  5: mapaHorarios();             break;
      }
    }
  }

  return 0;
}
