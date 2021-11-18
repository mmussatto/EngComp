; Nome: Murilo Mussatto		Nusp: 11234245
;
; Lista 1 - Ex 1 - Contador

;-------------- Jumps -------------------------------------------
    ORG     	0
    SJMP    	PROG
;************************************
    ORG		000Bh
    SJMP	OFT0
;************************************

;-------------- Programa ----------------------------------------
PROG:
	SETB 	EA		;Habilita Interrupcoes
	SETB 	ET0		;Habilita Timer 0
	MOV	TMOD, #01	;Timer0: Ativacao por Software, Timer e Modo 1

	MOV	A,#100		;Contador vai rodar 100 vezes para resultar em 5 segundos
	CLR	20h.0		;Controle do Timer

LOOP:	JB	20h.0,$		;Espera enquanto 20h.0 = 1
	JNZ	LOOP		;Loop enquanto ACC nao for zero
	ACALL	TIMER_0		;Chama timer de 0,05s


	SJMP	$		;Fim Logico do Programa



TIMER_0:
	MOV	TH0,#03Ch
	MOV	TL0,#0B0h
	SETB	TR0		;Inicia Timer
	SETB	20h.0		;Deixa o programa em Loop
	RET


;-------------- Contador ----------------------------------------
OFT0:
	CLR	20h.0
	DEC	A
	RETI

;-------------- END ----------------------------------------------
	END