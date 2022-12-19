#include <stdio.h>
#include <assert.h>

int maxProfit(int* prices, int pricesSize){
   int left = 0;
   int right = pricesSize - 1;
   int profit = 0;

   while (prices[left] > prices[right]){
      left++;
   }
   
   profit = prices[right] - prices[left];
   
   
}

int main(void) {
   int a[3] = {2, 4, 1};
   printf("%d", maxProfit(a, 3));
}
	
/* time complexity o(n)
int maxProfit(int* prices, int pricesSize){
   int profit;
   int max = 0;

   for (int i = 0; i < pricesSize - 1; i++){
       profit = prices[i + 1] - prices[i];
       for (int j = i + 1; j < pricesSize; j++){
          int this = prices[j] - prices[i];
          profit = this>profit?this:profit;
       }
       max = max>profit?max:profit;
   }

   return max;
}
*/

