; Nome: Murilo Mussatto	Nusp: 11234245
; Simulacao 3 - Ex1 Onda Quadrada


;-------------- Programa ----------------------------------------
	ORG 0

	SETB P2.0
	CLR P2.1

LOOP:	ACALL ATRASO
	CPL P2.0
	CPL P2.1
	ACALL ATRASO

	SJMP LOOP


ATRASO:
; START: Wait loop, time: 50 us
; Clock: 12000.0 kHz (12 / MC)
; Used registers: R0
	MOV	R0, #018h
	NOP
	DJNZ	R0, $
	RET
; Rest: 0
; END: Wait loop

;-------------------- Fim ---------------------------
	END
	