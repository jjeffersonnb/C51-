	    ORG 0000H
		MOV DPTR, #TABLE
LOOP0:	MOV R0, #00H
LOOP1:	MOV A, R0
  		MOVC A,@A+DPTR
		CPL A
		MOV P0, A
        ACALL DELAY
		INC R0
        CJNE R0,#08H,LOOP1
        SJMP LOOP0
DELAY:  MOV R1, #0     //—” ±≥Ã–Ú
        MOV R2, #0
LOOP3:  DJNZ R1, LOOP3
        DJNZ R2, LOOP3
        RET
TABLE:	DB 01H,02H,04H,08H,10H,20H,40H,80H
        END
