#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define HEIGHT 15
#define WIDTH 15

#define LIVE 1
#define DIE 0

void generateInitialCells(int cells[HEIGHT][WIDTH]) {
	srand(time(NULL));

	for(int i= 0; i < HEIGHT; i++) {
		for(int j= 0; j < WIDTH; j++) {
			cells[i][j]= rand() % 2;
		}
	}
}

void printCells(int cells[HEIGHT][WIDTH]) {
	system("cls");

	for(int i= 0; i < HEIGHT; i++) {
		printf("\t\t\t\t");
		for(int j= 0; j < WIDTH; j++) {
			printf("%d ", cells[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");

	Sleep(500);
}

int willDieOrLive(int cells[HEIGHT][WIDTH], int i, int j) {
	int rangeNeighborHeight= 3, rangeNeighborWidth= 3;
	if(i == 0) {
		rangeNeighborHeight = 2;
	}
	if(i == HEIGHT - 1) {
		rangeNeighborHeight = 2;
	}
	if(j == 0) {
		rangeNeighborWidth = 2;
	}
	if(j == WIDTH - 1) {
		rangeNeighborWidth = 2;
	}

	int k= i- 1, l= j- 1;
	int aux_l= j- 1;
	if(k < 0) {
		k= 0;
	}
	if(l < 0) {
		aux_l= 0;
		l= 0;
	}

	// printf("k=%d,l=%d / rh=%d,rw=%d\n", k, l, rangeNeighborHeight, rangeNeighborWidth);
	int neighborCount= 0;
	int auxHeight= k+ rangeNeighborHeight;
	int auxWidth= l+ rangeNeighborWidth;
	if(auxHeight > HEIGHT) {
		auxHeight= HEIGHT;
	}
	if(auxWidth > WIDTH) {
		auxWidth= WIDTH;
	}
	while(k < auxHeight) {
		while(l < auxWidth) {
			// printf("k=%d,l=%d > %d\n", k, l, cells[k][l]);
			if(cells[k][l] == LIVE) {
				neighborCount++;
			}
			l++;
		}
		l= aux_l;
		k++;
	}
	if(cells[i][j] == LIVE) {
		neighborCount--;
	}

	// printf("i=%d,j=%d / nb=%d\n", i, j, neighborCount);
	if(cells[i][j] == LIVE && (neighborCount < 2 || neighborCount > 3)) {
		return DIE;
	} if(cells[i][j] == DIE && neighborCount == 3) {
		return LIVE;
	}
	return cells[i][j];
}

int isEnded(int cells[HEIGHT][WIDTH]) {
	for(int i= 0; i < HEIGHT; i++) {
		for(int j= 0; j < WIDTH; j++) {
			if(cells[i][j] == LIVE) return 0;
		}
	}

	return 1;
}

void copyMatriz(int matrix1[HEIGHT][WIDTH], int matrix2[HEIGHT][WIDTH]) {
	for(int i= 0; i < HEIGHT; i++) {
		for(int j= 0; j < WIDTH; j++) {
			matrix2[i][j]= matrix1[i][j];
		}
	}
}

void main() {
	int cells[HEIGHT][WIDTH]
							// = 	{	0,	0,	1,	0,	1,	0,	1,
							// 		0,	1,	0,	0,	1,	1,	0,
							// 		1,	1,	0,	0,	1,	1,	1,
							// 		1,	1,	1,	1,	1,	0,	0,
							// 		0,	0,	1,	0,	1,	1,	1,
							// 		0,	0,	0,	0,	1,	1,	0,
							// 		0,	0,	1,	1,	1,	1,	1
							// 	}
	;

	generateInitialCells(cells);

	while(!isEnded(cells)) {
		printCells(cells);

		int auxCells[HEIGHT][WIDTH]=	{	0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0,
											0, 0, 0, 0, 0, 0, 0
										}
		;
		
		for(int i= 0; i < HEIGHT; i++) {
			for(int j= 0; j < WIDTH; j++) {
				if(willDieOrLive(cells, i, j)) {
					auxCells[i][j]= LIVE;
				} else {
					auxCells[i][j]= DIE;
				}
			}
		}

		copyMatriz(auxCells, cells);
	}
}