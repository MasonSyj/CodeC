(
   (SET Z '1')
   (PRINT Z)
   (SET A '(1 2 (3 4))')
   (PRINT A)
   (SET B A)
   (PRINT B)
   (SET C NIL)
   (PRINT C)
   (SET D (LENGTH A))
   (PRINT D)
   (SET E (CONS A (CONS (CAR (CDR A)) (CDR (CDR B)))))
   (PRINT E)
   (SET F '6')
   (PRINT F)
   (SET G (PLUS Z '4'))
   (PRINT G)
)