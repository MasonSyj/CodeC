#No ( in loop function action stage.
#but it will not be discovered if the instru has a ( to supplement

(   
   (SET C '5')
   (WHILE (LESS '0' C)
      (PRINT C)
      (SET A (PLUS '-1' C))
      (SET C A))
   )
)