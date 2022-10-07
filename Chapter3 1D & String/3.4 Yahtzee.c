#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

#define MAX 100000000
#define TESTS 100000
#define MAXTHROW 6
#define NUMDICE 5

/* Fill the array d with random numbers 1..6 */
void randomthrow(int d[NUMDICE]);
/* Decide if the number n occurs anywhere in the histogram h */ 
bool histo_has(const int h[MAXTHROW], const int n);
/* Compute a histogram, given a dice hand */
void makehist(const int d[NUMDICE], int h[MAXTHROW]);
/* Check that the histograms h1 & h2 are the same */
bool hists_same(const int h1[MAXTHROW], const int h2[MAXTHROW]);
/* Does this hand have 2 lots of one number and 3 lots of another */
bool isfullhouse(const int d[NUMDICE]);
/* Does this hand have 4 lots of one number and 1 of another ? */
bool is4ofakind(const int d[NUMDICE]);
bool is5ofakind(const int d[NUMDICE]);
void test();

int main(void){
//	srand((unsigned)time(NULL));
//		double four = 0;
//		double fullhouse = 0;
//	
//	int i = 0;
//	do{
//
//		int a[6] = {0, 0, 0, 0, 0, 0};
//		for (int i = 0; i < 5; i++){
//			a[rand() % 6]++;
//		}
//		
//		for (int i = 0; i < 5; i++){
//			if (a[i] == 5){
//				printf("A Five of a kind");
//			if (a[i] == 4){
//				printf("A Four of a kind");
//				four++;
//				break;
//			}else if (a[i] == 3 || a[i] == 2){
//				for (int j = i + 1; j < 6; j++){
//					if (a[j] == 3 || a[j] == 2 && a[i] + a[j] == 5){
//						printf("Full house.");
//						fullhouse++;
//						break;
//					}
//				}
//			}
//		}
//	}while (i++ < MAX);
//	printf("%f %f\n", four, fullhouse);
//	printf("%f %f\n", four/MAX, fullhouse/MAX);
	
	int dice[NUMDICE]; 
	int k4 = 0;
	int fh = 0;
	int i;	test();
	
//	for(i=0; i<TESTS; i++){
//		randomthrow(dice); if(isfullhouse(dice)){
//			fh++; }//		if(is4ofakind(dice)){ k4++;
//		} }
//	printf("FH=%.2f%% 4oK=%.2f%%\n", (double)fh*100.0/(double)TESTS, (double)k4*100.0/(double)TESTS);
	return 0;
}

void randomthrow(int d[NUMDICE]){
	for (int i = 0; i < NUMDICE; i++){
		d[i] = rand() % MAXTHROW + 1;
	}
}

bool histo_has(const int h[MAXTHROW], const int n){
	for (int i = 0; i < MAXTHROW; i++){
		if (h[i] == n){
			return true;
		}
	}
	return false;
}

void makehist(const int d[NUMDICE], int h[MAXTHROW]){
	for (int i = 0; i < NUMDICE; i++){
		h[d[i] - 1]++;
	}
}

bool hists_same(const int h1[MAXTHROW], const int h2[MAXTHROW]){
	return is4ofakind(h1) == is4ofakind(h1) || isfullhouse(h1) == isfullhouse(h2);
}

bool isfullhouse(const int d[NUMDICE]){
	int h[MAXTHROW];
	makehist(d, h);
	for (int i = 0; i < MAXTHROW; i++){
		if (h[i] == 3 || h[i] == 2){
			for (int j = i + 1; j < 6; j++){
				if ((h[j] == 3 || h[j] == 2) &&h[i] + h[j] == NUMDICE){
					return true;
				}
			}
		}
	}
	return false;
}

bool is4ofakind(const int d[NUMDICE]){
	int h[MAXTHROW];
	makehist(d, h);
	for (int i = 0; i < MAXTHROW; i++){
		if (h[i] == 4){
				return true;
		}
	}
	return false;
}

bool is5ofakind(const int d[NUMDICE]){
	int h[MAXTHROW];
	makehist(d, h);
	for (int i = 0; i < MAXTHROW; i++){
		if (h[i] == 5){
			return true;
		}
	}
	return false;
}


void test(){
	int i, j;
	int h1[MAXTHROW] = {0,0,0,0,0,5}; /* 5−of−a−kind */ 
	int h2[MAXTHROW] = {0,0,5,0,0,0}; /* 5−of−a−kind */ 
	int h3[MAXTHROW] = {0,2,0,0,3,0}; /* Full−House */ 
	int h4[MAXTHROW] = {2,0,3,0,0,0}; /* Full−House */
	int h5[MAXTHROW] = {3,2,0,0,0,0}; /* Histo of d1 */ 
	int h6[MAXTHROW] = {0,0,0,2,3,0}; /* Histo of d2 */ 
	int h7[MAXTHROW] = {4,1,0,0,0,0}; /* Histo of d3 */ 
	int h8[MAXTHROW] = {0,0,0,0,1,4}; /* Histo of d4 */ 
	int h9[MAXTHROW] = {0,0,0,0,0,0};/* Temp */
	int d1[NUMDICE] = {1,1,1,2,2}; /* Full House */
	int d2[NUMDICE] = {5,4,5,4,5}; /* Full House */
	
	int d3[NUMDICE] = {2,1,1,1,1}; /* 4−of−a−kind */
	int d4[NUMDICE] = {6,6,6,6,5}; /* 4−of−a−kind */ 
	int d5[NUMDICE] = {6,6,6,6,5}; /* Temp */
	/* Tricky to test a random throw ... */	
	for(i=0; i<100; i++){
		randomthrow(d5);
		for(j=0; j<NUMDICE; j++){
			assert((d5[j] >= 1) && (d5[j] <= MAXTHROW)); 
		}
		
		makehist(d5,h9);
		
		for (int temp = 0; temp < MAXTHROW; temp++){
			h9[temp] = 0;
		}
		
		for(j=0; j<MAXTHROW; j++){
			assert((h9[j] >= 0) && (h9[j] < NUMDICE)); 
		}
		
		
	}
	
	assert(hists_same(h1,h1)==true); 
	assert(hists_same(h5,h5)==true);
	assert(hists_same(h1,h2)==false); 
	assert(hists_same(h4,h5)==false); 
	makehist(d1,h9); 
	assert(hists_same(h9,h5)); 
	makehist(d2,h9); 
	assert(hists_same(h9,h6)); 
	makehist(d3,h9);
	assert(hists_same(h9,h7)); 
	makehist(d4,h9); 
	assert(hists_same(h9,h8));
	assert(histo_has(h1,5)==true); 
	assert(histo_has(h1,0)==true); 
	assert(histo_has(h1,2)==false); 
	assert(histo_has(h2,5)==true); 
	assert(histo_has(h2,0)==true); 
	assert(histo_has(h2,2)==false);
	assert(histo_has(h3,3)==true); 
	assert(histo_has(h3,2)==true); 
	assert(histo_has(h3,1)==false); 
	assert(histo_has(h4,3)==true); 
	assert(histo_has(h4,2)==true); 
	assert(histo_has(h4,1)==false);
	assert(isfullhouse(d1)==true); 
	assert(isfullhouse(d2)==true); 
	assert(is4ofakind(d1)==false); 
	assert(is4ofakind(d2)==false); 
	assert(isfullhouse(d3)==false); 
	assert(isfullhouse(d4)==false);
	assert(is4ofakind(d3)==true);
	assert(is4ofakind(d4)==true); 
}
