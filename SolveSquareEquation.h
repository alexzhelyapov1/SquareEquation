#ifndef SOLVESQUAREEQUATION_H_INCLUDED
#define SOLVESQUAREEQUATION_H_INCLUDED
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#define DEBUG


enum {
//   ^ TODO: Consider naming enum, it would give it's content clarity,
//           serve as documentation and give you a chance to use it in function
//           signatures, variable declarations, etc... as any other type.

    INFINITY_ROOTS = -1,    //!<  Const in case of Infinity number of roots
    NO_ROOTS,               //!<  Const in case of No roots
    // TODO: It's a good idea to make all enum values explicit here.

    //       Because conversion from your enum to integer representing
    //       number of roots is very natural (and potentially enables
    //       code simplifications and generalizations).

    //       Imagine someone accidentally shuffling this enum (it can happen,
    //       especialy if order isn't this obvious), and NO_ROOTS suddenly
    //       becomes represented by 1, ONE_ROOT by 2,...

    //       Even more so since you've already specified "-1" for INFINITY_ROOTS

    //       In general I try to follow rule of specifying every number
    //       explicitly when one of a numbers or their order (or partial order)
    //       matters or it makese sense to support implicit conversions to integer
    //       or specify neither of them otherwise.

    //       For example, when ordering doesn't really *matter:
    //       enum colors { RED, ORANGE, BLUE, VIOLET, ... };

    //       *I guess you can imagine where order of colors would be useful too,
    //        but I think you can see where I'm going!

    //       DED even recommends to specify explicit values always as it could
    //       be useful for debugging. But for my taste it's a bit too extreme.

    //       But hey, you decide! I think either convention could improve this enum.

    ONE_ROOT,               //!<  Const in case of Single root
    TWO_ROOTS               //!<  Const in case of two roots
};

// TODO: Why? There's a beautiful type called "bool" and conventional "true" and "false", use them!
const int NO = 0;
const int YES = 1;


const double NEAR_ZERO = 1e-100;      //!<  Accuracy of our calculations (gets by MathAnalysis)
// TODO:     ^~~~~~~~~ Conventional name is EPSILON (proof: std::numerical_limits<double>::epsilon()),
//           using conventional naming improves readability as programmers will immediately know
//           what you're trying to do.


int SolveSquare (double a, double b, double c, double* root1, double* root2);
// TODO: ^~~~~~ I think they are called "quadratic" equations, no "square" ones

bool IsEqual (double value, double compareValue);
// TODO: This file is the heart of your program, it provides core API
//       (solving equations) that other programmers can potentially
//       integrate in their own programs.

//       Yet, for some reason, you are putting here interactive and
//       debugging functions. Do not do this! Split this header in 
//       multiple organised by purpose.

//       Make sure interface of every header file stays clean and minimal!

//       This separation has a lot of benefits: your header name becomes
//       part of documentation, parts are much more easy to use and
//       integrate in other projects.

//       There's isn't a lot of files in your project for now, but what if
//       your code would be part of a large codebase? Than finding
//       functions like PrintErrOfTest would be a huge pain, because name
//       SolveSquareEquation.h does not suggest it!

//       Or imagine someone with huge project trying to find an equation
//       solver to integrate in his program and stumbling across your GitHub.

//       And then seeing this: to use your library he needs to pollute his
//       project with a dozen of functions meant for debugging or user
//       interaction. Not ideal! Improve!

double SolveLinear (double coefficientAtX, double freeMember);
void OutputAnswer (int nRoots, double root1, double root2);
// TODO: "output" is too generic, it suggests returning string a lot more than
//       it does printing.
//
//       Maybe use printSolution() or something?
//
//       Get used to naming stuff by it's side-effect. print*, show*, write*
//       read*, ... It's conventional and clear, and since side effects can
//       be pretty drastic (printing in a big program is a big deal, writing,
//       reading, ... equally so), so good naming prevents a bunch of errors.

void InputCoefficient (double* a, double* b, double* c);
// TODO:             ^ should be in plural

// TODO: While certainly being a better way of implementing tests than
//       compiling them right in your program, a much better alternative
//       would be creating a different .cpp file with it's own main
//       and running tests from there.
#ifdef DEBUG
void TestSolveSquare ();
void PrintErrOfTest (int numberOfTest);
// TODO: naming, this does not print "error of the test", which would suggest
//       something like "perror" (and here there's no special error description or anything),
//       it just prints "Error" and supplied number.

//       For my liking it does too little and too tighten to TestSolveSquare to be a function,
//       so I would just rewrite a bit TestSolveSquare so it calls it just once (it's pretty easy, actually). //       But you can skip rewriting part, if you don't feel like it, it's more of a style preference.
#endif


#endif // SOLVESQUAREEQUATION_H_INCLUDED
