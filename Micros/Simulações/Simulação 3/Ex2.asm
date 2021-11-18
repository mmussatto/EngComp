; Nome: Murilo Mussatto	Nusp: 11234245
; Simulacao 3 - Ex2 Led com duas frequencias
;
;
;	Bit de memoria 20h.0 foi usado para guardar a frequencia
;	20h.0 = 1 ---> 10Hz
;	20h.0 = 0 ---> 20Hz


	ORG 0
	SJMP PROG

	ORG 0003	;Atividada pela chave P3.2
	SJMP INT_EXT0

;-------------- Interrupcao Externa ------------------------------
INT_EXT0:
	CPL 20h.0
	RETI

;-------------- Programa ----------------------------------------
PROG:
	SETB 	EA		;Habilita Interrupcoes
	SETB 	EX0		;Habilita Interrupcao Externa 0
	SETB 	IT0		;Habilita Descida de Borda
	SETB 	20h.0		;Bit utilizado para armazenar a frequencia atual

LOOP:	JB 	20h.0,F10Hz	;verifica a frequencia

	CLR 	P2.2		;Led Aceso
	ACALL 	ATRASO_20HZ
	SETB 	P2.2		;Led Apagado
	ACALL 	ATRASO_20HZ
	SJMP 	LOOP


F10Hz:
	CLR 	P2.2		;Led Aceso
	ACALL 	ATRASO_10HZ
	SETB 	P2.2		;Led Apagado
	ACALL 	ATRASO_10HZ
	SJMP 	LOOP

	

ATRASO_10Hz:
; START: Wait loop, time: 10 ms
; Clock: 12000.0 kHz (12 / MC)
; Used registers: R0, R1
	MOV	R1, #015h	;#015h
	MOV	R0, #0ECh	;#0ECh
	NOP
	DJNZ	R0, $
	DJNZ	R1, $-5
	NOP
	NOP
	NOP
	RET
; Rest: 0
; END: Wait loop

ATRASO_20Hz:
; START: Wait loop, time: 20 ms
; Clock: 12000.0 kHz (12 / MC)
; Used registers: R0, R1
	MOV	R1, #063h	;063#
	MOV	R0, #063h	;063#
	NOP
	DJNZ	R0, $
	DJNZ	R1, $-5
	NOP
	RET
; Rest: 0
; END: Wait loop

;-------------------- Fim ---------------------------
	END
