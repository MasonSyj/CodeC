int min(int a, int b){
    if (a < b){
        return a;
    }else{
        return b;
    }
}

int minCost(int* cost, int n){
   if (n <= 1){
       return cost[n];
   }else{
       return cost[n] + min(minCost(cost, n - 1), minCost(cost, n - 2));
   }
}

int minCostClimbingStairs(int* cost, int costSize){
    return min(minCost(cost, costSize - 1), minCost(cost, costSize - 2));
}