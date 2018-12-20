.name	"Booster !"
.comment "Alors la, si ca marche, trop content !  :)"

boost:	
	ld %5, r7                # 7, 0 - 5, 0
	sti r1,%:live1,%1		# 7, 7 - 25, 30

live1:	
	live %66				# 5, 12 - 10, 40
	sti r1,%:fork0,%1		# 7, 19 - 25, 65
	sti r1,%:fork1,%1		# 7, 26 - 25, 90
	sti r1,%:fork2,%1		# 7, 33 - 25, 115
	sti r1,%:wait,%1		# 7, 40 - 25, 140
	sti r1,%:master,%1		# 7, 47 - 25, 165
	sti r1,%:numero1,%1		# 7, 54 - 25, 190
	sti r1,%:numero2,%1		# 7, 61 - 25, 215

	ldi %:live,%-2,r6		# 7, 68 - 25, 240 / ptr : 184 => 0x03050b54 / used for numero1

fork0:	
	live %66				# 5, 73 - 10, 250
	fork %:numero1			# 3, 76 - 800, 1050

fork1:	
	live %66				# 5, 81 - 10, 1060
	fork %:numero2			# 3, 84 - 800, 1860

fork2:	
	live %66				# 5, 89 - 10, 1870


master:			#	ldi %:master,%0,r6
	live %66				# 5, 94 - 10, 1880
	ld %0,r3				# 7, 101 - 5, 1885
	ld %16777216,r6			# 7, 108 - 5, 1890 / 0x01000000
	ld %0,r5				# 7, 115 - 5, 1895
	zjmp %:ready			# 3, 118 - 20, 1915, 45

numero1:		#	ldi %:live,%-2,r6       # put before in live1
	live %66				# 5, 123 - 10, 1925
	ld %3,r3				# 7, 130 - 5, 1930
	ld %1,r2				# 7, 137 - 5, 1935 / useless, only to keep cycle count
	ld %0,r5				# 7, 144 - 5, 1940
	zjmp %:ready			# 3, 147 - 20, 1960, 45

numero2:		#	ldi %:tampon,%1,r6	
	live %66				# 5, 152 - 10, 1970
	ld %6,r3				# 7, 159 - 5, 1975
	ld %1409680135,r6		# 7, 166 - 5, 1980 / 0x54060307
	ld %0,r5				# 7, 173 - 5, 1985
	zjmp %:ready			# 3, 176 - 20, 2005, 45

tampon:	
	sti r6,r3,r5			# 5, 181 - 25, 2030

live:	
	sti r1,r5,r5			# 5, 186 - 25, 2055
	
ready:	
	sti r6,r3,%:ecriture	# 6, 192 - 25, 2080

wait:	
	live %66				# 5, 197 - 10, 2090
	zjmp %:ecriture			# 3, 200 - 20, 2110

ecriture: 
	zjmp %:wait				# 3, 203 - 20, 2130, 50
