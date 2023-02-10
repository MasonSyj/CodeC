(
   (SET A '(1 2 3 4)')
   (PRINT (CONS (CAR A) (CDR A)))
   (PRINT (CONS A (CDR A)))
   (PLUS '-1' '4')
   
   (PRINT A)
   (SET A '5')
   (IF (EQUAL A '10') ((PRINT "EQUAL")) ((PRINT "NOT EQUAL")))
   (IF (LESS A '10') ((PRINT "LESS")) ((PRINT "NOT LESS")))
   (IF (GREATER A '3') ((PRINT "GREATER")) ((PRINT "NOT GREATER")))
   (IF (LESS A '6') ((SET B '(1 2 3 4)')) ((SET C '(1 2 3 4)')))
   (PRINT B)
   (PRINT C)
   (PRINT D)
   
   (PRINT "Hello World")
   (SET A '(1 2 (3 4))')
   (PRINT A)
   (PRINT '(1 2 (3 4))')
   (PRINT NIL)
   (PRINT (CAR A))
   
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
   
   (SET C '5')
   (WHILE (LESS '0' C)(
      (PRINT C)
      (SET A (PLUS '-1' C))
      (SET C A))
   )
)