.name "Car_simple_2.s"
.comment ""

start:
	ld %190055938, r2 # r4    # 190055938
	ld %50921482, r3 # r5     # 50921867
	ld %15, r6
	st r2, :label00
	sti r3, %:label00, %4

label00:
					# sti , zjmp
