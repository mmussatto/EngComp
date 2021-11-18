; Nome: Murilo Mussatto		Nusp: 11234245
;
; Lista 1 - Ex 7 - Frequencia de Onda Quadrada
;
;	DPTR é incrementado durante 1 segundo e depois enviado
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

	MOV	SCON,#40h	;Modo 1 (Variavel 10bits)

	MOV	TMOD,#20h	;Timer1: Software, Timer e Modo 2;

	MOV	PCON,#00h	;K = 1 --> Baud = 4800

	MOV	TH1,#250	;Timer 1: recarregavel com 250 decimal
	MOV	TL1,#250
	SETB	TR1		;Inicia Timer 1


LOOP:	MOV	DPTR,#0		;Reset DPTR

	ACALL	DELAY

	MOV	SBUF,DPL	;Enviar Menos Significativo
	JNB	TI,$
	CLR	TI

	MOV	SBUF,DPH	;Enviar Mais Significativo
	JNB	TI,$
	CLR	TI

	SJMP	LOOP

;-------------- DELAY ----------------------------------------------
DELAY:
; START: Wait loop, time: 1 s
; Clock: 12000.0 kHz (12 / MC)
; Used registers: R0, R1, R2, R3
	MOV	R3, #003h
	MOV	R2, #0D2h
	MOV	R1, #024h
	MOV	R0, #014h
	NOP
	DJNZ	R0, $
	DJNZ	R1, $-5
	DJNZ	R2, $-9
	DJNZ	R3, $-13
	MOV	R0, #059h
	DJNZ	R0, $
	NOP
; Rest: 0
; END: Wait loop
	RET
;-------------- Interrupcoes ----------------------------------------
;**** Externa 0 ******
EXT0:
	INC	DPTR
	RETI

;-------------- END ----------------------------------------------
	END