; Nome: Murilo Mussatto		Nusp: 11234245
;
; Simulação 6 - Contador BCD controlado por Interrupção
;
;	INT0 --> Inicia Contagem
;	INT1 --> Para Contagem
;
;	R0 --> Valor em Hex atual
;


;-------------- Jumps -------------------------------------------
    ORG     	0
    SJMP    	PROG
;************************************
    ORG		0003H
    SJMP	INT_0
;************************************
    ORG		0013H
    SJMP	INT_1
;************************************

;-------------- Programa ----------------------------------------
PROG:
	SETB	EX0		;Habilita Interrupcao Externa 0
	SETB	EX1		;Habilita Interrupcao Externa 1
	SETB	EA		;Habilita Interrupcoes
	SETB	IT0		;Descida de borda para IT0
	SETB	IT1		;Descida de borda para IT1


INIC:	MOV	A,#00		;Zera o Acumulador


LOOP:
	JNB	20h.0,$		;Para a contagem enquanto 20h.0 estiver em 0

	MOV 	R0,A		;Salva acumulador em R0
	ACALL 	CONVBCD
	ACALL	LEDS
	ACALL 	DELAY
	MOV	A,R0		;Recupera valor em hexa atual
	INC	A
	CJNE	A,#064h,LOOP	;Volta para loop se menor que 064h (100 decimal)
	SJMP	INIC		;Reseta se maior que 064h (100 decimal)




;************ Mostra LED ***************
LEDS:
	CPL	A		;Complementa pois Led Aceso = 0
	MOV	P2, A
	RET

;************ Conversão ***************
CONVBCD:
	MOV	B, #0Ah
	DIV	AB		;Divide o numero hex por 0A --> BCD Unpacked: MSB - A  e  LSB - B
	MOV	R2, A		;Salva MSB decimal
	MOV 	R1, B		;Salva LSB decimal
	SWAP	A		;Inverte MSB
	ORL	A, R1		;Junta os decimais
	RET

;************ Delay ***************
DELAY:
; START: Wait loop, time: 200 us
; Clock: 12000.0 kHz (12 / MC)
; Used registers: R3
	MOV	R3, #063h
	NOP
	DJNZ	R3, $
	RET

;-------------- Interrupcoes ----------------------------------------
;************ INT_0 ***************
INT_0:
	SETB	20h.0		;Inicia Contagem
	RETI
;************ INT_1 ***************
INT_1:
	CLR 	20h.0		;Para Contagem
	RETI
	
;-------------- END ----------------------------------------------
	END