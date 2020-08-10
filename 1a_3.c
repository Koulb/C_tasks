#include <stdio.h>

/* hanoy recursive function for shifting disks */
void hanoi(int height, int start, int finish, int tmp){

	if (height == 1)
		printf("Move disk 1 from %d to %d. \n", start, finish);
	else {
		hanoi(height-1,start,tmp,finish);
		printf("Move disk %d from %d to %d. \n", height, start, finish);
		hanoi(height-1,tmp,finish,start);
	}

	return;
}

int main(){

	int h, strt, end, tmp;
	printf ("Enter Height of the tower, start point and end point (i,g: 3,1,2) \n");
	scanf("%d,%d,%d", &h , &strt, &end);
	tmp =  6 - strt - end;  
	hanoi(h,strt,end,tmp);

	return 0;
}