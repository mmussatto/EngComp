; Nome: Murilo Mussatto		Nusp: 11234245
;
; Lista 1 - Ex 8 - Pares e Impares com Serial
;
;	R0 --> Posicao Atual do Vetor
;	R1 --> Nro Impares
;	R2 --> Nro Pares
;	R3 --> Salva Momentaneamente o Valor Lido
;

;-------------- Jumps -------------------------------------------
    ORG     	0
    SJMP    	PROG
;************************************

;-------------- Programa ----------------------------------------
PROG:
	SETB 	EA		;Habilita Interrupcoes

	MOV	SCON,#40h	;Modo 1 (Variavel 10bits)

	MOV	TMOD,#20h	;Timer1: Software, Timer e Modo 2;

;	Formula para TH1 do Timer:	256 - (K*110592*10^6)/(32*12*BaudRate)
;		Com K = 1 e BaudRate = 4800 --> TH1 = 250
;		Com K = 1 e BaudRate = 9600 --> TH1 = 253
;		Com K = 2 e BaudRate = 9600 --> TH1 = 250
;	 Logo, eh possivel alterar apenas o valor de K (SMOD) e
;	manter o contador com 250

	MOV	TH1,#250	;Timer 1: recarregavel com 250 decimal
	MOV	TL1,#250
	SETB	TR1		;Inicia Timer 1


	MOV	DPTR,#VET	;Endereco do vetor
	MOV	R0,#0FFh	;Indice do Vetor
	MOV	R1,#0		;Quantidade de Nros Impares
	MOV	R2,#0		;Quantidade de Nros Pares


LOOP:	INC	R0		;Incrementa Indice

	CJNE	R0,#10,TEST	;Finaliza se R0 >= 10 (tam vetor)
TEST:	JNC	FIM

	MOV	A,R0		;Le o dado de VET[R0]
	MOVC	A,@A+DPTR
	MOV	R3,A		;Salva dado Lido

	MOV	B,#02
	DIV	AB
	MOV	A,B		;Resto da Divisao por 2

	JNZ	IMPAR		;JMP se for Impar

PAR:	INC	R2		;Incrementa Nro Pares
	MOV	A,R3		;Recupera o Nro Lido
	MOV	P1,A		;Envia para P1
	MOV	PCON,#80h	;K = 2 --> Baud = 9600
	ACALL	ENVIA
	SJMP	LOOP

IMPAR:	INC	R1		;Incrementa Nro Impares
	MOV	A,R3		;Recupera o Nro Lido
	MOV	P2,A		;Envia para P2
	MOV	PCON,#00h	;K = 1 --> Baud = 4800
	ACALL	ENVIA
	SJMP	LOOP


FIM:	MOV	DPTR,#2030h
	MOV	A,R2
	MOVX	@DPTR,A		;Armazena Nro de Pares

	MOV	DPTR,#2031h
	MOV	A,R1
	MOVX	@DPTR,A		;Armazena Nro de Impares

	SJMP	$		;Fim Logico do Programa

ENVIA:
	MOV	SBUF,A
	JNB	TI,$
	CLR	TI
	RET


;-------------- Dados ----------------------------------------------
VET:	DB	22, 255, 100, 48, 97, 128, 64, 45, 56, 10
TAM	EQU	10

;-------------- END ----------------------------------------------
	END