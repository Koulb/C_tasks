#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 100
#define SIZE_numb 6
#define PI 3.141593

// delete selected char in n
void deleteChar(char *str, const char c){
    int i = 0;

    do{ 
        if (str[i] == c)
            str[i] = ' ';
    } while (str[++i] != '\0');
}

// struct for stack
typedef struct stack{
	char value[SIZE]; 
  	struct stack *next ;  	
} Stack;

// stack initialization
Stack * initStack(char *c){
	Stack *lst;

	lst = (Stack*)malloc(sizeof(Stack));
    lst->value[0] = '0';
	lst->next = NULL;

	return lst;
}

// print stack values
void printStack(Stack * lst){

	Stack *tempList;
  
  	tempList = lst;

  	do {
    	printf("%s \n", tempList->value); 
    	tempList = tempList->next; 
  	} while (tempList != NULL); 

}

// print stack size
int stackSize( Stack * lst){
    Stack *tempList;
    int count = 0;

    tempList = lst;

    do {
        count++;
        tempList = tempList->next; 
    } while (tempList != NULL); 

    return count;
}

// add value in stack
void pushStack( Stack **lst, char *data){
	Stack *temp;

  	temp = (Stack*)malloc(sizeof(Stack));
  	strcpy(temp->value,data);
  	temp->next = *lst;
  	*lst = temp;

}

// delete value in stack
void popStack( Stack **lst){
	Stack *temp;

  	temp = *lst;
  	*lst = (*lst)->next;
  	free(temp);

}

// check selected char for digit
int isNumber(char c){
    switch(c){
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
        case '.':
            return 1;
        default:
            return 0;    
         }   
}

int main(void) {
    Stack *head, *current;
    char str[SIZE], tempStr[SIZE] = "";
    int i = -1,j = 0,negIndex = 0;
    double x,y;
    size_t strSize = sizeof tempStr;

    //initialization of stack `and string
    head = initStack("0");
    current = head;
    printf("Enter expression in reverse notation (i.e. \"1 1 + 2.2 sqrt /\"): \n");
    fgets(str, sizeof(str), stdin);
    deleteChar(str,'\n');

    // loop for analyse chars in given string
    while(str[++i] != '\0'){
        // spase case
        if (str[i] == ' ')
            continue; 

        //negative number case
        if ((str[i] == '-') && (isNumber(str[i+1]))){
                negIndex = 1;
                continue;
        }
        // number case
        if (isNumber(str[i])){  
            while (isNumber(str[i+j])){
                tempStr[j] = str[i+j];
                j++;
            }

            if (negIndex ){
                x = -atof(tempStr);
                memset(tempStr, '\0', strSize);
                gcvt(x, SIZE_numb, tempStr);
                negIndex = 0;
            }

            pushStack(&current,tempStr);
            i = i + j - 1 ;
            j = 0;
            memset(tempStr, '\0', strSize);
            continue;
        }

        // unary operaton case 
        if (stackSize(current) < 2 ){
            printf("Syntactic error: check your expression\n");
            exit(2);
        }

        x = atof(current->value);
        popStack(&current);

        switch(str[i]){
            case 'c':
                x = cos(x);
                gcvt(x, SIZE_numb, tempStr);
                pushStack(&current, tempStr);
                memset(tempStr, '\0', strSize);
                i = i + 2;
                continue;
            case 't':
                if (x == PI / 2){
                     printf("Error: tan is not determined for  PI / 2\n");
                    exit(1);
                }

                x = tan(x);
                gcvt(x, SIZE_numb, tempStr);
                pushStack(&current, tempStr);
                memset(tempStr, '\0', strSize);
                i = i + 2;
                continue;
            case 's':
                if (str[i+1] == 'i'){
                    x = sin(x);
                    gcvt(x, SIZE_numb, tempStr);
                    pushStack(&current, tempStr);
                    memset(tempStr, '\0', strSize);
                }
                else {
                    if (x < 0){
                        printf("Error: square root is determined for not negative values\n");
                        exit(1);
                    }
                    x = sqrt(x);
                    gcvt(x, SIZE_numb, tempStr);
                    pushStack(&current, tempStr);
                    memset(tempStr, '\0', strSize);
                    i++;
                }

                i = i + 2; 
                continue;
            case 'l':
            if (x <= 0){
                printf("Error: logarithm is determined for positive values\n");
                exit(1);
            }

            if (str[i+1] == 'n'){
                x = log(x);
                gcvt(x, SIZE_numb, tempStr);
                pushStack(&current, tempStr);
                memset(tempStr, '\0', strSize);
                i++;
            }
            else{
                x = log10(x);
                gcvt(x, SIZE_numb, tempStr);
                pushStack(&current, tempStr);
                memset(tempStr, '\0', strSize);
                i = i + 4; 
            }
            continue;
        }


        // binary operaton case
        if (stackSize(current) < 2 ){
            printf("Syntactic error: check your expression\n");
            exit(4);
        } 

        y = atof(current->value);
        popStack(&current);
    
        switch(str[i]){
            case '+':
            gcvt(x+y, SIZE_numb, tempStr);
            pushStack(&current, tempStr);
            memset(tempStr, '\0', strSize);
            continue;
            case '-':
            gcvt(y-x, SIZE_numb, tempStr);
            pushStack(&current, tempStr);
            memset(tempStr, '\0', strSize);
            continue;
            case '*':
            gcvt(x*y, SIZE_numb, tempStr);
            pushStack(&current, tempStr);
            memset(tempStr, '\0', strSize);
            continue;
            case '/':
            if (x == 0){
                printf("Error: division by zero is not determined\n");
                exit(1);
            }
            gcvt(y/x, SIZE_numb, tempStr);
            pushStack(&current, tempStr);
            memset(tempStr, '\0', strSize);
            continue;
        }

    }    

    // Syntactic check
    if (stackSize(current) > 2){
        printf("Syntactic error: check your expression\n");
        exit(6);
    }

    printf("Result is %s\n",current->value );

  return 0;
}
