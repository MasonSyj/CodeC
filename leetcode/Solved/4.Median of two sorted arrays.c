#include <stdio.h>
#include <stdlib.h>

// 1 3 5 7 9
// 2 4 6 8 10
//12 14 16 18 20

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size);

int main(void){
    int a[] = {1, 3, 5, 7, 9, 11, 13};
    int b[] = {2, 4, 6, 8, 10, 12};
    int numa = 7;
    int numb = 6;
    double x = findMedianSortedArrays(a, numa, b, numb);
    printf("%f", x);
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int i, j, k;
    i = j = k = 0;
    int sum = nums1Size + nums2Size;
    int* a = (int*)malloc(sum * sizeof(int));
//  int a[sum];
    while (k < sum && i < nums1Size && j < nums2Size){
        
        if (nums1[i] < nums2[j]){
            a[k++] = nums1[i];
            i++;
        }else {
            a[k++] = nums2[j];
            j++;
        }
    }
    
    while (i == nums1Size && j < nums2Size){
        a[k++] = nums2[j++];
    }
    while (j == nums2Size && i < nums1Size){
        a[k++] = nums1[i++];
    }
    
    double result;
    
    if (sum % 2 == 0){
        result =  (double) (a[sum/2] + a[sum/2 - 1]) / 2;
    }else{
        result =  a[sum/2];
    }
    free(a);
    return result;
}

