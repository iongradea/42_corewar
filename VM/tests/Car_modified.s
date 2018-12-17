.name "Car_modified.s"
.comment ""

	 ld    %-272,r3           		# 7,3,278
	 live  %0                 		# 5,10,271
	 fork  %:label01          		# 3,15,266

label01: ld    %-202,r3           		# 7,62,219
	 fork  %:label04          		# 3,69,212
	 ld    %0,r2              		# 7,72,209
	 zjmp  %:label05          		# 3,86,195

label04: ld    %4,r2              		# 7,89,192
	 zjmp  %:label05          		# 3,103,178

label05: ldi   r2,%:label14,r6    		# 6,233,48
	 ld    %0,r10              		# 7,239,42
	 live  %1                 		# 5,246,35

label14: sti   r6,r2,r3           		# 5,251,30
	 zjmp  %-207              		# 3,256,25

