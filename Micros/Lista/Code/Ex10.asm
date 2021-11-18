; Nome: Murilo Mussatto		Nusp: 11234245
;
; Lista 1 - Ex 10 - Maquina de Doces
;
;	INT0 --> Detecta Moeda
;
;	P1.0, P1.1 e P1.2 --> Identifica Moeda
;
;	P2.0 --> Fornece Doce
;	P2.1 --> Devolve  5 cents
;	P2.2 --> Devolve 10 cents
;
;-------------- Jumps -------------------------------------------
    ORG     	0
    SJMP    	PROG
;************************************
    ORG		0003h
    SJMP	EXT0
;************************************

;-------------- Programa ----------------------------------------
PROG:
	SETB 	EA		;Habilita Interrupcoes
	SETB 	EX0		;Habilita Interrupcao Externa 0
	SETB 	IT0		;Habilita Descidada de Borda para EX0

	ACALL 	RESET

LOOP:	CJNE	A,#20,TEST	;Espera soma dar >= 20
TEST:	JC	LOOP

	CJNE	A,#20,R_25

	;Resultado eh 20
	ACALL	DOCE
	SJMP	FIM

R_25:	CJNE	A,#25,R_30

	;Resultado eh 25
	ACALL	DOCE
	ACALL	T_5
	SJMP	FIM

R_30:	CJNE	A,#30,R_35

	;Resultado eh 30
	ACALL	DOCE
	ACALL	T_10
	SJMP	FIM

R_35:	;Resultado eh 35
	ACALL	DOCE
	ACALL	T_5
	ACALL	T_10

FIM:	ACALL 	DELAY
	ACALL	RESET
	SJMP	LOOP


;**** Doce ******
DOCE:	SETB	P2.0		;Fornece Doce
	RET

;**** TROCO 5 cents ******
T_5:	SETB	P2.1		;Retorna moeda de 5 cents
	RET

;**** TROCO 10 cents ******
T_10:	SETB	P2.2		;Retorna moeda de 10 cents
	RET

;**** Reset ******
RESET:	MOV	P1,#0FFh	;Reset no pino P1
	MOV	P2,#0		;Reset no pino P2
	MOV	A,#0		;Reset no ACC
	RET
;-------------- Interrupcoes ----------------------------------------
;**** Externa 0 ******
EXT0:
	CLR 	EA		;Desabilita Interrupcao INT0
	PUSH	PSW		;Salva o Carry

	JNB	P1.2,M_20	;Moeda de 20 Cents

	JNB	P1.1,M_10	;Moeda de 10 Cents

	ADD	A,#05		;Moeda de 5 Cents
	SJMP	FIM_INT

M_20:	ADD	A,#20
	SJMP	FIM_INT

M_10:	ADD	A,#10

FIM_INT:
	SETB	EA		;Reabilita Interrupcoes
	POP	PSW		;Recupera o Carry
	RETI
	
;-------------- DELAY ----------------------------------------------
DELAY:
; START: Wait loop, time: 0.5 ms
; Clock: 12000.0 kHz (12 / MC)
; Used registers: R0
	MOV	R0, #0F9h
	NOP
	DJNZ	R0, $
; Rest: 0
; END: Wait loop
RET

;-------------- END ----------------------------------------------
	END