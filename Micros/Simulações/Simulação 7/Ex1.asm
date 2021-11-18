; Nome: Murilo Mussatto		Nusp: 11234245
;
; Simulação 7 - Senha com teclado matricial
;
;	Teclado:
;		P1.0 ate P1.3 --> entrada
;		P1.4 ate P1.7 --> saida
;
;	Senha:	7AB3#
;
;	20h.0 = 1 --> Senha Correta
;	20h.0 = 0 --> Senha Incorreta
;
;-------------- Jumps -------------------------------------------
    ORG     	0
    SJMP    	PROG
;************************************
    ORG		0003h
    SJMP	EXT0
;************************************

;-------------- Interrupcoes ----------------------------------------
;**** Externa 0 ******
EXT0:
	SETB	20h.0
	RETI

;-------------- Programa ----------------------------------------
PROG:
	SETB 	EA		;Habilita Interrupcoes
	SETB 	EX0		;Habilita Interrupcao Externa 0
	SETB 	IT0		;Habilita Descidada de Borda para EX0

	ACALL	RESET

INIC:  
	MOV    	P1, #0FFH
    	MOV    	R0, #07FH
    	ACALL	DELAY

LOOP:   ACALL   VARRE
	MOV    	A, P1
	ORL    	A, #0F0H
	CJNE    A, #0FFH, TECLA
	
	SJMP    LOOP


;******* Registra Tecla **********
TECLA:	MOV    	A, P1

	CJNE	R5,#0,T_R4
	MOV	R5,A
	SJMP    INIC

T_R4:	CJNE	R4,#0,T_R3
	MOV	R4,A
	SJMP    INIC

T_R3:	CJNE	R3,#0,T_R2
	MOV	R3,A
	SJMP    INIC

T_R2:	CJNE	R2,#0,GRADE
	MOV	R2,A
	SJMP    INIC

GRADE:	CJNE	A,#0B7h,T_RESET
	ACALL	VERIFICA	;Verifica Senha

	JNB	20h.0,T_ERRADO	;Senha Incorreta

	ACALL	S_CORRETA

    	SJMP    $		;Fim Logico do Programa

T_ERRADO:
	SETB	EA		;Habilita Tecla Secreta
L_LEDS:	MOV	P2,#0		;Ascende os LEDS
	ACALL	DELAY		;Delay
	MOV	P2,#0FFh	;Apaga os LEDS
	ACALL	DELAY
	JNB	20h.0,L_LEDS

T_RESET:
	ACALL	RESET
	SJMP	INIC

;******* Leitura **********
VARRE:	MOV    A, R0
    	MOV    P1, A
    	RR    A
    	JNB    ACC.3, FIM
    	MOV    R0, A
    	RET

FIM:    MOV    R0, #07FH
    	RET

;******* Verifica Senha **********
VERIFICA:
	CJNE	R5,#0EBh,V_RESET	;R5 = 7
	CJNE	R4,#7Eh,V_RESET		;R4 = A
	CJNE	R3,#7Dh,V_RESET		;R3 = B
	CJNE	R2,#0BEh,V_RESET	;R2 = 3
	SETB	20h.0			;Senha Correta
	RET

V_RESET:
	ACALL RESET
	RET

;******* RESET **********
RESET:
	MOV	R5,#0
	MOV	R4,#0
	MOV	R3,#0
	MOV	R2,#0
	CLR	20h.0
	CLR	EA
	MOV	P2,#0FFh
	RET

;******* Senha Incorreta **********
S_CORRETA:
	CLR	P2.0
	ACALL	DELAY
	CLR	P2.1
	ACALL	DELAY
	CLR	P2.2
	ACALL	DELAY
	CLR	P2.3
	ACALL	DELAY
	CLR	P2.4
	ACALL	DELAY
	CLR	P2.5
	ACALL	DELAY
	CLR	P2.6
	ACALL	DELAY
	CLR	P2.7
	ACALL	DELAY
	RET
;-------------- DELAY ----------------------------------------
DELAY:
; START: Wait loop, time: 0.5 ms
; Clock: 12000.0 kHz (12 / MC)
; Used registers: R6
	MOV	R6, #039h
	NOP
	DJNZ	R6, $
; Rest: 0
; END: Wait loop
	RET


;-------------- END ----------------------------------------------
	END
