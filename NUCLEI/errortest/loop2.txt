#when the condition phase doesn't come with a boolfunc
#meanwhile, if it's func like length which require only one list, it will ignore this issue. 
#main issue is here lies the wrong type of funcions which fail the parse.
(   
   (SET C '5')
   (WHILE (LENGTH '0' C)(
      (PRINT C)
      (SET A (PLUS '-1' C))
      (SET C A))
   )
)
