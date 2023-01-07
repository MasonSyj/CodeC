bool isIsomorphic(char * s, char * t){
   int sflag[256] = {0};
   int tflag[256] = {0};
   while (*s != '\0'){
      if (sflag[*s] == 0){
          sflag[*s] = *t;
      }else if (sflag[*s] != *t){
          return false;
      }

      if (tflag[*t] == 0){
          tflag[*t] = *s;
      }else if (tflag[*t] != *s){
          return false;
      }

      s++;
      t++;
   }
   return true;
}
