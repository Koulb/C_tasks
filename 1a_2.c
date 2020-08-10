#include <stdio.h>

/* power function x ** y */
double Pow(double x, int y){

    if (y==0) return 1; 
    if (y<0) return (Pow(1 / x, -y));

    return(Pow(x,y-1)*x);
}

/* optimzed power function x ** y */
double PowOp(double x, int y){

    if (y==0) return 1; 
    if (y<0) return (PowOp(1 / x, -y));
    if (y % 2 == 0) return(PowOp(x*x,y/2));

    return(PowOp(x,y-1)*x);
}

int main(){

    double a;
    int n;

    printf("Enter number a and power n (i,g: 3,1) \n");
    scanf("%lf , %d", &a, &n);
    printf("aˆn = %lf \n", Pow(a,n));
    printf("aˆn with optimized function = %lf \n", PowOp(a,n));

    return 0; 
}