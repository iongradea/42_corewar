.name "1_tst"
.comment "f*ck"

l2:
sti r1, %:live, %1
live: live %1
zjmp %:live
gobepc: st r1, :l1+1
buff: st r1, r1
l1: live %1
