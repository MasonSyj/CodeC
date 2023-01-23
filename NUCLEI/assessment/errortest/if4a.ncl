#when first action stage miss a (, this issue will not be discovered if instrus func has a ( to supplement

(
   (IF (EQUAL (LENGTH A) (LENGTH '(1 2)')) (PRINT "SAME LENGTH")) ((PRINT "NOT SAME LENGTH")))
)
