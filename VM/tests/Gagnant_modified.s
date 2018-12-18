.name		"Celebration Funebre v0.99pl42"
.comment	"Jour J"

	ld   %0,r3		
	zjmp %:debut
label:		
	zjmp %:init
	zjmp %0				# pour eviter ecrasement
						# de l'instruction suivante
code:		
	live %42			# 5
	sti  r15,%0,r14			# 6
	zjmp %-200			# 3
	live %42			# 5
	sti  r15,%0,r14			# 6
	zjmp %-200			# 3
	live %42			# 5
	sti  r15,%0,r14			# 6
	zjmp %-200			# 3
	live %42			# 5
	sti  r15,%0,r14			# 6
	zjmp %-200			# 3
	sti  r15,%0,r14			# 6
	zjmp %-200			# 3
	sti  r15,%0,r14			# 6
	zjmp %-200
	
init:		
	ld   %393216,r4		 	# 7 / r4 = 00060000	
	ld   %917504,r12		# 7	/ r12 = 000e0000
	ld   %1,r11			#7
	ld   %6,r10			#7

debut:		
	live %42			# 5
	sti  r4,%:label , %1		# 7
	add  r4,r12,r4			# 5 / r4 = 00150000	
	sub  r10,r11,r10		# 5 / r10 = 00000007
#	ld %0, r1
	zjmp %:init			# 3
	fork %:debut			
	live %3

level0:		
	fork %:level10

level11:	
	live %4
	fork %:level111

level110:	
	live %42
	ldi  %8, %:code, r15		#set des octets 9-12
	ld   %-186, r14			#=$A-6-8
	ld   %0,r2
	zjmp  %:label
			
level10:	
	live %42
	fork %:level100

level101:	
	live %42
	ldi  %4, %:code, r15 		#set des octets 5-8
	ld   %-190, r14			#=$A-6-4
	ld   %0,r2
	zjmp %:label
		
level111:	
	live %42	
	ldi  %12, %:code, r15		#set des octets 13-16
	ld   %-182, r14			# $A -6 -12
	ld   %0,r2
	zjmp %:label
		
level100:	
	live %42
	ldi  %0, %:code, r15		#set des octets 1-4
	ld   %-194, r14			# $A -6 -0
	ld   %0,r2			#
	zjmp %:label			#
