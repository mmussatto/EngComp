; Nome: Murilo Mussatto		Nusp: 11234245
;
; Exercicio Aula 9 - 8 Displays Multiplexados
;
;
;	Endereco 30h - 37h --> Buffer que guarda os digitos
;
;	R0 --> ponteiro para o buffer
;	R1 --> digito menos significativo da conversao de hexa para decimal
;	R2 --> digito mais significativo da conversao de hexa para decimal
;	R4 --> controla qual display esta ativo
;
;	Os 8 Displays estao conectados na porta P1 juntamente com a memoria externa
;	utilizando a configuracao mostrada em aula
;
;	A ativacao dos displays eh feita pela porta P2
;
;	Memoria Externa:
;	  (1000)h --> 2 displays Menos Significativos
;	  (2000)h --> 2 displays seguintes
;	  (3000)h --> próximos 2 displays
;	  (4000)h --> 2 displays Mais Significativos
;
;
;	Escrita dos displays: endercos superiores a 8000h
;
;	Interrupcao Externa 1 --> interrompe o loop do programa
;
;	A tabela para conversao dos digitos decimais para BCD foi a mesma
;	utilizada na simulacao 8
;
;
;-------------- Jumps ---------------------------------------------------------------
    ORG     	0
    SJMP    	PROG
;************************************
    ORG		0013h
    SJMP	EXT1
;************************************

;-------------- Interrupcoes --------------------------------------------------------
;**** Externa 1 ******
EXT1:
	CPL	20H.0		;Complementa Bit de Contagem
	RETI
;-------------- Programa -----------------------------------------------------------
PROG:
	SETB 	EA		;Habilita Interrupcoes
	SETB 	EX1		;Habilita Interrupcao Externa 1
	SETB 	IT1		;Habilita Descidada de Borda para EX1

	ACALL	PRESET		;Carrega numeros na memoria externa
	ACALL	APAGA		;Apaga todos os displays e o digito salvo

	MOV	R0,#2Fh		;Um endereco a menos que o Buffer -- eh incrementando na rotina LE

	SETB	20H.0		;Comeca a contagem

LOOP:	JNB	20H.0, $	;Trava o programa caso contagem esteja desabilitada


; ~~~~ Leitura de Digitos e Construcao do Buffer ~~~~
	MOV	DPTR,#1000h	;Le os dois primeiros Digitos
	ACALL	LE

	MOV	DPTR,#2000h	;Le os proximos dois digitos
	ACALL 	LE

	MOV	DPTR,#3000h	;Le os proximos dois digitos
	ACALL 	LE

	MOV	DPTR,#4000h	;Le os dois ultimos digitos
	ACALL 	LE

; ~~~~ Mostra numero nos displays ~~~~
	ACALL 	DMUX
	
	SJMP	LOOP


;-------------- Funcoes ---------------------------------------------------------


DMUX:	MOV	DPTR,#8000h	;Posicao 8000h da memoria externa, manda digito para displays
	MOV	R0,#30h		;Ponteiro para o Buffer
	MOV	R4,#01		;Seleciona o display ativo

CONT:	ACALL	APAGA
	MOV	A,@R0		;Carrega o byte no acumulador
	MOVX	@DPTR,A		;Envia byte para displays
	XCH	A,R4		;Recupera o valor do display ativo
	MOV	P2,A
	RL	A		;Rotaciona o display ativo
	XCH	A,R4		;Quarda o valor do display ativo
	INC	R0		;Incrementa o ponteiro

	CJNE	R0,#38h,DIGIT	;Loop enquanto nao percorre todos os displays
DIGIT:	JC	CONT

	ACALL	APAGA
	RET

; ~~~~ Apaga todos os displays e o digito salvo ~~~~
APAGA:	MOV	A,#00
	MOVX	@DPTR,A	;apaga display
	MOV	P2,#00
	RET


; ~~~~ Carrega o numero 22486710 nos enderecos da memoria externa ~~~~
PRESET:
	MOV	DPTR,#1000h
	MOV	A, #0Ah		; 10
	MOVX	@DPTR, A

	MOV	DPTR,#2000h
	MOV	A, #43h		;67
	MOVX	@DPTR, A

	MOV	DPTR,#3000h
	MOV	A, #30h		;48
	MOVX	@DPTR, A

	MOV	DPTR,#4000h
	MOV	A, #16h		;22
	MOVX	@DPTR, A
	RET


; ~~~~ Le o digito hexadecimal da memoria externa, converte e adiciona no buffer ~~~~
LE:
	MOVX	A,@DPTR		;Le hexadecimal da memoria externa
	ACALL	CONVERT_HEX	;converte para decimal R1 -> menos significativo, R2 -> mais significativo

	MOV	A,R1
	ACALL	CONVERT_BCD	;converte menos significativo para BCD usando a tabela
	INC	R0
	MOV	@R0, A		;Salva no Buffer

	MOV	A,R2
	ACALL CONVERT_BCD	;converte mais significativo para BCD usando a tabela
	INC 	R0
	MOV	@R0, A		;Salva no Buffer
	RET

; ~~~~ Converte o numero hexa para decimal ~~~~
CONVERT_HEX:
	MOV   B,#10
	DIV   AB	;Divide hexadecimal por 10
	MOV   R2,A   	;Digito Mais Significativo
     	MOV   R1,B   	;Digito Menos Sigificativo
	RET

; ~~~~ Converte o numero decimal para o valor BCD correspondente ~~~~
CONVERT_BCD:
	MOV 	DPTR,#DIGITOS	;Ponteiro para tabela de Digitos
	MOVC	A, @A+DPTR
	RET

;-------------- Dados ----------------------------------------------

DIGITOS:	DB	3FH, 06H, 5Bh, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 6FH

;-------------- END ----------------------------------------------
	END