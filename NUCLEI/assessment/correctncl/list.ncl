(
   (SET A '(1 2 3 4)')
   
   (SET B (CAR A))
   (SET C (CAR '((3 4) 5 6)'))
   (SET D (CAR (LENGTH A)))
   
   (SET E (CDR A))
   (SET F (CDR '((3 4) 5 6)'))
   (SET G (CDR (LENGTH A)))
   
   (SET E (CONS B C))
   (SET F (CONS B '(6 7 (8))'))
   (SET G (CONS B NIL))
   (SET H (CONS B (CONS '(6 7 (8))' (CDR '(5 (9 10) 7 8)'))))
   (SET I (CONS '(6 7 (8))' '((3 4) 5 9)'))
   (SET J (CONS (CONS '(6 7 (8))' (CDR '(5 (9 10) 7 8)')) (CONS (LENGTH (CONS '(-10 200 (233))' A)) (CDR '(678 (12 16) 320 63)'))))
   
   (PRINT A)
   (PRINT B)
   (PRINT C)
   (PRINT D)
   (PRINT E)
   (PRINT F)
   (PRINT G)
   (PRINT H)
   (PRINT I)
   (PRINT J)
   
)
