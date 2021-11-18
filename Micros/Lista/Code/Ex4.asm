; Nome: Murilo Mussatto		Nusp: 11234245
;
; Lista 1 - Ex 4 - Teste Termico
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

	MOV	P2,#0
	MOV	P1,#0

	MOV	A,#03		;Ciclo ocorrera 3 vezes

LOOP:	SETB	20h.0		;Controle do Ciclo

	SETB	P2.7		;Direcao p/ baixo
	SETB	P2.6		;Liga o motor


	JB	20h.0, $	;Aguarda o Ciclo Acabar
	DJNZ	ACC,LOOP	;Se A diferente de 0, ainda restam ciclos

	SJMP	$		;Fim Logico do Programa

;-------------- Delay ----------------------------------------------
DELAY:
; START: Wait loop, time: 500 ms
; Clock: 12000.0 kHz (12 / MC)
; Used registers: R0, R1, R2
	MOV	R2, #004h
	MOV	R1, #0FAh
	MOV	R0, #0F8h
	NOP
	DJNZ	R0, $
	DJNZ	R1, $-5
	DJNZ	R2, $-9
; Rest: -13.0 us
; END: Wait loop
	RET

;-------------- Interrupcoes ----------------------------------------
;**** Externa 0 ******
EXT0:
	CLR 	P2.6	;Desliga Motor
	SETB	P1.2	;liga Forno
	ACALL	DELAY	;Delay de 500ms
	CLR	P1.2	;Deliga Forno
	CLR	P2.7	;Direcao p/ cim
	SETB	P2.6	;Liga Motor
	RETI

;**** Externa 1 ******
EXT1:
	CLR 	P2.6	;Desliga Motor
	SETB	P1.0	;Liga Resfriamento
	ACALL 	DELAY	;Delay de 500ms
	CLR	P1.0	;Desliga Resfriamento
	CLR	20h.0	;Controle do Ciclo
	RETI

;-------------- END ----------------------------------------------
	END