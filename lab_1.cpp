#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

const int N=50;
double coord[N][2];
int pop[N];

int numP=5;
int P[] = {0,1,2,3,4};

void readFile()
{
  ifstream df("data.dat");
  if(!df.is_open()) cout << "neatsidare failas" << endl;
  for(int i=0;i<N;i++)
  {
    df >> coord[i][0] >> coord[i][1] >> pop[i];
  }
}

void printData()
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
}

double HaversineDistance(int i, int j)
{
  double platSkirt = fabs(coord[i][0] - coord[j][0]);
  double ilgSkirt = fabs(coord[i][1] - coord[j][1]);
  double aa = pow((sin((double)platSkirt/(double)2*0.01745)),2) + cos(coord[i][0]*0.01745) * cos(coord[j][0]*0.01745) * pow((sin((double)ilgSkirt/(double)2*0.01745)),2);
  double c = 2 * atan2(sqrt(aa), sqrt(1-aa));
  double d = 6371 * c; 
  return d;
}

double getClosestDistance(int i, int* F, int numF)
{
  double mazAtstumas=HaversineDistance(i,*F);
  for(int j=0;j<numF;j++)
  {
    if(HaversineDistance(i, F[j]) < mazAtstumas)
    {
      mazAtstumas = HaversineDistance(i, F[j]); 
    }
  }
  return mazAtstumas;
}

double getUtilityOfX(int* X, int numX)
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
}

int main()
{
  int numX = 3;
  int X[] = {0,1,2};
  readFile();
  //printData(3);
  //cout << HaversineDistance(0, 1) << endl;
  //cout << getClosestDistance(0,P,numP) << endl; 
  //cout << getClosestDistance(0,X,numX) << endl; 
  cout << getUtilityOfX(X, numX) << endl;
}
