; Nome: Murilo Mussatto		Nusp: 11234245
;
; Lista 1 - Ex 9 - Robo desviando de Obstaculos
;
;	P1.0 --> Roda Esquerda: 1 - Ligado, 0 - Desligado
;	P1.1 --> Direcao  Roda Esquerda: 1 - Frente 0 - Tras
;	P1.2 --> Roda Direita: 	1 - Ligado, 0 - Desligado
;	P1.3 --> Direcao Roda Direita: 1 - Frente 0 - Tras
;
;	INT_0 --> Obstaculos
;
;	20h.0 --> Direcao:	1 - Direita, 0 - Esquerda
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

	MOV	P1,#0		;Reset no pino P1

	SETB	P1.0		;Roda esquerda ligada
	SETB	P1.2		;Roda direita ligada

	SETB	20h.0		;Robo comeca virando para a direita

	ACALL 	FRENTE		;Robo anda para frente

	SJMP	$		;Fim Logico do Programa


;-------------- Movimento ----------------------------------------
;**** Para Frente ******
FRENTE:
	SETB	P1.1		;Roda esquerda p/ frente
	SETB	P1.3		;Roda direita p/ frente

	RET
;**** Para Tras ******
TRAS:
	CLR	P1.1		;Roda esquerda p/ tras
	CLR	P1.3		;Roda direita p/ tras

	RET
;**** Para Direita ******
DIREITA:
	SETB	P1.1		;Roda esquerda p/ frente
	CLR	P1.3		;Roda direita p/ tras

	RET
;**** Para Esquerda ******
ESQUERDA:
	CLR	P1.1		;Roda esquerda p/ tras
	SETB	P1.3		;Roda direita p/ frente

	RET
;-------------- DELAY ----------------------------------------------
DELAY:
; START: Wait loop, time: 2 s
; Clock: 12000.0 kHz (12 / MC)
; Used registers: R0, R1, R2, R3
	MOV	R3, #003h
	MOV	R2, #0D2h
	MOV	R1, #00Ch
	MOV	R0, #082h
	NOP
	DJNZ	R0, $
	DJNZ	R1, $-5
	DJNZ	R2, $-9
	DJNZ	R3, $-13
	MOV	R1, #006h
	MOV	R0, #0BAh
	NOP
	DJNZ	R0, $
	DJNZ	R1, $-5
	NOP
	NOP
	NOP
; Rest: 0
; END: Wait loop
	RET
;-------------- Interrupcoes ----------------------------------------
;**** Externa 0 ******
EXT0:
	CLR 	EA		;Desabilita Interrupcao INT0

	ACALL	TRAS		; Robo anda para tras por
	ACALL	DELAY		;dois segundos
	JNB	20h.0, VIRAESQ	;Verifica a ultima direcao

	ACALL	DIREITA		;Robo vira para a direita
	SJMP	FIM_INT

VIRAESQ:
	ACALL	ESQUERDA	;Robo vira para a esquerda



FIM_INT:
	CPL	20h.0		;Inverte a direcao
	ACALL 	DELAY		;Delay de 2s
	ACALL 	FRENTE		;Robo volta a andar para a frente

	SETB	EA		;Reabilita Interrupcoes
	RETI

;-------------- END ----------------------------------------------
	END