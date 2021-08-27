#include "SolveSquareEquation.h"


//----------------------------------------------------------------
//!  Program propose to user enter coefficient for square equation
//!  And program will solve it.
//----------------------------------------------------------------

int main () {

#ifdef DEBUG
    TestSolveSquare ();

#else
    double a = NAN, b = NAN, c = NAN;
    InputCoefficient (&a, &b, &c);

    double root1 = NAN, root2 = NAN;
    int nRoots = SolveSquare (a, b, c, &root1, &root2);
    OutputAnswer (nRoots, root1, root2);
#endif

    return 0;
}

