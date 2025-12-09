#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

struct Taskas{
  double plat;
  double ilg;
  int pop;

};


//const int N=50;
//double coord[N][2];
//int pop[N];
//int numP=5;
//int P[] = {0,1,2,3,4};

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

  while(df >> a >> b >> c)
  {
    kiekTasku++;
  }
  df.close();

  taskai = new Taskas[kiekTasku];
  df.open("data.dat");
  int n=0;
  while(df >> a >> b >> c)
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
/*double getClosestDistance(int i, int* F, int numF)
{
  double mazAtstumas=HaversineDistance(i,*F);
  for(int j=1;j<numF;j++)
  {
    if(HaversineDistance(i, F[j]) < mazAtstumas)
    {
      mazAtstumas = HaversineDistance(i, F[j]); 
    }
  }
  return mazAtstumas;
}*/

/*double getUtilityOfX(int* X, int numX)
{
  double naujuObjNaud=0.0;
  double visoGyventoju=0.0;
  for(int i=0;i<N;i++)
  {
    visoGyventoju+=pop[i];
    double artEsantisAtst = getClosestDistance(i,P,numP);
    double artNaujasAtst = getClosestDistance(i,X,numX);
    if(artNaujasAtst<artEsantisAtst)
    {
      naujuObjNaud+=pop[i];
    }
    else if(artNaujasAtst==artEsantisAtst)
    {
      naujuObjNaud+=pop[i]/3.0;
    }
  }
  return (naujuObjNaud / visoGyventoju) * 100.0;
}*/

int main()
{
  /*int numX = 3;
  int X[] = {5,6,7};
  readFile();
  printData(3);
  cout << HaversineDistance(0, 1) << endl;
  cout << getClosestDistance(0,P,numP) << endl; 
  cout << getClosestDistance(0,X,numX) << endl; 
  cout << getUtilityOfX(X, numX) << endl;*/
  readFile();
  cout << "nuskaityta tasku: " << kiekTasku << endl;
  double** matrica = calculateMatrix(taskai, kiekTasku);
  printMatrix(matrica, 10, kiekTasku);

  int a=4, b=2;
  cout << "atstumas tarp tasku " << a << " ir " << b << " yra: " << getDistance(a,b,matrica) << endl;

}
