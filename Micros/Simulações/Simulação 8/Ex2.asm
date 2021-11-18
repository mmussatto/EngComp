; Nome: Murilo Mussatto		Nusp: 11234245
;
; Simulação 8 - Ex 2 - Contador BCD 4 digitos multiplexado
;
;
;	Conta de 0000 até 9999
;
;	Interrupcao Externa 1 --> Pausa e retoma a contagem
;
;	20H.0 --> controla a contagem
;
;	34H - 33H - 32H - 31H --> guardam o numero
;
;	R0 --> Endereco do Digito durante Contador
;	R1 --> Endereco do Digito durante Display
;	R7 --> Guarda qual display esta ativo
;
;	P0 --> Controla qual display est[a ativo
;	P2 --> Digito a ser mostrado no display
;
;	Fade out Interval --> 50
;
;-------------- Jumps -------------------------------------------
    ORG     	0
    SJMP    	PROG
;************************************
    ORG		000Bh
    SJMP	TIM0
;************************************
    ORG		0013h
    SJMP	EXT1
;************************************

;-------------- Interrupcoes ----------------------------------------
;**** Externa 1 ******
EXT1:
	CPL	20H.0		;Complementa Bit de Contagem
	RETI

;**** Timer 0 ******
TIM0:
	CLR	EA

	MOV	R1,#31H
	ACALL	DISPLAY
	MOV	TH0,#0FFH
	MOV	TL0,#0FAH

	SETB	EA
	RETI

;-------------- Programa ----------------------------------------
; ~~~~ Setup ~~~~
PROG:
	SETB 	EA		;Habilita Interrupcoes
	SETB 	EX1		;Habilita Interrupcao Externa 1
	SETB 	IT1		;Habilita Descidada de Borda para EX1

	SETB	ET0		;Habilita Interrupcao Timer 0
	MOV	TMOD,#01	;Timer 0 --> Software, Timer Modo 1

	ACALL	RESET

	MOV 	DPTR,#DIGITOS	;Ponteiro para tabela de Digitos

	SETB	20H.0		;Comeca a contagem

	MOV	TH0,#0FFH
	MOV	TL0,#0FAH

;	preferi nao utilizar o contador pra mostrar os digitos no display;
;	nao consegui acertar o valor do fade out e do contador para ficar uma animacao boa;
;	fora que usando o contador baixo, demorava para mudar de numero;
;	usando um contador alto, as vezes a contagem pulava alguns numeros;
;
;	SETB	TR0

; ~~~~ Loop principal ~~~~
LOOP:	MOV	R1,#31H
	ACALL	DISPLAY
	JNB	20H.0, $	;Trava o programa caso contagem esteja desabilitada

; ~~~~ Verifica se o numero eh 9999 ~~~~
	MOV	R0,#34H
	CJNE	@R0,#9,LOOP4
	DEC	R0
	CJNE	@R0,#9,LOOP3
	DEC	R0
	CJNE	@R0,#9,LOOP2
	DEC	R0
	CJNE	@R0,#9,LOOP1

	ACALL	RESET
	SJMP	LOOP

; ~~~~ Verifica se o numero eh X999 ~~~~
LOOP4:	MOV	R0,#33H
	CJNE	@R0,#9,LOOP3
	DEC	R0
	CJNE	@R0,#9,LOOP2
	DEC	R0
	CJNE	@R0,#9,LOOP1

	MOV	31H,#0		;Reset Digito 1
	MOV	32H,#0		;Reset Digito 2
	MOV	33H,#0		;Reset Digito 3
	INC	34H		;Incrementa Digito 4

	SJMP	LOOP

; ~~~~ Verifica se o numero eh XX99 ~~~~
LOOP3:	MOV	R0,#32H
	CJNE	@R0,#9,LOOP2
	DEC	R0
	CJNE	@R0,#9,LOOP1

	MOV	31H,#0		;Reset Digito 1
	MOV	32H,#0		;Reset Digito 2
	INC	33H		;Incrementa Digito 3
	
	SJMP	LOOP

; ~~~~ Verifica se o numero eh XXX9 ~~~~
LOOP2:	MOV	R0,#31H
	CJNE	@R0,#9, LOOP1
	
	MOV	31H,#0		;Reset digito 1
	INC	32H		;Incrementa digito 2
	
	SJMP	LOOP

; ~~~~ Incrementa ultimo Digito ~~~~
LOOP1:	INC	31H
	SJMP	LOOP

;-------------- Rotinas ----------------------------------------------
; ~~~~ Reseta todos os digitos ~~~~
RESET:
	MOV	31H,#0
	MOV	32H,#0
	MOV	33H,#0
	MOV	34H,#0
	RET

; ~~~~ Mostra o numero, um digito por vez ~~~~
DISPLAY:
	MOV	P0,#0		;Apaga Display
	MOV	R7,#1
BUF:	MOV	A,@R1		;Digito atual
	MOVC	A,@A+DPTR	;Pega o Digito D7S correspondente
	ACALL 	MOSTRA

	INC	R1		;Incrementa o ponteiro
	CJNE	R1,#35H,BUF	;Loop enquanto nao mostrar os 4 digitos

	MOV	P0,#0		;Desativa todos os displays
	MOV	R1,#31H		;Reset ponteiro para digitos
	MOV	P2,#0		;Apaga o digito salvo

	RET

; ~~~~ Mostra um digito ~~~~
MOSTRA:
	MOV	P2,A		;Envia o digito para displays
	MOV	A,R7		;Pega o valor do display ativo
	MOV	P0,A		;Ativa um display especifico
	
	RL	A		;Altera para que o proximo display seja ativado
	MOV	R7,A
	
	MOV	P0,#0		;Apaga todos os displays
	RET

;-------------- Dados ----------------------------------------------

DIGITOS:	DB	3FH, 06H, 5Bh, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 6FH

;-------------- END ----------------------------------------------
	END
