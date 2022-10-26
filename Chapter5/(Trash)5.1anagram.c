#include <stdio.h>
#include <string.h>
#include <assert.h>

#define N 8

void swap(char* a, char* b);
void permuate(char a[], int n);
void permuatecnt(char a[], int n);
void test();

const char* array[] = {"angriest", "astringe","ganister", "gantries", "ingrates","rangiest","reasting","stearing"};

int main(int argc, char* argv[]){
//	test();
	char a[] = "sternaig";
	permuatecnt(a, N - 1);
}

void swap(char* a, char* b){
	char temp = *a;
	*a = *b;
	*b = temp;
}

void permuatecnt(char a[], int n){
	if (n == 0){
		for (int x = 0; x < N; x++){
			if (strcmp(a, array[x]) == 0){
				puts(array[x]);
			}		
		}
		return;
	}
	
	for (int i = n; i >= 0; i--){
		swap(&a[i], &a[n]);
		permuatecnt(a, n - 1);
		swap(&a[i], &a[n]);
	}
}

void permuate(char a[], int n){
	
	if (n == 0){
		puts(a);
		return;
	}
	
	
	for (int i = n; i >= 0; i--){
		swap(&a[i], &a[n]);
		permuate(a, n - 1);
		swap(&a[i], &a[n]);
	}
}

void test(){
	char a[] = "inegnreteni";
	swap(&a[0], &a[1]);
	assert(a[0] == 'n');
	assert(a[1] == 'i');
	char c[] = "ABC";
	permuate(c, N - 1);
}
