.name "Car_simple_1.s"
.comment ""

start:
	ld %190055938,  r4    # 190055938
	ld %50921482, r5     # 50921867
	ld %10, r3
	ld %54, r2
	ld %15, r6
	st r4, :label00
	sti r5, %:label00, %4

label00:
					# sti , zjmp
