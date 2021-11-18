;Nome: Murilo Mussatto
;NUSP: 11234245

;	P2.1	P2.7	Estado
;	0	0	Parado
;	0	1	Anti-horario
;	1	0	Horario
;	1	1	Parado		---> Nao vi motivos para usar esse estado
;
; Funcionamento:
;	Os pinos para o sentido horario sao setados e o programa fica esperando uma interrupcao
;	Quando uma interrupcao chega defini-se qual era o sentido da esteira.
;	Como o estado (1,1) nao foi utilizado, foi possivel verificar apenas o pino P2.1
;	Coloca-se a esteira no estado 'Parado' e espera-se o delay apropriado
;	Coloca-se entao a esteira no sentido contrario ao que estava e o programa volta a esperar uma interrupcao
; 	Os estados da esteira podem ser verificados utilizando LEDs ou Chaves


;---- Programa -----------------------
	ORG 0
	SJMP PROG

	ORG 0003
	SJMP INT_EXT0

;********* Interrupcao Externa ********************
INT_EXT0:
	MOV C, P2.1
	JC INT_HORARIO

	ACALL SET_PARADO
	ACALL DELay10	;Delay de 10 segundos
	ACALL SET_HORARIO
	RETI

INT_HORARIO:
	ACALL SET_PARADO
	ACALL DELAY5	;Delay de 5 segundos
	ACALL SET_ANTIHORARIO
	RETI



;********** Programa *************************
PROG:
	SETB IE.0	;Habilita Interrupcoes
	SETB IE.7	;Habilita Interrupcao Externa no pino INT0

	ACALL SET_HORARIO

	SJMP $		;Programa fica esperando uma interrupcao


;*********** Sub-Rotinas ***********************
SET_HORARIO:
	SETB P2.1	;Sentido Horario
	CLR P2.7
	RET

SET_ANTIHORARIO:
	CLR P2.1	;Sentido Anti-horario
	SETB P2.7
	RET

SET_PARADO:
	CLR P2.1	;Parado
	CLR P2.7
	RET


DELAY5:			;Delay de 5 segundos
	mov R2,#02h
Loop1: 	mov R1,#05h	;  Eh necessario ajustar os valores para obter um atraso de 5s
Loop:	mov R0,#0Fh	;como o simulador fica muito lento, optei por deixar um valor mais baixo
	djnz R0, $	;mas que demonstre o funcionamento do circuito
	djnz R1, Loop
	djnz R2, Loop1
	ret


DELAY10:		;Delay de 10 segundos
	mov R2,#02h
Loop3: 	mov R1,#0Fh	;  Eh necessario ajustar os valores para obter um atraso de 10s
Loop2:	mov R0,#0Fh	;como o simulador fica muito lento, optei por deixar um valor mais baixo
	djnz R0, $	;mas que demonstre o funcionamento do circuito
	djnz R1, Loop2
	djnz R2, Loop3
	ret

;*************** Fim ************************
	END