#the condition stage must have a bool func, if something else like length, come with error

(
   (IF (LENGTH (LENGTH A) (LENGTH '(1 2)')) ((PRINT "SAME LENGTH")) ((PRINT "NOT SAME LENGTH")))
)
