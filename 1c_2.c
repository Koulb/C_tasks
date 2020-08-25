#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 100


typedef struct stack{
	float value; 
  	struct stack *next ;  	
} Stack;

Stack * initStack(float c){
	Stack *lst   ;

	lst = (Stack*)malloc(sizeof(Stack));
	lst->value = c;
	lst->next = NULL;

	return lst;
}

void printStack(Stack * lst){

	Stack *tempList;
  
  	tempList = lst;

  	do {
    	printf("%f \n", tempList->value); 
    	tempList = tempList->next; 
  	} while (tempList != NULL); 

}

Stack * addStack( Stack *lst, float data){
	Stack *temp;

  	temp = (Stack*)malloc(sizeof(Stack));
  	temp->value = data; 
  	temp->next = lst;

  	return(temp);
}

void pushStack( Stack **lst, float data){
	Stack *temp;

  	temp = (Stack*)malloc(sizeof(Stack));
  	temp->value = data; 
  	temp->next = *lst;
  	*lst = temp;

}


Stack * deleteStack( Stack *lst){
	Stack *temp;

  	temp = lst;
  	lst = lst->next;
  	free(temp);

  	return(lst);
}

void popStack( Stack **lst){
	Stack *temp;

  	temp = *lst;
  	*lst = (*lst)->next;
  	free(temp);

}


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
    char str[SIZE], tempStr[SIZE] = {};
    int i = -1,j = 0;
    float x,y;
    size_t strSize = sizeof tempStr;

    head = initStack((float)j);
    current = head;

    //scanf("%s", str);
    strcpy(str , "3.3  2 sqrt + 2 2 * /") ;
    strcpy(str , "3.3  2 + sqrt") ;
    //strcpy(str , "0.0 cos ") ;
    printf("%s\n", str);


    while(str[++i] != '\0'){
        // spase case
        if (str[i] == ' ')
            continue; 
        
        // number case
        if (isNumber(str[i])){
            while (isNumber(str[i+j])){
                tempStr[i+j] = str[i+j];
                j++;
            }

            x = strtof(tempStr, NULL);
            pushStack(&current,x);
            i = i + j;
            j = 0;
            memset(tempStr, ' ', strSize);
            continue;
        }

        // unary operaton case 
        switch(str[i]){
            case 'c':
                x = current->value;
                x = cos(x);
                popStack(&current);
                pushStack(&current,x);
                i = i + 2;
                continue;
            case 't':
                x = current->value;
                x = tan(x);
                popStack(&current);
                pushStack(&current,x);
                i = i + 2;
                continue;
            case 's':
                if (str[i+1] == 'i'){
                    x = current->value;
                    x = sin(x);
                    popStack(&current);
                    pushStack(&current,x);
                }
                else {
                    x = current->value;
                    x = sqrt(x);
                    popStack(&current);
                    pushStack(&current,x);
                i = i + 1;
                }

                i = i + 2; 
                continue;
            case 'l':
            if (str[i+1] == 'n'){
                x = current->value;
                x = log(x);
                popStack(&current);
                pushStack(&current,x); 
                i++;
            }
            else{
                x = current->value;
                x = log10(x);
                popStack(&current);
                pushStack(&current,x); 
                i = i + 4; 
            }
            continue;
        }

        // binary operaton case 
        switch(str[i]){
            case '+':
            x = current->value;
            popStack(&current);
            y = current->value;
            popStack(&current);
            pushStack(&current, x + y);
            continue;
            case '-':
            x = current->value;
            popStack(&current);
            y = current->value;
            popStack(&current);
            pushStack(&current, y - x);
            continue;
            case '*':
            x = current->value;
            popStack(&current);
            y = current->value;
            popStack(&current);
            pushStack(&current, x*y);
            continue;
            case '/':
            x = current->value;
            popStack(&current);
            y = current->value;
            popStack(&current);
            pushStack(&current, y/x);
            continue;
        }

    }    

    printf("Result is %f\n",current->value );
    // printStack(current);

  return 0;
}
