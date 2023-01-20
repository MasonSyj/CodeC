(
   (SET C '5')
   (WHILE (LESS '0' C)(
      (PRINT C)
      (SET A (PLUS '-1' C))
      (SET C A))
   )
   
   (PRINT "Hello World.")
   
   (WHILE (LESS '0' C)(
      (PRINT "condition doesn't satisify, shouldn't print this line."))
   )
)
