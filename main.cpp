#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>



const int INFINITY_ROOTS = -1;        //!<  Const in case of Infinity number of roots
const int NO_ROOTS = 0;               //!<  Const in case of No roots
const int ONE_ROOT = 1;               //!<  Const in case of Single root
const int TWO_ROOTS = 2;              //!<  Const in case of two roots
const int NO = 0;
const int YES = 1;
const double NEAR_ZERO = 1e-100;      //!<  Accuracy of our calculations (gets by MathAnalysis)


int SolveSquare (double a, double b, double c, double* root1, double* root2);
bool IsEqual (double value, double compareValue);
double SolveLinear (double coefficientAtX, double freeMember);
void OutputAnswer (int nRoots, double root1, double root2);
void InputCoefficient (double* a, double* b, double* c);
void TestSolveSquare ();
void PrintErrOfTest (int numberOfTest);


//! Structure to keep tests for function TestSolveSquare()

struct paramTests {
    double a;           //!<  Coefficient of equation for x^2
    double b;           //!<  Coefficient of equation for x
    double c;           //!<  Coefficient of equation for free member
    int nRoots;         //!<  Number of roots
    double root1;       //!<  First solution of equation
    double root2;       //!<  Second solution of equation
};


int main () {
    double a = NAN, b = NAN, c = NAN;
    InputCoefficient (&a, &b, &c);

    double root1 = NAN, root2 = NAN;
    int nRoots = SolveSquare (a, b, c, &root1, &root2);
    OutputAnswer (nRoots, root1, root2);
    //TestSolveSquare ();

    return 0;
}



//----------------------------------------------------------------
//!  Program solve square equation a*x^2 + b*x + c = 0
//!  @param  [in]   a - coefficient
//!  @param  [in]   b - coefficient
//!  @param  [in]   c - coefficient
//!  @param  [out]   root1 - pointer to the 1st root
//!  @param  [out]   root2 - pointer to the 2nd root
//!  @return Number of roots
//!  @note In case of infinity number of roots program return INFINITY_ROOTS
//!  @copyright AlexZ (Idea of Ded;))
//----------------------------------------------------------------

int SolveSquare (double a, double b, double c, double* root1, double* root2) {

    assert (!isnan (a));
    assert (!isnan (b));
    assert (!isnan (c));
    assert (root1 != NULL);
    assert (root2 != NULL);


    if (IsEqual(a, 0.0)) {
        if (IsEqual(b, 0.0)) {
            if (IsEqual(c, 0.0)) {
                return INFINITY_ROOTS;
            }
            else {
                return NO_ROOTS;
            }
        }
        else {
            *root1 = SolveLinear(b, c);
            return ONE_ROOT;
        }
    }
    else {
        double discriminant = pow (b, 2.0) - 4*a*c;

        if (discriminant < 0) {
            return NO_ROOTS;
        }
        else if (IsEqual(discriminant, 0.0)) {
            *root1 = SolveLinear(2*a, b);
            return ONE_ROOT;
        }
        else {
            *root1 = (-b + sqrt (discriminant)) / (2*a);
            *root2 = (-b - sqrt (discriminant)) / (2*a);
            return TWO_ROOTS;
        }
    }
}

//----------------------------------------------------------------
//!  Compare two double numbers
//!  @param [in] value - first number
//!  @param [in] compareValue - second number
//!  @return Is this two numbers equal?
//----------------------------------------------------------------

bool IsEqual (double value, double compareValue) {

    assert (!isnan (value));
    assert (!isnan (compareValue));

    return (fabs (value - compareValue) < NEAR_ZERO);
}



//----------------------------------------------------------------
//!  Program solve linear equation coefficientAtX * x + freeMember = 0
//!  Program solve square equation a*x^2 + b*x + c = 0
//!  @param  [in]   coefficientAtX - coefficient
//!  @return Decision of equation
//!  @note Decision must exist!
//----------------------------------------------------------------

