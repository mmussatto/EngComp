;Nome: Murilo Mussatto
;NUSP: 11234245

;---- Programa -----------------------
	ORG	0

	MOV DPTR, #DADOS
	CLR A
	MOVC A,@A+DPTR
	MOV 30h, A

	INC DPTR
	CLR A
	MOVC A,@A+DPTR

	MOV DPTR, #1200h
	
	CJNE A,30h,TEST
TEST:	JC LT

	;Valor no 30h eh menor
	MOV A, 30h
	MOVX @DPTR, A
	SJMP FIM

LT:	MOVX @DPTR, A	;Valor no ACC eh menor


FIM:	SJMP	$

; --------- Dados -----------------

DADOS:	DB 1Dh, 0Ch

	END