#include <stdio.h>

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize);

int main(void){
   int gas[] = {1, 2, 3, 4, 5};
   int cost[] = {3, 4, 5, 1, 2};
   int index = canCompleteCircuit(gas, 5, cost, 5);
   printf("%d\n", index);
}

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize){
   for (int j = 0; j < gasSize; j++){
      int cur = gas[j];
      for (int i = 0; i < gasSize; i++){
         cur = cur - cost[j];
//         printf("current gas: %d\n", cur);
         if (cur < 0){
            break;
         }
         cur += gas[(j+1) % gasSize];
      }
      if (cur > 0){
         return j;
      }
   }
   return -1;
}

//Best 
/*
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize){
   int total = 0, avail = 0, ind = 0;
   for (int i = 0; i < gasSize; i++){
       total += gas[i] - cost[i];
       avail += gas[i] - cost[i];
       if (avail < 0){
           avail = 0;
           ind = i + 1;
       }
   }
   return total < 0 ? -1: ind;
}
*/

/*
      int totalgas = 0;
      int totalcost = 0;
      for (int i = 0; i < gasSize; i++){
          totalgas += gas[i];
          totalcost += cost[i];
      }
      if (totalgas < totalcost){
          return -1;
      }
      int j = 0;
      int cur = gas[j];
      int mark = j;
      for (int i = 0; i < gasSize; i++){
         cur = cur - cost[j];
//         printf("current gas: %d\n", cur);
         if (cur < 0){
            j = ++mark;
            if (j >= gasSize){
                return -1;
            }
            cur = gas[j];
            i = -1;
            continue;
            
         }
         j++;
         j = j % gasSize;
         cur += gas[j];
         
      }
      if (cur > 0){
         return mark;
      }
      j = mark;
   return -1;
*/
