#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5


/* swap function x and y */
void swap(int *x, int *y){
 int tmp ;

 tmp = *x;
 *x = *y;
 *y = tmp; 
}

int main(){

    int a[SIZE], i, j, m;

    srand(time(0));
    m = SIZE;
    printf("Initial random generated array (0 - 100): \n");

    for (i=0; i < SIZE ; i++){
        a[i] = rand() % 100;
        printf("%d ", a[i] );
    }

    printf("\n");
    printf("Enter number that is not greater than %d and not less than 1 \n",m );
    scanf("%d",&m);

    for (j=1; j < SIZE + 1 - m; j++){
        for (i=SIZE - 1; i > 0 ; i--){
            swap(&a[i],&a[i-1]);
        }
    }

    printf("Transformed array: \n" );

    for (i=0; i < SIZE ; i++){
        printf("%d ", a[i] );
    }

    printf("\n");

    return 0; 
}