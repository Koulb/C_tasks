#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#define SIZE  5000

/* function for bubble sorting words in alphabetical order */
void sortAlphabet(char *strings[], int num){ 
	
	char *temp;
	int top, seek;

	for(top = 0; top < num-1; top++)
		for(seek = top + 1; seek < num; seek++)
			if(strcmp(strings[top], strings[seek]) > 0){
				temp = strings [top];
				strings[top] = strings[seek];
				strings[seek] = temp;
			} 

}

/* function for counting words after sorting */
void wordsCount(char *strings[],int num)
{
	int i, count = 1;

	for(i=0; i < num - 1; i++)
		if(strcmp(strings[i], strings[i+1]) == 0)
			count++;
		else {
			printf("%s -- %d\n", strings[i], count);
			count = 1;	
		}
	
	if (count == 1)
		printf("%s -- %d\n", strings[num-1], count);
	else 
		printf("%s -- %d\n", strings[num-1], ++count);
	
}

int main()
{   

    FILE *text;
    char txtString[SIZE], *ptString[SIZE], *token;;
    const char breakers[SIZE] = " \t\n,.:;!?-"; 
    int i = 0, endString, sizeString;

    /* reading text file */
    text = fopen("input_1b_2.txt", "r");
    fgets(txtString,SIZE,text);
    fclose(text);
    token = strtok(txtString, breakers);
    
    /* assigning string arrays */
    while( token != NULL ){
 		ptString[i] = token;
 		*ptString[i] = tolower(*ptString[i]);
 		i++; 
        token = strtok(NULL, breakers);
    }

    endString = i;
    printf("Words frequency in input_1b_2.txt (world -- total number in text): \n");
    printf("Press Enter to continue");;
   	getchar();
    sortAlphabet(ptString,endString);
    wordsCount(ptString,endString);
    printf("_________________________________________\n");;
    printf("To change input text, edit input_1b_2.txt\n");;

    return 0;
}