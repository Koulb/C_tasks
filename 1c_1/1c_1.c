#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define SIZE 15 // quantity of points 
#define PI 3.141593

// struct for all points
struct coordinate {
  	int x[SIZE];
	int y[SIZE];
};

// struct for polygon coordinates
typedef struct polCoord{ 
	int x;
	int y;
} polCoord;

// linked list for polygon coordinates
struct list {	
	polCoord loc;
	struct list *next;
	struct list *prev;
};

// function that initialize linked list
struct list * initList(polCoord startValue){
	struct list *lst;

  	lst = (struct list*)malloc(sizeof(struct list));
  	lst->loc = startValue;
  	lst->next = NULL; 
  	lst->prev = NULL; 
  	
  	return(lst);
}

// function that can add element in the linked list
struct list * addList( struct list *lst, polCoord value){
	struct list *temp, *p;

  	temp = (struct list*)malloc(sizeof( struct list));
  	p = lst->next; 
  	lst->next = temp; 
  	temp->loc = value; 
  	temp->next = p; 
  	temp->prev = lst; 

	if (p != NULL)
		p->prev = temp;

  return(temp);
}

// function that can print all elements in the linked list
void listPrint(struct list *lst){
	struct list *p;
  
  	p = lst;

  	do {
    	printf("%2d, %2d \n", p->loc.x,p->loc.y); 
    	p = p->next; 
  	} while (p != NULL); 

}

// counting index of the point that has the least value
int minArrayInd(int *arr, int sizeAr){
	int tmp, i, minIndex;

	tmp = arr[0]; 
	minIndex = 0;

	for (i = 1; i < sizeAr;  i++){
		if (arr[i] < tmp){
			minIndex = i;
			tmp = arr[i];
		}
	}

	return minIndex;
} 

// counting polar angle between 2 points
double polarAngle(int x1, int y1, int x2, int y2){
	
	double x,y,angle;

	x = x2 - x1;
	y= y2 - y1;

	if ((x > 0) && (y > 0))
		angle = atan2(y, x);
	else if ((x < 0) && (y > 0))
		angle = atan2(y, x);
	else if ((x < 0) && (y < 0))
		 angle = 2*PI  - fabs(atan2(y, x));
	else if ((x > 0) && (y <0 ))
		angle = 2*PI - fabs(atan2(y,x));
	else if  (y == 0)
		angle = fabs(atan2(y,x));
	else if ((x == 0 ) && (y > 0))
		angle = fabs(atan2(y,x));
	else if ((x == 0 ) && (y < 0))
		angle = 3*PI/2;
	else if ((x == 0 ) && (y == 0))
		angle = fabs(atan2(y,x));
	
	return angle;
}

// counting polar radius between 2 points
double polarRad(int x1, int y1, int x2, int y2){
	double x,y,Radius;

	x = x2 - x1;
	y= y2 - y1;

	Radius = sqrt(x*x+y*y);

	return Radius;
}

