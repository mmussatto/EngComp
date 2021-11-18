; Nome: Murilo Mussatto		Nusp: 11234245
;
; Simulação 5 - Ex 1 - Comunicacao Serial sem Interrupcao
;
;	'G' --> 47h --> acende led P2.0
;	'Y' --> 59h --> acende led P2.4
;	'R' --> 52h --> acende led P2.7
;	'D' --> 44h --> apaga todos os leds
;
;	O programa fica esperando RI ser setada
;
;


;-------------- Programa ----------------------------------------
    	ORG     0
PROG:	MOV	TMOD,#20h	;Timer1: Ativacao por software, Timer e Modo 2 (8 bits auto-recarregavel)

	MOV	TH1, #253	;Valores para Timer 1
	MOV	TL1, #253

	MOV	PCON,#80h	;SMOD = 1 ---> K = 2

	MOV	SCON,#50h	;Modo 1 (variavel 10 bits), REN = 1, TI = RI = 0

	SETB	TR1		;Ativa timer 1

	MOV	P2,#0FFH	;Desliga Leds



LOOP:	JNB	RI, LOOP	;Espera um bit chegar
	ACALL	SERIAL		;Le o bit
	SJMP	LOOP


;-------------- Compare ----------------------------------------
COMPARE:
	CJNE	A,#'G',NOT_G
	CLR	P2.0		;G foi lido, ascende Led P2.0
	RET

NOT_G:	CJNE	A,#'Y',NOT_Y
	CLR	P2.4		;Y foi lido, ascende Led P2.4
	RET


NOT_Y: 	CJNE	A,#'R',NOT_R
	CLR	P2.7		;R foi lido, ascende Led P2.7
	RET

NOT_R:	CJNE	A,#'D',NOT_D
	MOV	P2,#0FFh	;D foi lido, apaga todos os leds
	RET

NOT_D:	RET


;-------------- SERIAL ----------------------------------------
SERIAL:
	MOV	A, SBUF		;Le o bit recebido no buffer
	ACALL 	COMPARE		;Verficia qual bit foi recebido
	CLR 	RI
	RET

;-------------- END ----------------------------------------------
	END