#ifndef SOLVESQUAREEQUATION_H_INCLUDED
#define SOLVESQUAREEQUATION_H_INCLUDED
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#define DEBUG


enum {
    INFINITY_ROOTS = -1,    //!<  Const in case of Infinity number of roots
    NO_ROOTS,               //!<  Const in case of No roots
    ONE_ROOT,               //!<  Const in case of Single root
    TWO_ROOTS               //!<  Const in case of two roots
};

const int NO = 0;
const int YES = 1;
const double NEAR_ZERO = 1e-100;      //!<  Accuracy of our calculations (gets by MathAnalysis)


int SolveSquare (double a, double b, double c, double* root1, double* root2);
bool IsEqual (double value, double compareValue);
double SolveLinear (double coefficientAtX, double freeMember);
void OutputAnswer (int nRoots, double root1, double root2);
void InputCoefficient (double* a, double* b, double* c);

#ifdef DEBUG
void TestSolveSquare ();
void PrintErrOfTest (int numberOfTest);
#endif


#endif // SOLVESQUAREEQUATION_H_INCLUDED
