#include "SolveSquareEquation.h"

//----------------------------------------------------------------
//!  Program solve square equation a*x^2 + b*x + c = 0
//   ^~~~~~~
//   TODO: Why do you write "this program", "that program"?
//
//         It's obvious, believe me, programmers know function/program/variable
//         when they see one, so your clarification does not add any value.
//  
//         And Doxygen will put this documentation right next to respective
//         function declaration. Instead of spilling all this "water", just
//         describe function's actions right away like so:
//  
//         "Solve quadratic equation of form ax^2 + bx + c == 0"
//
//!  @param  [in]   a - coefficient
//!  @param  [in]   b - coefficient
//!  @param  [in]   c - coefficient
//!  @param  [out]   root1 - pointer to the 1st root
//!  @param  [out]   root2 - pointer to the 2nd root
//!  @return Number of roots
//!  @note In case of infinity number of roots program return INFINITY_ROOTS
//   TODO:          Spelling ^ (infinite)
//!  @copyright AlexZ (Idea of Ded;))
//----------------------------------------------------------------

int SolveSquare (double a, double b, double c, double* root1, double* root2) {

    assert (!isnan (a));
    assert (!isnan (b));
    assert (!isnan (c));
    assert (root1 != NULL);
    assert (root2 != NULL);
    // TODO: what if root1 == root2? Ooops. Add assert!


    if (IsEqual(a, 0.0)) { // TODO: used lots of times, extract in function isZero
        // TODO: I think entirety of this scope belongs in SolveLinear
        if (IsEqual(b, 0.0)) {
            if (IsEqual(c, 0.0)) {
                return INFINITY_ROOTS;
            }
            else {
                return NO_ROOTS;
            }
        }
        else { // TODO: else after return is considered a bad style by most style guides
            *root1 = SolveLinear(b, c);
            return ONE_ROOT;
        }
    }
    else { // TODO: else after return is considered a bad style by most style guides
        double discriminant = pow (b, 2.0) - 4*a*c;

        if (discriminant < 0) {
            return NO_ROOTS;
        } // TODO: else after return is considered a bad style by most style guides
        else if (IsEqual(discriminant, 0.0)) {
            // TODO: else after return is considered a bad style by most style guides
            *root1 = SolveLinear(2*a, b);
            return ONE_ROOT;
        }
        else {// TODO: else after return is considered a bad style by most style guides
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
//   TODO: undocumented parameter
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
    // TODO:       ^~~ Limited number of states that nRoots can be in
    //             would be expressed much better if you'd use an enum type
    //             (see header for that enum and related commentary)

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
            // TODO: If this code is reached it's a pretty bad programmer
            //       error (there was a nRoots's state that wasn't checked).

            //       And there is a specially utiliy in standard library for
            //       telling programmer about program's invariant violations (like such)
            //       ASAP. They are called asserts, use them (especially here!).
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
    //  ^~~~~~ TODO: varRet? Doesn't make any sense. Something like numberOfRead would be a lot better.

    int cntOfTry = 1;
    //  ^~~ Why use obscure abbrivations? A few extra letter won't hurt!
    if (varRet != 3) {
        while (cntOfTry < 5) {
            fflush(stdin);
// TODO:           ^~~~~ TODO: this is MSVC specific, look for a better and more portable way!
            printf ("Wrong coefficient!\nTry again!\n");
            varRet = scanf ("%lg %lg %lg", a, b, c);
            if (varRet == 3)
                return; //^ TODO: You've separated 3 and printf enough, it's not obvious anymore
                        //        where 3 came from. Add a comment, extract in constant or bring
                        //        scanf closer to it, so it's obvious.
            else
                cntOfTry++;
        }

        printf ("You're tired, go to sleep!!!");
        exit(0);
//      ^~~~~~~ TODO: you should NEVER explicitly call exit,
//      It disrupts stdlib's doings (some text could left in buffer without flushing,
//      stdlib's resources might be leaked, ... as it exits immediately.
//
//      And is also very hard to control and track. Imagine huge program
//      with dozens of functions running continuously on a server,
//      and than some random function just obliterates the whole thing
//      under rare (or worse -- unpredictable) circumstances!
    }
}


//----------------------------------------------------------------
//!  Testing program of the function "SolveSquare()"
//!  Tests already set!
//   ^~~~~~~~~~~~~~~~~ TODO: What does it mean?
//!  @copyright AlexZ
//----------------------------------------------------------------


#ifdef DEBUG

void TestSolveSquare () {

    // TODO: What is the reason to define paramTests structure locally?
    //       I think making it top-level in appropriate header (e.g. equation-solver-test.h)
    //       would add a lot of possibilities for splitting this in more functions.  

    //! Structure to keep tests for function TestSolveSquare()
    struct paramTests {
    //     ^~~~~~~~~~ TODO: snakeCase for struct/class names is very rare,
    //                but this is not really a "need to fix", since you don't
    //                have any other structs in program, so you're kinda consistent,
    //                and consistency is really the key here.

    //                But!

    //                Just note if this is something you did accidentally,
    //                that PascalCase (aka ParamTests) and snake_case (param_tests)
    //                are overwhelmingly more common for structure names.

    // TODO: Also, name "paramTests" isn't that good. Why "param" test? You're
    //       testing equations solver, definitely not some "params". Improve upon this!

        double a;           //!<  Coefficient of equation for x^2
        double b;           //!<  Coefficient of equation for x
        double c;           //!<  Coefficient of equation for free member
        int nRoots;         //!<  Number of roots
        double root1;       //!<  First solution of equation
        double root2;       //!<  Second solution of equation
    };

    // TODO: Move declarations closer to their usage!
    double a = NAN, b = NAN, c = NAN;
    double root1 = NAN, root2 = NAN;
    int nRoots = 100;
    // TODO:     ^~~ What is 100? Why is it here?

    const int NTESTS = 4;
    paramTests arrayOfTests[NTESTS] =  {{1,  1, 1, NO_ROOTS,       0, 0},
                                        {0,  0, 0, INFINITY_ROOTS, 0, 0},
                                        {1,  2, 1, ONE_ROOT,      -1, 0},
                                        {1, -5, 6, TWO_ROOTS,      3, 2}};

    printf ("Tests are going!\n");
    for (int numberOfTest = 0; numberOfTest < NTESTS; numberOfTest++) {

        a = arrayOfTests[numberOfTest].a;
        b = arrayOfTests[numberOfTest].b;
        c = arrayOfTests[numberOfTest].c;

        // TODO: Just define nRoots at assignment point (meaning below)
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
        // TODO:                                                      ^~~ yeah, obscure constant repeated twice
    }
    printf ("End of Tests!");
}

#endif


//----------------------------------------------------------------
//!  Print "Error!" and number of test in case of failed
//!  @param [in] numberOfTest - coefficient
//----------------------------------------------------------------

void PrintErrOfTest (int numberOfTest) {
    printf ("Error Test %d!\n", numberOfTest + 1);
}
