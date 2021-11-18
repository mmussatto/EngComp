; Nome: Murilo Mussatto	Nusp: 11234245
; Ex Aula 4 - Ondas quadradas com timer
;
;	  Esperou-se o sistema estabilizar para
;	avaliar o tempo de cada onda.
;
;		P1.0			P1.1
;	Righ = 86-48 = 38us	Righ = 67-29 = 38us
;	Low = 124-86 = 38us 	Low = 105-67 = 38us
;
;	Periodo = 38us		Periodo = 38us
;
;	Defasagem entre as ondas: 86-67 = 19us


    ORG     0
    SJMP    Prog
;************************************
    ORG    000BH
    SJMP    Sub0
;************************************
    ORG    001BH
    SJMP    Sub1
;************************************
Prog:    CLR    P1.0
    CLR    P1.1
    SETB    ET1
    SETB    ET0
    MOV    TMOD, #11h
    MOV    TH1, #0FFh
    MOV    TL1, #0FEh
    MOV    TH0, #0FFh
    MOV    TL0, #0FDh
    SETB    EA
    SETB    TR1
    SETB    TR0
    SJMP    $
;************************************
Sub0:
    CLR     EA
    CPL    P1.0
    CLR    TR1
    CLR    TR0
    MOV    TH0, #0FFh
    MOV    TL0, #0FDh
    SETB    EA
    SETB    TR1
    SETB    TR0
    RETI
;************************************
Sub1:
    CLR    EA
    CPL    P1.1
    CLR    TR1
    CLR    TR0
    MOV    TH1, #0FFh
    MOV    TL1, #0FEh
    SETB    EA
    SETB    TR1
    SETB    TR0
    RETI
;************************************
    END