;Nome: Murilo Mussatto
;NUSP: 11234245


;---- Programa -----------------------
	ORG 0

INICIO:
	SETB P1.0	;L1 APAGADO
	SETB P1.1	;L2 APAGADO
	SETB P1.2	;L3 APAGADO

	MOV C, P3.5
	JNC CH1_FECHADO		;Carry = 0 -> Chave Fechada
				;Carry = 1 -> Chave Aberta
	MOV C, P3.6
	JNC CH2_FECHADO

	MOV C, P3.7
	JNC CH3_FECHADO

	SJMP INICIO

CH1_FECHADO:

	CLR P1.0	;L1 ACESO
	ACALL DELAY	;Atraso de 1s aproximadamente
	SETB P1.0	;L1 APAGADO
	ACALL DELAY	;Atraso de 1s aproximadamente
	SJMP INICIO



CH2_FECHADO:

	CLR P1.1	;L2 ACESO
	ACALL DELAY	;Atraso de 1s aproximadamente
	SETB P1.1	;L2 APAGADO
	ACALL DELAY	;Atraso de 1s aproximadamente
	SJMP INICIO


CH3_FECHADO:

	CLR P1.2	;L3 ACESO
	SETB P1.0	;L1 APGADADO
	ACALL DELAY	;Atraso de 1s aproximadamente
	SETB P1.2	;L3 APAGADO
	CLR P1.0	;L1 ACESO
	ACALL DELAY	;Atraso de 1s aproximadamente
	SJMP INICIO


FIM:	SJMP $



DELAY:
	mov R2,#02h	; Eh necessario ajustar os valores para obter um atraso de 1HZ
Loop1: 	mov R1,#02h	;como o simulador fica muito lento, optei por deixar um valor mais baixo
Loop:	mov R0,#0Fh	;mas que demonstre o funcionamento do circuito
	djnz R0, $
	djnz R1, Loop
	djnz R2, Loop1
	ret

; --------- Dados ----------------

	END