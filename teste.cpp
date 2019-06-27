#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <typeinfo>
#define DB "teste.b"
using namespace std;

int main(void) {
  string n1 = "matheus";
  char n2[] = "matheus  ";
  if (n1 == n2) {
    cout << "iguais";
  } else {
    cout << "diferentes";
  }
  cout << endl;
  return 0;
}
