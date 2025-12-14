#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
#include "lab_3.h"

using namespace std;

const int N=50;
int numP=5;
int P[] = {0,1,2,3,4};

Taskas* taskai = nullptr;
int kiekTasku = 0;

void readFile()
{
  ifstream df("data.dat");
  if(!df.is_open())
  {
    cout << "neatsidare failas" << endl;
    return;
  }

  double a,b;
  int c;

  while(df >> a >> b >> c && kiekTasku < N)
  {
    kiekTasku++;
  }
  df.close();

  taskai = new Taskas[kiekTasku];
  df.open("data.dat");
  int n=0;
  while(df >> a >> b >> c && n < N)
  {
    taskai[n].plat = a;
    taskai[n].ilg = b;
    taskai[n].pop = c;
    n++;
  }
  df.close();

}

/*void printData()
{
  for(int i=0;i<N;i++)
  {
    cout << coord[i][0] << " " << coord[i][1] << " " << pop[i] << endl;
  }
}

void printData(int n)
{
  for(int i=0;i<n;i++)
  {
    cout << coord[i][0] << " " << coord[i][1] << " " << pop[i] << endl;
  }
}*/

double HaversineDistance(Taskas* A, Taskas* B)
{
  double platSkirt = fabs(A->plat - B->plat);
  double ilgSkirt = fabs(A->ilg - B->ilg);
  double aa = pow((sin((double)platSkirt/(double)2*0.01745)),2) + cos(A->plat*0.01745) * cos(B->plat*0.01745) * pow((sin((double)ilgSkirt/(double)2*0.01745)),2);
  double c = 2 * atan2(sqrt(aa), sqrt(1-aa));
  double d = 6371 * c; 
  return d;
}
double** calculateMatrix(Taskas* taskai, int kiekTasku)
{
    double** mat = new double*[kiekTasku];

    for(int i=0; i<kiekTasku;i++)
    {
        mat[i] = new double[i+1];

        for(int j=0;j<=i;j++)
        {
            if(i==j)
            {
                mat[i][j] = 0.0; 
            }
            else
            {
                mat[i][j] = HaversineDistance(&taskai[i], &taskai[j]);
            }
        }
    }

    return mat;
}
// i kaip eilutes o j stulpeliai, i ir j yra taskai
void printMatrix(double** mat, int n, int kiekTasku)
{
  if(n>kiekTasku) n=kiekTasku;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<=i;j++)
    {
      cout << setprecision(1) << fixed << mat[i][j] << "\t";
    }
    cout << endl;
  }
}

double getDistance(int i, int j, double** mat)
{
  if(i==j) return 0.0;
  else if (i > j) {
    return mat[i][j];
  }
  else {
    return mat[j][i];
  }
}

double getClosestDistance(int miestas, int* obj, int kiekObj, double** mat)
{
  double mazAtstumas=getDistance(miestas, obj[0], mat);

  for(int i=1;i<kiekObj;i++)
  {
    double atstumas = getDistance(miestas, obj[i], mat);
    if(atstumas < mazAtstumas)
    {
      mazAtstumas = atstumas;
    }
  }
  return mazAtstumas;
}

double getUtilityOfX(int* X, int numX, double** mat)
{
  double naujuObjNaud=0.0;
  double visoGyventoju=0.0;
  for(int i=0;i<kiekTasku;i++)
  {
    visoGyventoju+=taskai[i].pop;
    double artEsantisAtst = getClosestDistance(i,P,numP,mat);
    double artNaujasAtst = getClosestDistance(i,X,numX,mat);
    if(artNaujasAtst<artEsantisAtst)
    {
      naujuObjNaud+=taskai[i].pop;
    }
    else if(artNaujasAtst==artEsantisAtst)
    {
      naujuObjNaud+=taskai[i].pop/3.0;
    }
  }
  return (naujuObjNaud / visoGyventoju) * 100.0;
}
bool isValid(int* X, int numX)
{
  for(int i = 0; i < numX; i++)
        for(int j = i+1; j < numX; j++)
            if(X[i] == X[j])
                return false;
    return true;
}
void generateCombo(int start, int kurisPildomas, int n, int* X, double** mat, double& didzNaud, int* gerX)
{
  if(kurisPildomas==n)
  {
    if(!isValid(X,n)) return;

    double naud = getUtilityOfX(X,n,mat);
    if(naud > didzNaud)
    {
      didzNaud = naud;
      for(int i = 0; i < n; i++){
        gerX[i] = X[i];
      }
    }
    return;
  }
    for(int i=start; i<=kiekTasku - (n - kurisPildomas); i++)
    {
      X[kurisPildomas] = i;
      generateCombo(i+1, kurisPildomas+1, n, X, mat, didzNaud, gerX);
    }
}
void findBest(int n, double** mat)
{
  int* X = new int[n];
  int* gerX = new int[n];
  double didzNaud = -1;
  
  generateCombo(0,0,n,X,mat,didzNaud,gerX);
  cout << "geriausias sprendinys, kai n = " << n << ": ";
  for(int i=0;i<n;i++)
  {
    cout << gerX[i] << " ";
  }
  cout << endl;
  cout << "Naudingumas: " << didzNaud << "%" << endl;
  delete[] X;
  delete[] gerX;

}
