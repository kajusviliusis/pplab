#ifndef LAB3_H
#define LAB3_H

struct Taskas {
    double plat;
    double ilg;
    int pop;
};

extern int numP;
extern int P[];
extern Taskas* taskai;
extern int kiekTasku;

void readFile();
double HaversineDistance(Taskas* A, Taskas* B);
double** calculateMatrix(Taskas* taskai, int kiekTasku);
double getDistance(int i, int j, double** mat);
double getClosestDistance(int miestas, int* obj, int kiekObj, double** mat);
double getUtilityOfX(int* X, int numX, double** mat);
bool isValid(int* X, int numX);
void generateCombo(int start, int kurisPildomas, int n, int* X, double** mat, double& didzNaud, int* gerX);
void findBest(int n, double** mat);
#endif

