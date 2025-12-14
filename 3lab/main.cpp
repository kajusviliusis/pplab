#include <iostream>
#include "lab_3.h"
#include <iostream>
using namespace std;

int main()
{
  readFile();
  cout << "nuskaityta tasku: " << kiekTasku << endl;
  double** matrica = calculateMatrix(taskai, kiekTasku);

  findBest(3, matrica);

  for(int i = 0; i < kiekTasku; i++){
      delete[] matrica[i];
  }
    delete[] matrica;

    delete[] taskai;
}
