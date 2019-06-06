#include <iostream>
#include <windows.h>

void mensagem(char texto[]) {
  std::cout << "A mensagem eh: " << texto << std::endl;
}

int main(void) {
  mensagem("hasudhausdhuasdhuasdhu");
  return 0;
}

int getrowscols(void) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    std::cout << "columns: " << columns << std::endl;
    std::cout << "rows: " << rows << std::endl;
    return 0;
}
