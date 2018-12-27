.name	"Booster !"
.comment "Alors la, si ca marche, trop content !  :)"

boost:	ld %12,r2
	ld %3,r3
	ld %4,r4
	ld %4,r7

	sti r1,%:live1,%1
live1:	live %66
	sti r1,%:fork0,%1
	sti r1,%:fork1,%1
	sti r1,%:fork2,%1
	sti r1,%:wait,%1
	sti r1,%:master,%1
	sti r1,%:numero1,%1
	sti r1,%:numero2,%1

	sti r1,%:live,%-4			# r1 -> %:live - 4 (00000001 / init : 54060305)
	ldi %:live,%-2,r6			# r6 = %:live - 2 = 00010b54 (init : 03050b54)
fork0:	live %66
	fork %:numero1
fork1:	live %66
	fork %:numero2
fork2:	live %66
#	fork %:fork0

master:	live %66				# r6 -> 0 + 5 (r7) / 0 + %:ecriture
	ld %0,r3
	ld %16777216,r6				# r6 = 01000000  
#	ldi %:master,%0,r6
	ld %0,r5
	zjmp %:ready

numero1: live %66				# r6 -> 3 + 5 (r7) / 3 + %:ecriture
	ld %3,r3
	ld %1,r15				
#	ldi %:live,%-2,r6
	ld %0,r5
	zjmp %:ready

numero2: live %66               # r6 -> 6 + 5 (r7) / 6 + %:ecriture
	ld %6,r3
	ld %1409680135,r6			# r6 = 54060307
#	ldi %:tampon,%1,r6
	ld %0,r5
	zjmp %:ready

tampon:	sti r6,r3,r5
live:	sti r1,r5,r5

ready:	sti r6,r3,%:ecriture

wait:	live %66				# numero1 : 0 / numero2 : 10 + 800 / numero3: 10 + 800 + 10
	zjmp %:ecriture

ecriture: zjmp %:wait



