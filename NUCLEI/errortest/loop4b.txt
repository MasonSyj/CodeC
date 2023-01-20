#No ( in loop function action stage.
#it will show when the first instrus also have no (

(   
   (SET C '5')
   (WHILE (LESS '0' C)
      PRINT C)
      (SET A (PLUS '-1' C))
      (SET C A))
   )
)