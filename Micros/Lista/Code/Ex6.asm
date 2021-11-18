; Nome: Murilo Mussatto		Nusp: 11234245
;
; Lista 1 - Ex 6 - Interrupcoes
;
;
;
;

;-------------- Jumps -------------------------------------------
    ORG     	0
    SJMP    	PROG
;************************************
    ORG		0003h
    SJMP	EXT0
;************************************
    ORG		000Bh
    SJMP	OFT0
;************************************
    ORG		0013h
    SJMP	EXT1
;************************************
    ORG		001Bh
    SJMP	OFT1
;************************************

;-------------- Programa ----------------------------------------
PROG:
	SETB 	EA		;Habilita Interrupcoes
	SETB 	EX0		;Habilita Interrupcao Externa 0
	SETB 	EX1		;Habilita Interrupcao Externa 1

	SETB 	IT0		;Habilita Descidada de Borda para EX0
	SETB 	IT1		;Habilita Descidada de Borda para EX1

	SETB 	ET0		;Habilita Timer 0
	SETB	ET1		;Habilita Timer 1
	MOV	TMOD, #11h	;Timer1: Software, Timer e Modo 1;  Timer0: Software, Timer e Modo 1

	MOV	TH0,#0D8h	;Timer 0: 10ms
	MOV	TL0,#0F0h
	SETB	TR0		;Inicia Timer 0

	MOV	TH1,#015h	;Timer 1: 60ms
	MOV	TL1,#0A0h
	SETB	TR1		;Inicia Timer 1

	SETB	PX0		;Alta prioridade para Interrupcao Externa 0
	CLR	PX1		;Baixa prioridade para Interrupcao Externa 1
	SETB	PT0		;Alta prioridade para o Timer 0
	CLR	PT1		;Baixa prioridade para o Timer 1


	;Valores Aleatorios Iniciais
	MOV 	P1,#0AAh

	MOV	7Fh,#0Fh

	MOV 	A,#0F0h
	MOV 	DPTR, #5000H
	MOVX 	@DPTR, A



	SJMP	$		;Fim Logico do Programa


;-------------- Interrupcoes ----------------------------------------
;**** Externa 0 ******
EXT0:
	PUSH ACC
	PUSH DPL
	PUSH DPH

	MOV	DPTR,#5000h	;Salva o que esta em 500h Externo em B
	MOVX	A,@DPTR
	MOV	B,A

	MOV	A,P1		;Salva P1 em 5000h Externo
	MOVX	@DPTR,A

	MOV	P1,B		;Transfere B para P1

	POP DPH
	POP DPL
	POP ACC

	RETI

;**** Externa 1 ******
EXT1:
	MOV	DPTR,#5000h
	MOVX	A,@DPTR
	MOV	7Fh,A

	RETI

;**** Timer 0 ******
OFT0:
	PUSH ACC
	PUSH DPL
	PUSH DPH

	MOV	A,7Fh		;Transfere o que estava em 7Fh
	MOV	DPTR,#5200h	;para 5200h na memoria externa
	MOVX	@DPTR,A

	MOV	TH0,#0D8h	;Timer 0: 10ms
	MOV	TL0,#0F0h

	POP DPH
	POP DPL
	POP ACC

	RETI

;**** Timer 1 ******
OFT1:

	MOV	DPTR,#5200h
	MOVX	A,@DPTR
	MOV	DPTR,#5000h
	MOVX	@DPTR,A

	MOV	TH1,#015h	;Timer 1: 60ms
	MOV	TL1,#0A0h

	RETI
;-------------- END ----------------------------------------------
	END