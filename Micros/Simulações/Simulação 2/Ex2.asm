;Nome: Murilo Mussatto
;NUSP: 11234245



;---- Programa -----------------------
	ORG 0

	MOV DPTR, #1200h

LOOP:	MOV C, P1.0
	JC ABERTO


	;Carry = 0 -> Chave Fechada
	MOV A, #0FFh
	MOVX @DPTR,A
	SETB P3.0	;LED 1 Aceso
	CLR P3.1	;LED 2 Apagado
	SJMP LOOP

	
ABERTO:	;Carry = 1 -> Chave Aberta
	MOV A, #7Fh
	MOVX @DPTR,A
	CLR P3.0	;LED 1 Apagado
	SETB P3.1	;LED 2 Aceso
	SJMP LOOP


FIM:	SJMP $

; --------- Dados ----------------

	END