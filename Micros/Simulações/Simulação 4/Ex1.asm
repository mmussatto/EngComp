; Nome: Murilo Mussatto	Nusp: 11234245
; Simulação 4 - Ex 1 - Onda quadrada com timers
;
;	Foi utilizado o bit 20H.0 para armazenar a frequencia atual
;
;	20H.0 = 0 --> 10Hz	20H.0 = 1 --> 20Hz
;
;	LED piscando no pino P2.0
;	Descidada de Borda em P3.2 --> Muda a Frequencia
;


;-------------- Jumps -------------------------------------------
    ORG     0
    SJMP    Prog
;************************************
    ORG    0003H
    SJMP    EXT0
;************************************
    ORG    000BH
    SJMP    OFT0
;************************************


;-------------- Programa ----------------------------------------
PROG:	SETB 	EA		;Habilita Interrupcoes
	SETB 	EX0		;Habilita Interrupcao Externa 0
	SETB 	ET0		;Habilita Timer 0
	SETB 	IT0		;Habilita Descidada de Borda para EX0
	SETB 	20h.0		;Bit utilizado para armazenar a frequencia atual
	MOV	TMOD, #01	;Timer0: Ativacao por Software, Timer e Modo 1

	CLR 	P2.0		;Led Aceso

LOOP:	JNB 	20h.0,F10Hz	;verifica a frequencia


	ACALL 	TIMER_20HZ
	JNB	P2.0, $		;espera o led apagar
	ACALL 	TIMER_20HZ
	JB	P2.0, $		;espera o led acender
	SJMP 	LOOP


F10Hz:
	ACALL 	TIMER_10HZ
	JNB	P2.0, $		;espera o led apagar
	ACALL 	TIMER_10HZ
	JB	P2.0, $		;espera o led acender
	SJMP 	LOOP


TIMER_20HZ:
	MOV 	TH0, #0FFH
	MOV 	TL0, #0CEH
	SETB 	TR0		;Dispara Timer 0
	RET



TIMER_10HZ:
	MOV 	TH0, #0FFH
	MOV 	TL0, #09CH
	SETB 	TR0		;Dispara Timer 0
	RET


;-------------- EXT0 ---------------------------------------------
EXT0:
	CPL	20h.0
	RETI

;-------------- OFT0 ---------------------------------------------
OFT0:
	CPL	P2.0
	RETI

;-------------- END ----------------------------------------------
	END




