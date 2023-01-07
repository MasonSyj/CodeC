bool isSubsequence(char * s, char * t){
   while (*s != '\0' && *t != '\0'){
      if (*s != *t){
          t++;
          continue;
      }else{
          s++;
          t++;
          continue;
      }

      if (*t == '\0'){
          return false;
      }
   }

   if (*s == '\0'){
      return true;
   }else{
      return false;
   }
}
