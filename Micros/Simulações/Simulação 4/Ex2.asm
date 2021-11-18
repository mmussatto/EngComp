; Nome: Murilo Mussatto	Nusp: 11234245
; Simulação 4 - Ex 2 - Contador de Pulsos
;
;	Acumulador foi usado para guardar o estado dos LEDs
;
;	Apos  5 pulsos no pino P3.5 --> LED P2.0 Acende
;	Apos 15 pulsos no pino P3.5 --> LED P2.1 Acende
;	Apos 35 pulsos no pino P3.5 --> LED P2.2 Acende
;
;	Descidada de Borda em P3.2 --> Apaga LEDs, recomeca o contador
;



;-------------- Jumps -------------------------------------------
    ORG     0
    SJMP    Prog
;************************************
    ORG    0003H
    SJMP    EXT0
;************************************
    ORG    001BH
    SJMP    OFT1
;************************************


;-------------- Programa ----------------------------------------
PROG:	SETB 	EA		;Habilita Interrupcoes
	SETB 	EX0		;Habilita Interrupcao Externa 0
	SETB 	ET1		;Habilita Timer 1
	SETB 	IT0		;Habilita Descidada de Borda para EX0

	MOV	TMOD, #50H	;Timer1: Ativacao por Software, Contador e Modo 1 --> 01010000B = 50H

	MOV	TH1, #0FFH	;Counter Faltando 5
	MOV	TL1, #0FBH

	SETB 	TR1		;Inicia Counter

	CLR 	A		;Zera Acumulador

	SJMP $




;-------------- EXT0 ---------------------------------------------
EXT0:
	CLR A			;Zera o Acumulador
	MOV P2, #0FFH		;Apaga LEDs
	MOV	TH1, #0FFH	;Counter faltando 5
	MOV	TL1, #0FBH
	RETI

;-------------- OFT1 ---------------------------------------------
OFT1:
	CJNE	A, #00, LED_2
	CPL 	P2.0		;Acende Led 3
	MOV	TH1, #0FFH	;Counter faltando 10
	MOV	TL1, #0F6H
	INC 	A
	RETI

LED_2:	CJNE 	A, #01, LED_3
	CPL 	P2.1		;Acende Led 2
	MOV	TH1, #0FFH	;Counter faltando 20
	MOV	TL1, #0ECH
	INC 	A
	RETI

LED_3:	CPL P2.2		;Acende Led 3
	INC A
	RETI

;-------------- END ----------------------------------------------
	END
