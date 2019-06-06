// ECRA.H
// Arquivo de cabecalho para controle do video modo
// windows.h

// Constantes para as cores de texto e fundo

#define black     0 // Preto
#define blue      1 // Azul
#define green     2 // Verde
#define cyan      3 // Ciano
#define red       4 // Vermelho
#define magenta   5 // Magenta
#define brown     6 // Marrom
#define lgray     7 // Cinza claro
#define dgray     8 // Cinza escuro
#define lblue     9 // Azul claro
#define lgreen   10 // Verde claro
#define lcyan    11 // Ciano claro
#define lred     12 // Vermelho claro
#define lmagenta 13 // Magenta claro
#define yellow   14 // Amarelo
#define white    15 // Branco

// BIBLIO_ECRA.CPP
// Arquivo com codigo das funcoes da biblioteca ECRA.h

#include <iostream>
#include <windows.h>


void getRowCols(int &rows, int &cols) {
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  return;
}


// Limpar tela

void clear(void)
{
  int rows, cols;
  getRowCols(rows, cols);

  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD NewSBSize = GetLargestConsoleWindowSize(hOut);

  HANDLE TELA;
  DWORD ESCRITA = 0;
  COORD POS;
  TELA = GetStdHandle(STD_OUTPUT_HANDLE);
  std::cout << TELA << std::endl;
  POS.X = 0;
  POS.Y = 0;
  FillConsoleOutputCharacter(TELA, 32, cols * rows, POS,
    &ESCRITA);
  SetConsoleCursorPosition(TELA, POS);
  return;
}

// Posicionar cursor

void position(int LINHA, int COLUNA)
{
  HANDLE TELA;
  COORD POS;
  TELA = GetStdHandle(STD_OUTPUT_HANDLE);
  POS.X = COLUNA - 1;
  POS.Y = LINHA - 1;
  SetConsoleCursorPosition(TELA, POS);
  return;
}

// Limpar linha

void clearline(void)
{
  int rows, cols;
  getRowCols(rows, cols);

  HANDLE TELA;
  COORD POS;
  CONSOLE_SCREEN_BUFFER_INFO VIDEO;
  DWORD ESCRITA = 0;
  TELA = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(TELA, &VIDEO);
  POS.Y = VIDEO.dwCursorPosition.Y;
  POS.X = VIDEO.dwCursorPosition.X;
  FillConsoleOutputCharacter(TELA, 32, cols - POS.X , POS,
    &ESCRITA);
  return;
}

// Cor de texto e fundo

void color(int COR_FUNDO, int COR_TEXTO)
{
  HANDLE TELA;
  int COR;
  TELA = GetStdHandle(STD_OUTPUT_HANDLE);

  if (COR_FUNDO<0 and COR_FUNDO>15 and COR_TEXTO<0 and
    COR_TEXTO>15)
    COR = 15;
  else
    COR = COR_TEXTO - 1 + 16 * COR_FUNDO + 1;
  SetConsoleTextAttribute(TELA, COR);
  return;
}


