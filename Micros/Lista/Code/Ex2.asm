; Nome: Murilo Mussatto		Nusp: 11234245
;
; Lista 1 - Ex 2 - Interrupcoes


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

;-------------- Programa ----------------------------------------
PROG:
	SETB 	EA		;Habilita Interrupcoes
	SETB 	EX0		;Habilita Interrupcao Externa 0
	SETB 	EX1		;Habilita Interrupcao Externa 1

	SETB 	IT0		;Habilita Descidada de Borda para EX0
	SETB 	IT1		;Habilita Descidada de Borda para EX1

	SETB	PX0		;Alta prioridade para Interrupcao Externa 0
	SETB	PX1		;Alta prioridade para Interrupcao Externa 1
	
	SETB 	ET0		;Habilita Timer 0
	MOV	TMOD, #02	;Timer0: Ativacao por Software, Timer e Modo 2

	MOV	TH0,#0FCh
	MOV	TL0,#018h
	SETB	TR0		;Inicia Timer

	;Valores Aleatorios Iniciais
	MOV 	P2,#0AAh

	MOV 	A,#0Ah
	MOV 	DPTR, #4000H
	MOVX 	@DPTR, A
	
	MOV 	A, #0FFH
	MOV 	DPTR, #4200H
	MOVX 	@DPTR, A



	SJMP	$		;Fim Logico do Programa


;-------------- Interrupcoes ----------------------------------------
;**** Externa 0 ******
EXT0:
	CLR	EA

	MOV	DPTR,#4000h
	MOVX	A,@DPTR
	MOV	DPTR,#4200h
	MOVX	@DPTR,A

	SETB	EA
	RETI

;**** Externa 1 ******
EXT1:
	MOV	DPTR,#4200h
	MOVX	A,@DPTR
	MOV	P1,A

	RETI

;**** Timer 0 ******
OFT0:
	MOV	A,P2
	MOV	DPTR,#4000h
	MOVX	@DPTR,A

	RETI
;-------------- END ----------------------------------------------
	END