#include <stdio.h>
#include <math.h>

const int INFINITY_ROOTS = -1;
const int NO_ROOTS = 0;
const int ONE_ROOT = 1;
const int TWO_ROOTS = 2;
const double NEAR_ZERO = 1e-100;

int SolveSquare (double a, double b, double c, double* root1, double* root2);     // обязателно указывать переменные?
bool IsZero (double a);
double SolveLinear (double coefficientAtX, double freeMember);  //Решение линейного уравнения вида coefficientAtX * x + freeMember = 0 (оно гарантировано существует)

int main () {
    double a = NAN, b = NAN, c = NAN;
    printf ("# Please enter coefficient of equation (a, b, c)\n");
    scanf ("%lg %lg %lg", &a, &b, &c);

    double root1 = NAN, root2 = NAN;
    int nRoots = SolveSquare (a, b, c, &root1, &root2);      // Указатель!


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

    return 0;
}



int SolveSquare (double a, double b, double c, double* root1, double* root2){
    if (IsZero(a)) {
        if (IsZero(b)) {
            if (IsZero(c))
                return INFINITY_ROOTS;
            else
                return NO_ROOTS;
        }
        else {
            *root1 = SolveLinear(b, c);
            return ONE_ROOT;
        }
    }
    else {
        double discriminant = pow (b, 2) - 4*a*c;

        if (discriminant < 0)
            return NO_ROOTS;
        else if (IsZero(discriminant)) {
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


bool IsZero (double a){
if (fabs (a) < NEAR_ZERO)
    return 1;
else
    return 0;
}

double SolveLinear (double coefficientAtX, double freeMember){
    return -freeMember/coefficientAtX;
}