double SolveLinear (double coefficientAtX, double freeMember){

    assert (coefficientAtX != 0);
    assert (!isnan (coefficientAtX));
    assert (!isnan (freeMember));

    return -freeMember/coefficientAtX;
}


//----------------------------------------------------------------
//!  Program printing answer of equation
//!  @param  [in]   nRoots - number of roots
//!  @param  [in]   root1 - first root of equation
//!  @param  [in]   root2 - second root of equation
//----------------------------------------------------------------

void OutputAnswer (int nRoots, double root1, double root2) {

    switch (nRoots){
        case NO_ROOTS:
            printf ("No roots");
            break;
        case ONE_ROOT:
            printf ("x = %lg", root1);
            break;
        case TWO_ROOTS:
            printf ("x1 = %lg\nx2 = %lg", root1, root2);
            break;
        case INFINITY_ROOTS:
            printf ("Any roots!");
            break;
        default:
            printf ("Undefined number of roots!");
            break;
    }
}


//----------------------------------------------------------------
//!  Program gets values of variables
//!  @param  [out]   a - pointer to the "a" coefficient
//!  @param  [out]   b - pointer to the "b" coefficient
//!  @param  [out]   c - pointer to the "c" coefficient
//!  @note You have only 5 attempts to enter coefficients! \n Or you will go to sleep (maybe this isn't a threat:))
//----------------------------------------------------------------

void InputCoefficient (double* a, double* b, double* c) {

    assert (a != 0);
    assert (b != 0);
    assert (c != 0);

    printf ("# Please enter coefficient of equation (a, b, c)\n");
    int varRet = scanf ("%lg %lg %lg", a, b, c);

    int cntOfTry = 1;
    if (varRet != 3) {
        while (cntOfTry < 5) {
            fflush(stdin);
            printf ("Wrong coefficient!\nTry again!\n");
            varRet = scanf ("%lg %lg %lg", a, b, c);
            if (varRet == 3)
                return;
            else
                cntOfTry++;
        }

        printf ("You're tired, go to sleep!!!");
        exit(0);
    }
}


//----------------------------------------------------------------
//!  Testing program of the function "SolveSquare()"
//!  Tests already set!
//!  @copyright AlexZ
//----------------------------------------------------------------

void TestSolveSquare () {
    double a = NAN, b = NAN, c = NAN;
    double root1 = NAN, root2 = NAN;
    int nRoots = 100;
    const int NTESTS = 4;
    paramTests arrayOfTests[NTESTS] =  {{1,  1, 1, NO_ROOTS,       0, 0},
                                        {0,  0, 0, INFINITY_ROOTS, 0, 0},
                                        {1,  2, 1, ONE_ROOT,      -1, 0},
                                        {1, -5, 6, TWO_ROOTS,      3, 2}};


    for (int numberOfTest = 0; numberOfTest < NTESTS; numberOfTest++) {

        a = arrayOfTests[numberOfTest].a;
        b = arrayOfTests[numberOfTest].b;
        c = arrayOfTests[numberOfTest].c;

        nRoots = SolveSquare (a, b, c, &root1, &root2);

        if (nRoots != arrayOfTests[numberOfTest].nRoots) {
            PrintErrOfTest (numberOfTest);
        }
        else if (nRoots != INFINITY_ROOTS && nRoots != NO_ROOTS) {
            if (!IsEqual(root1, arrayOfTests[numberOfTest].root1)) {
                PrintErrOfTest (numberOfTest);
            }

            else if (nRoots != ONE_ROOT) {
                if (!IsEqual(root2, arrayOfTests[numberOfTest].root2)) {
                    PrintErrOfTest (numberOfTest);
                }
            }
        }
        a = NAN; b = NAN; c = NAN; root1 = NAN; root2 = NAN; nRoots = 100;
    }
    printf ("End of Tests!");
}


//----------------------------------------------------------------
//!  Print "Error!" and number of test in case of failed
//!  @param [in] numberOfTest - coefficient
//----------------------------------------------------------------

void PrintErrOfTest (int numberOfTest) {
    printf ("Error Test %d!\n", numberOfTest + 1);
}

