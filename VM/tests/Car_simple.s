.name "Car_simple.s"
.comment ""

start:
	ld %-272, r3
	live %0
	fork %:label01
	ld %-272, r3
	fork %:label02

label01: 
	ld %-202, r3
	ld %0, r2
	ld %0, r4
	zjmp %:label05

label05:
	ldi r2, %:label14, r6
	ld %0, r4
	live %1

label14:
	sti r6, r2, r3
	zjmp %:label02              # %-207

label02:
	ld %4, r2
	ld %0, r4
	zjmp %:label03

label03: ldi r2, %:label12, r6             
	ld %0, r4
	live %1

label12:
	sti r6, r2, r3
	zjmp %:label08                       # %-277

label08:
	ldi r2, %:label13, r6
	zjmp %:label00                                # %395

label00:
	zjmp %:start

# label01 -> label05 -> label14
# label14 -> label02 -> label03
# label12 -> label08 -> label00 
