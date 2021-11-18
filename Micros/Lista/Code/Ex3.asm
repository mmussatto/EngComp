; Nome: Murilo Mussatto		Nusp: 11234245
;
; Lista 1 - Ex 3 - Controle de Nivel
;
;  Sensores:	Dentro do Liquido = 1;	Fora do Liquido = 0
;	S1 -->	INT_0
;	S2 -->	INT_1
;
;  Valvula:
;	V1 --> P1.0   	Drenar
;	V2 --> P1.1	Encher
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

	SETB	P1.1		;Abre valvula V2 para encher o tanque
	CLR	P1.0		;Fecha a valvula V1 de dreno

	SJMP	$		;Fim Logico do Programa

;-------------- Interrupcoes ----------------------------------------
;**** Externa 0 ******
EXT0:
	SETB	P1.1	;Abre valvula V2 para encher o tanque
	CLR	P1.0	;Fecha valvula V1
	RETI

;**** Externa 1 ******
EXT1:
	SETB	P1.0	;Abre valvula V1 para drenar o tanque
	CLR	P1.1	;Fecha valvula V2
	RETI

;-------------- END ----------------------------------------------
	END