// searching for the index of next polygon coordinates
int nextIndex(double *oldAngel, int i0, struct coordinate pos, int sizeStruct){
	int  i, j, icount=0, jcount=0; 
	double tempAngel = 4*PI, tempR = 15, angel = 0, R = 0;

	for (i = 0; i < i0 ; i++){
		R = polarRad(pos.x[i0], pos.y[i0], pos.x[i], pos.y[i]);

		if (*oldAngel >=  3 * fabs(atan2(1,0)))
			angel= polarAngle(-pos.x[i0], -pos.y[i0], -pos.x[i], -pos.y[i]);
		else if (*oldAngel >= fabs(atan2(0,-1)))
			angel= polarAngle(pos.y[i0], -pos.x[i0], pos.y[i], -pos.x[i]);
		else		
			angel= polarAngle(pos.x[i0], pos.y[i0], pos.x[i], pos.y[i]);

		if (angel < tempAngel){
			tempAngel = angel;
			tempR = R;
			icount = i;
		}
		else if ((angel == tempAngel) && (R > tempR)){
			tempAngel = angel;
			tempR = R;
			icount =i; 
		}
	}

	for (j = i0 + 1; j < sizeStruct ; j++){
		R = polarRad(pos.x[i0], pos.y[i0], pos.x[j], pos.y[j]);

		if (*oldAngel >= 3 * fabs(atan2(1,0)))
			angel= polarAngle(-pos.x[i0], -pos.y[i0], -pos.x[j], -pos.y[j])  ;
		else if (*oldAngel >= fabs(atan2(0,-1)))
			angel= polarAngle(pos.y[i0], -pos.x[i0], pos.y[j], -pos.x[j])  ;
		else	{
			angel= polarAngle(pos.x[i0], pos.y[i0], pos.x[j], pos.y[j])  ;	
		}

		if (angel < tempAngel){
			tempAngel = angel;
			tempR = R;
			jcount = j;
		}
		else if ((angel == tempAngel) && (R > tempR)){
			tempAngel = angel;
			tempR = R;
			jcount = j; 
		}	 
	}   

	if (jcount != 0){
		*oldAngel = polarAngle(pos.x[i0], pos.y[i0], pos.x[jcount], pos.y[jcount]);
		return jcount;
	}
	else {
		*oldAngel = polarAngle(pos.x[i0], pos.y[i0], pos.x[icount], pos.y[icount]);
		return icount;
	}
}

int main(){

	double oldAngel = -0.1*PI;
 	int  x0, y0, i,j, startIndex, iterIndex, tempX,tempY,counter = 1;
 	struct  coordinate coord;
 	struct list  *head, *current;
 	polCoord tempPolygonCord;
 	FILE *textIN,*textOUT;

 	srand(time(0));
	x0 = -5; 
	y0 = x0; 

	// open file that contains all points
	textIN = fopen("points.txt", "w"); 

	printf("Generation of random points for x and y from %d to %d :\n",x0, x0 + 10);
	
	for (i = 0; i < SIZE; i++){
		tempX = x0 + rand() % 10;
		tempY = y0 + rand() % 10;
		j = 0;

		while (j < i){
			if ((tempX == coord.x[j] )&&(tempY == coord.y[j])){
				tempX = x0 + rand() % 10;
				tempY = y0 + rand() % 10;
				j = 0;
				continue; 
			}

			j++;
		}

		coord.x[i] = tempX;
		coord.y[i] = tempY;
		fprintf(textIN, "%d %d \n",  coord.x[i], coord.y[i] );
		printf("%2d, %2d \n",  coord.x[i], coord.y[i] );
	}

	fclose(textIN);

	// first polygin point 
	startIndex = minArrayInd(coord.y, SIZE);
	tempPolygonCord.x = coord.x[startIndex]; 
	tempPolygonCord.y = coord.y[startIndex]; 
	head = initList(tempPolygonCord);
	current = head;

	// open file that contains polygon points
	textOUT = fopen("polygonPoints.txt", "w"); 

	// secong polygin point 
	fprintf(textOUT,"%d %d \n",coord.x[startIndex], coord.y[startIndex] );
	iterIndex = nextIndex(&oldAngel,startIndex, coord, SIZE);
	tempPolygonCord.x = coord.x[iterIndex]; 
	tempPolygonCord.y = coord.y[iterIndex]; 
	fprintf(textOUT,"%d %d \n",coord.x[iterIndex], coord.y[iterIndex] );
	current = addList(current,tempPolygonCord );

	// loop for searching all other polgyin pouints
	while (iterIndex != startIndex){
		iterIndex = nextIndex(&oldAngel,iterIndex, coord, SIZE);
		tempPolygonCord.x = coord.x[iterIndex]; 
		tempPolygonCord.y = coord.y[iterIndex]; 
		current = addList(current,tempPolygonCord );
		fprintf(textOUT,"%d %d \n",coord.x[iterIndex], coord.y[iterIndex] );
	}

	fclose(textOUT);

	printf("Polygon coordinates: \n");
	listPrint(head);
	printf("Points were created and polygon coordinates were found and saved.\n");
	printf("Run 1c_1Plot.py to visualise data.  \n");

	return 0;
}