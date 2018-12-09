	 .name     "0_tst      
.name     yolo   
.namezzz   
xxxx     "
.comment ""

l2: st r1, r1
sti r1, %:live, %1
live: live %1
zjmp %:live
gobepc: sti r1, :buff, %1
buff: st r1, r1
