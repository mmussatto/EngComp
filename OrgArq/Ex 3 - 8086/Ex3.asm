;name "Ex3"

;Nesse exercicio, os seguintes registradores 
;sao usados para as seguintes funcoes:

;SI -> endereco do Vetor1
;BP -> endereco do Vetor2
;DI -> endereco do VetorM
;CX -> tamanho dos vetores
;DH -> numero de vezes que Vetor1 ganahou
;DL -> numero de vezes que o Vetor2 ganahou


org 100h          

jmp start

Vetor1  db  10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 0
Vetor2  db  15, 5, 35, 45, 55, 25, 35, 85, 95, 1, 0  
qtdeV1  db  00
qtdeV2  db  00  
    
    
start:  lea si, Vetor1 ;load adress of Vetor1 
        lea bp, Vetor2 ;load adress of Vetor2 
        lea di, VetorM ;load adress of VectorM
        mov cx, 0      ;reset the counter 

size:   mov bh, [si]  ;conta o tamanho do vetor
        cmp bh, 0
        je continue   ;quando le um 0 (ultimo caracter) continua o codigo
        inc cx
        inc si
        jmp size
          
          
continue:
        lea si, Vetor1 ;load adress of Vetor1    
        mov dx, 0000h

comp:   mov ah, [si]
        mov al, [bp]
        cmp ah, al
        ja adcmaiorV1
        jmp adcmaiorV2

return: inc si
        inc bp
        loop comp    ;enquando o reg Cx nao chegar a 0, continua no loop  
        jmp ganhador ;quando acabar, pula para deceidir o ganahador       
        

adcmaiorV1: mov [di], ah 
            inc dh
            inc di 
            jmp return

adcmaiorV2: mov [di], al
            inc dl
            inc di
            jmp return

msg1 db "Vetor1 ganhou a disputa",0
msg2 db "Vetor2 ganhou a disputa",0

ganhador:   lea di, qtdeV1
            mov [di], dh
            lea di, qtdeV2 
            mov [di], dl
            cmp dh, dl
            mov bx, 0  
            ja ganhador1
            jmp ganhador2
            
ganhador1:  mov al, msg1[bx] ;Vetor1 ganhou, reg Bx percorre os caracteres da msg1
            cmp al, 0        ;o byte depois da msg1 eh zero
            je fim
            
            mov ah, 0eh      ;printa os caracteres na tela
            int 10h
            inc bl
            jmp ganhador1


ganhador2:  mov al, msg2[bx] ;Vetor2 ganhou reg Bx percorre os caracteres da msg2
            cmp al, 0        ;o byte depois da msg2 eh zero
            je fim
            
            mov ah, 0eh      ;printa os caracteres na tela
            int 10h
            inc bl
            jmp ganhador2 
            
           

fim: RET   
    

VetorM db   00 

