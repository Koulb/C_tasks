#include <stdio.h>

/* recursive function */
int Reverse(int n)   
{

    if (n==0) {
   	    printf("\n");	
   		return 0;
   	}

    printf("%d",n%10 );

    return Reverse(n/10);
}

int main()
{
    int n;
    printf("Enter number \n");
    scanf("%d", &n);
    printf("Reverse number is \n");
  
  /* negative or zero number case */
    if (n < 0){ 
        printf("-");
        n=-n;
    }
    else if (n == 0){
    printf("0");
    }  

    Reverse(n);

    return 0;
}