#include <stdio.h>
#include <stdlib.h>

int comparator (const void * p1, const void * p2)
{
  return (*(int*)p1 - *(int*)p2);
}

int maxIceCream(int* costs, int costsSize, int coins){
   qsort(costs, costsSize, sizeof(int), comparator);
   if (costs[0] > coins){
       return 0;
   }
   int i = 0;
   int totalcosts = 0;
   do{
      totalcosts += costs[i++];
   }while (totalcosts <= coins && i < costsSize);

   if (i == costsSize){
      i--;   
   }

   if (totalcosts - costs[i] <= coins){
      return i;
   }else{
      return i - 1;
   }
}

int main(void){
   int arr[] = {7,3,3,6,6,6,10,5,9,2};
   int x = maxIceCream(arr, 10, 56);
   printf("%d\n", x);

}

//correct answer
/*
int maxIceCream(int* costs, int costsSize, int coins){
   qsort(costs, costsSize, sizeof(int), comparator);
   if (costs[0] > coins){
       return 0;
   }
   int icecream = 0;
   // Pick ice creams till we can.
   while (icecream < costsSize && costs[icecream] <= coins) {
      // We can buy this icecream, reduce the cost from the coins. 
      coins -= costs[icecream];
      icecream += 1;
   }
   return icecream;
}
*/
