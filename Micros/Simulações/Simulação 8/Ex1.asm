; Nome: Murilo Mussatto		Nusp: 11234245
;
; Simulação 8 - Ex 1 - Contador BCD 3 digitos
;
;
;	MSB = P1
;	ISB = P2
;	LSB = P0
;
;	Conta de 000 até 999
;
;	Interrupcao Externa 1 --> Pausa e retoma a contagem
;
;	20H.0 --> controla a contagem
;
;	R2 - R1 - R0 --> guardam o numero
;
;-------------- Jumps -------------------------------------------
    ORG     	0
    SJMP    	PROG
;************************************
    ORG		0013h
    SJMP	EXT1
;************************************

;-------------- Interrupcoes ----------------------------------------
;**** Externa 1 ******
EXT1:
	CPL	20H.0		;Complementa Bit de Contagem
	RETI

;-------------- Programa ----------------------------------------
; ~~~~ Setup ~~~~
PROG:
	SETB 	EA		;Habilita Interrupcoes
	SETB 	EX1		;Habilita Interrupcao Externa 1
	SETB 	IT1		;Habilita Descidada de Borda para EX1

	MOV 	DPTR,#DIGITOS	;Ponteiro para tabela de Digitos

	ACALL	RESET		;Reseta o Contador

	SETB	20H.0		;Comeca a contagem

; ~~~~ Loop principal ~~~~
LOOP:	JNB	20H.0, $	;Trava o programa caso contagem esteja desabilitada

; ~~~~ Verifica se o numero eh 999 ~~~~
	CJNE	R2,#9,D_ISB	;
	CJNE	R1,#9,D_LSB
	CJNE	R0,#9,DISP

	ACALL	RESET
	SJMP	LOOP

; ~~~~ Verifica se o numero eh X99 ~~~~
D_ISB:	CJNE	R1,#9,D_LSB
	CJNE	R0,#9,DISP

	ACALL	DISPLAY_MSB	;Incrementa MSB e mostra

	MOV	R1,#0FFh	;Reset ISB
	ACALL	DISPLAY_ISB	;Incrementa ISB e mostra

	MOV	R0,#0FFh	;Reset LSB
	ACALL	DISPLAY_LSB	;Incrementa LSB e mostra

	SJMP 	LOOP

; ~~~~ Verifica se o numero eh XX9 ~~~~
D_LSB:	CJNE	R0,#9,DISP

	MOV	R0,#0FFh
	ACALL	DISPLAY_ISB	;Incrementa o ISB e mostra

; ~~~~ Incrementa LSB e mostra ~~~~
DISP:	ACALL 	DISPLAY_LSB

	SJMP 	LOOP

;-------------- Funcoes ---------------------------------------------------------
; ~~~~ Incrementa e Mostra o LSB ~~~~
DISPLAY_LSB:
	MOV	P0,#0		;Reseta o Display
	INC	R0		;Incrementa LSB (R0)
	MOV	A,R0
	MOVC	A, @A+DPTR
	MOV	P0, A		;Envia digito para display do LSB
	RET

; ~~~~ Incrementa e Mostra o ISB ~~~~
DISPLAY_ISB:
	MOV	P2,#0		;Reseta o Display
	INC	R1		;Incrementa ISB (R1)
	MOV	A,R1
	MOVC	A, @A+DPTR
	MOV	P2, A		;Envia digito para display do ISB
	RET

; ~~~~ Incrementa e Mostra o MSB ~~~~
DISPLAY_MSB:
	MOV	P1,#0		;Reseta o Display
	INC	R2		;Incrementa MSB (R2)
	MOV	A,R2
	MOVC	A, @A+DPTR
	MOV	P1, A		;Envia digito para display do MSB
	RET

; ~~~~ Reseta o contador para 000 ~~~~
RESET:
	MOV	R0,#0		;Zera R1
	MOV	R1,#0		;Zera R2
	MOV	R2,#0		;Zera R3

	MOV	P1,#3FH		;Digito zero no display MSB
	MOV	P2,#3FH		;Digito zero no display ISB
	MOV	P0,#3FH		;Digito zero no display LSB

	RET

;-------------- Dados ----------------------------------------------

DIGITOS:	DB	3FH, 06H, 5Bh, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 6FH

;-------------- END ----------------------------------------------
	END