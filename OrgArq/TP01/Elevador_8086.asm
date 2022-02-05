;                                     
;Organizacao e Arquitetura de Computadores
; TP01 - Prog.8086 - Elevador
;
;
;Nome: Murilo Mussatto  NUSP: 11234245
;
; 
;
;Funcionamento:
;
;   Somente as teclas  a seguir podem ser utilizadas na execucao do programa.
;   Qualquer tecla diferente das mostradas abaixo sera ignorada.
;
;   1, 2, 3, 4, 5, 6, 7, 8, a, b, c, d, e, f, g, h, p, P, s, S, x
;      
;
;   As teclas de 1 ate 8 movem o elevador para o andar correspondente
;   As teclas de 'a' ate 'h' representam respectivamente o andar 1, 2, 3, ... , 8
;   O elevador possui uma logica simples e atendende apenas uma chamada de cada vez.  
;
;   O usuario pode apertar mais teclas, elas ficaram no buffer do I/O e serao lidas conforme
;   a necessidade. Porem, como especificado, o elevador atendera as requisicoes na ordem em
;   em que foram dadas.
;
;   Pressionando a tecla 'p' a qualquer momento, o programa para.
;   O programa eh retomado pressionando a tecla 'P'.
;   Nenhuma tecla pressionada enquanto o sistema esta parado eh armazenada. 
;
;   Pressionando a tecla 'x' a qualquer momento, o progama sera resetado e
;   o elevador voltara para o primeiro andar.
;   Nao eh necessario apertar nenhuma tecla para "voltar a luz"      
;
;   Caso o elevador fique parado por muito tempo em um andar, ele fechara a porta e
;   voltara automaticamente para o primeiro andar 
;
;   Enquanto a porta esta fechando, o usuario pode digitar a tecla s para
;   indicar que a porta esta obstruida. Caso isso ocorra, a porta sera aberta
;   e a tecla 'S' deve ser pressionada para indicar que a porta nao esta mais obstruida.
;   Nenhuma tecla pressionada enquanto o sistema esta parado eh armazenada.


org 100h  

        
top:    CALL cls
        CALL andarAtual ;mostra o andar atual
        CALL fechaPorta ;mostra que a porta esta fechada
        CALL requisicoes 
        CALL espera1           
                   
inicio: MOV bx, cont
        CMP bx, pvet    ;verifica se ja leu todas as requisicoes
        JNE start
        
        CMP bx, 0       ;verifica se o contador esta em zero
        JNE f5          ;se nao, limpa o vetor
        
        LEA bp, timer   ;endereco timer -> bp
        INC [bp]        ;incrementa timer
        CMP [bp], 40    ;se timer == 40, pula pra f3
        JE f3
        CMP [bp], 80    ;se timer == 80, pula pra f4
        JE f4
       
        MOV ah, 01h     ;verifica se tem alguma tecla no buffer
        INT 16h
        JE inicio       ;equal -> ZF = 1 -> nao tem tecla
               
        
start:  CALL check1     ;verifica se foi 'p' ou 'x' e adiciona no vetor de chamadas        
        
        CMP tem_req, 0
        JE inicio              
        
        CALL requisicoes
                      
        MOV bx, cont   
        MOV al, vet[bx]
        INC cont

        MOV ah, 00      ; |   Isola o andar        |  Divide o numero 
        MOV bl, 10h     ; |>  desejado pelo        |>  por 16 e
        DIV bl          ; |   codigo do caractere  |   pega o resto
        
        LEA di, andar   ;coloca andar atual em di  
        CMP ah, [di]    ;compara com o andar desejado
        JA f1           ;andar desejado esta acima do elevador
        JB f2           ;andar desejado esta abaixo do elevador


        
;f1 - subir        
f1:     MOV [bp], 0     ;zera o timer
        
        CALL subir      ;funcao de subir
        CALL cls        ;limpa o console
        CALL andarAtual ;mostra andar atual
        JMP inicio 
           
;f2 - descer            
f2:     MOV [bp], 0     ;zera o timer
       
        CALL descer     ;funcao de descer
        CALL cls        ;limpa o console
        CALL andarAtual ;mostra andar atual
        JMP inicio  

;f3 - fecha a porta         
f3:     CMP porta, 0    ;verifica se a porta ja esta fechada
        JE inicio
        CALL fechaPorta ;fecha a porta apos certo tempo
        JMP inicio
                    
;f4 - volta elevador para andar 1         
f4:     MOV [bp], 0     ;zera o timer
        LEA di, andar   
        CMP [di], 1     ;verifica se ja esta no andar
        JE inicio       ;se sim, sai da funcao 
        MOV bl, 1       
        CALL descer     ;se nao, desce ate o andar 1
        JMP top                                         
        
;f5 - limpa vetor de requisicoes e recomeca as operacoes
f5:     CALL cls_vet
        JMP  inicio
                 
RET 


        
;---------- Print --------------------------

;mostra mensagem armazenada no enderco do si        
mostra PROC             ;printa na tela
        
        
        MOV dx, newl    ;nova linha
        MOV ah, 9
        INT 21h
                        
        MOV dx, si      ;coloca endereco da msg desejado em dx
        INT 21h 
        
        MoV dx, newl    ;nova linha
        INT 21h 
        
        RET 

mostra ENDP  


;mostra vetor de requisicoes
requisicoes PROC
     
            MOV ah,9
            MOV dx, newl    ;nova linha
            INT 21h
            
            LEA si, msg13   ;msg13 (requisicoes)
            MOV dx, si
            INT 21h
            
            CMP pvet, 0
            JE fim_req
            
            MOV bx, cont    ;contador -> bx
   
loop_req:   MOV dl, vet[bx] ;elemento do vetor com indice bx
        
            MOV ah, 2
            INT 21h 
            
            MOV dl,','      ;printa espaco com virgula
            INT 21h
            MOV dl,' '
            INT 21h
            
            INC bx          ;aumenta o "contador" sem mexer na variavel
             
            CMP bx, pvet    ;verifica se ja printou o vetor inteiro
            JNE loop_req 
            
            MOV ah, 9
            MOV dx, newl    ;nova linha
            INT 21h       
        
fim_req:    RET
            
requisicoes ENDP

;---------- Subir -------------------------        
        
subir PROC 
            LEA di, andar    ;andar atual -> di 
            MOV andar_d, ah
            MOV bl,andar_d   ;andar desejado -> bl  
               
            CMP porta, 0     ;verifica se a porta esta fechada
            JNE fPorta_s     ;se nao, fecha porta
            
volta_s1:   CALL check1      ;verifica se houve parada
            CMP bl, [di]     ;compara andar desejado com andar atual
            JA sobe          ;andar desejado esta acima
                
        
volta_s2:   CALL abrePorta   ;abre a porta
            JMP fim_s        ;fim da rotina
        
    
sobe:       CMP [di], 1      ;verifica se esta no andar 1
            JE  rBase        ;reseta base pois vai subir
            
volta_s3:   CMP [di], 8      ;verifica se esta no topo
            JE  sTopo        ;set flag topo

            INC [di]         ;andar atual ++
            LEA si, msg1     ;endereco da msg1 -> si
            CALL mostra      ;printa na tela
            CALL espera1     ;delay
            JMP volta_s1
                     
    
sTopo:      CALL setTopo     ;set Topo
            JMP volta_s2
            
rBase:      CALL resetBase   ;reset Base
            JMP volta_s3   
            
fPorta_s:   CALL fechaPorta  ;fecha porta
            JMP volta_s1                     
          
fim_s:      RET
subir ENDP      
             
             
;---------- Descer --------------------------    

descer PROC
            LEA di, andar     ;andar atual -> di
            MOV andar_d, ah                   
            MOV bl, andar_d   ;andar desejado -> bl
            
            CMP porta, 0      ;verifica se a porta esta fechada
            JNE fPorta_d      ;se nao, fecha porta
            
            
volta_d1:   CALL check1
            CMP bl, [di]      ;compara andar desejado e atual 
            JB desce          ;andar desejado esta abaixo
        
            
        
volta_d2:   CALL abrePorta    ;abre a porta
            JMP fim_d         ;fim da rotina
        
    
desce:      CMP [di], 8       ;verifica se esta no andar 8
            JE rTopo          ;reseta topo pois vai descer
            
volta_d3:   CMP [di], 1       ;verifica se esta no terreo
            JE  sBase         ;set flag base

            dec [di]          ;andar atual --
            LEA si, msg2      ;endereco msg2 -> si
            CALL mostra       ;printa na teka
            CALL espera1      ;delay
            JMP volta_d1         
 
    
sBase:      CALL setBase      ;set Base
            JMP volta_d2
            
rTopo:      CALL resetTopo    ;reset Topo
            JMP volta_d3     

fPorta_d:   CALL fechaPorta   ;fecha porta
            JMP volta_d1                  
          
fim_d:      RET
descer ENDP 

    
;---------- Porta ----------------------------

;abre porta
abrePorta PROC
    
    
    LEA si, msg9    ;printa a msg9 (Porta Abrindo)
    CALL mostra 
    
    CALL espera2    ;delay
    CALL espera2    ;delay
    CALL espera2    ;delay 
    
    
    LEA si, msg3    ;printa msg3 (Porta Aberta)
    CALL mostra
    
    MOV porta, 1    ;set porta aberta
    CALL espera2    ;delay 
    
    RET  
    
abrePorta ENDP    
  
  
;fecha porta    
fechaPorta PROC
    
                CMP porta, 0    ;verifica se a porta ja esta fechada
                JE  fechada     ;se sim, mostra msg4
                
                
fechando:       MOV foi_obs, 0  ;reset foi_obs
                LEA si, msg10   ;printa a msg10 (Porta Fechando)
                CALL mostra
                  
                CALL espera2    ;delay
                CALL espera2    ;delay
                CALL espera2    ;delay
                
                CALL check2     ;verifica porta obstruida
                CMP foi_obs, 1  ;verifica se a porta foi obstruida
                JE fechando
                 
    
fechada:        LEA si, msg4    ;printa a msg4 (Porta Fehcada)
                CALL mostra 
                    
                MOV porta, 0    ;set porta fechada 
                CALL espera2    ;delay
                RET  
    
fechaPorta ENDP
                
  
;obstrucao da porta                
portaObs PROC
        
        MOV pporta, 1   ;set porta obstruida 
        MOV foi_obs, 1  ;set foi obstruida
        
        LEA si, msg11   ;printa a msg11 (Porta Obstruida)
        CALL mostra
        
        CALL abrePorta 
    
loop_obs:   MOV ah,7    ;le do teclado
            int 21h
    
        CMP al, 'S'     ;checa se a tecla foi 'S'
        JNE loop_obs    ;jump se a tecla nao era 'S'
                                                    
        MOV pporta, 0   ;reset porta obstruida
                                                    
        LEA si, msg12   ;printa msg12 (Porta Liberada)
        CALL mostra          
                  
        RET  

portaObs ENDP                    
               
;---------- Andar Atual ----------------------------               
               
andarAtual PROC 
    
    LEA di, andar     ;andar atual -> di
    MOV al, 30h       ;adiciona 30h ao andar atual para
    add al, [di]      ; transformar em caracter
    MOV msg5[14], al  ;altera o caracter do andar na msg5
    
    LEA si, msg5      ;printa o andar atual
    CALL mostra
    RET  
     
andarAtual ENDP 


;---------- Topo -----------------------------
            
setTopo PROC
        
   MOV topo, 1   ;seta a flag topo com 1
   RET
        
setTopo ENDP


resetTopo PROC
    
   MOV topo, 0   ;reseta a flag topo com 0
   RET 
    
resetTopo ENDP


;---------- Base -----------------------------

setBase PROC
    
    MOV base, 1  ;seta flag base com 1
    RET
      
setBase ENDP 
         
         
resetBase PROC
    
    MOV base, 0  ;seta flag base com 0
    RET
      
resetBase ENDP 
            
            
;-------- Checagem -----------------------------
   
check1 PROC
    
j_check1:   MOV ah, 01h     ;verifica se tem alguma tecla no buffer
            int 16h
            JE fim_c1       ;equal -> ZF = 1 -> nao tem tecla
            
            CMP al, 'p'     ;compara para ver se era o 'p'  
            JE setParada    ;para o programa     
            
            CMP al, 'x'     ;compara para ver se era o 'p'
            JE setReset     ;reseta o programa  
            
            MOV ah,7        ;le o caractere do buffer
            INT 21h
            
            CMP al, 31h      ;verifica se eh caracter menor que 1 (30h)
            JB j_check1
            
            CMP al, 68h      ;verifica se eh caracter maior que h (68h) 
            JA j_check1
            
            CMP al, 38h      ;verifica se esta entre 8 (38h) e a (61h)
            JA invalido
             
            
inclui:     MOV bx, pvet    ;inclui o valor lido no vetor de requisicoes
            MOV vet[bx], al
            INC pvet        
            MOV tem_req, 1  ;set tem_req
            JMP j_check1    ;recomeca o loop
           
            
fim_c1: RET

              
invalido:   CMP al, 61h 
            JB j_check1
            JMP inclui


setReset: CALL reset
          RET
    
setParada: CALL parada
           RET
               
check1 ENDP


check2 PROC 
    
    MOV ah, 01h     ;verifica se tem alguma tecla no buffer
    int 16h
    JE fim_c2       ;equal -> ZF = 1 -> nao tem tecla
    
    CMP al, 's'     ;compara para ver se era o 's'  
    JE setPortaObs  ;para o programa     
    
    
fim_c2: RET   

setPortaObs: CALL portaObs 
             RET

check2 ENDP    
   
;-------- Parada -------------------------------
   
parada PROC
             
        LEA si, msg6  ;printa a msg6 (Parada)
        CALL mostra 
    
loop_p: MOV ah,7      ;le do teclado
        int 21h
    
        CMP al, 'P'   ;checa se a tecla foi 'P'
        JNE loop_p    ;jump se a tecla nao era 'P'
                  
        LEA si, msg7  ;printa msg7 (retomada)
        CALL mostra          
                  
        RET
    
parada ENDP                                         


;------- Reset ------------------------------------

reset PROC 
    
    CALL cls 
                        ;limpa o buffer do console
    MOV ah, 0Ch
    MOV al, 0
    INT 21h
    
    LEA si, msg8        ;mostra mensagem de reset
    CALL mostra
    
    MOV msg5[14], '?'   ; altera o caracter do andar na msg5 
    LEA si, msg5
    CALL mostra 
    
    CALL cls_vet        ;limpa o vetor de requisisoes
    
    CMP [di], 1         ;verifica se esta no andar 1
    JE fim_r
    
    MOV ah, 1           ;se nao, desce ate o andar 1
    CALL descer          


fim_r: JMP top          ;volta para o incio do programa   
          
reset ENDP    


   
;--------- Timer -------------------------------------   

;essas funcoes sao timers de delay. 
;a primeira eh mais rapida enquanto a segunda demora mais
;a primeira eh usada para subir ou descer
;a segunda eh usada para abir e fechar porta

espera1 PROC
    
    MOV     CX, 05h
    MOV     DX, 000Fh
    MOV     AH, 86h
    INT     15H 
    RET

espera1 ENDP 

espera2 PROC
    
    MOV     CX, 07h
    MOV     DX, 000Fh
    MOV     AH, 86h
    INT     15H 
    RET

espera2 ENDP


;--------- Cls --------------------------------------
  
;limpa a tela do console  
cls PROC  
    
    mov ah,0
    mov al,03h
    int 10h
    ret
    
cls ENDP   

  
;limpa o vetor de requisicoes  
cls_vet PROC 
        
lp_clsv:    MOV bx, pvet        ;pvet -> bx       
   
            MOV vet[bx], 90h    ;reseta a posicao bx do vetor
        
        
            CMP pvet, 0         ;se pvet = 0, ja limpou tudo e continua
            JNE dec_pvet        ;se nao, decrementa o pvet

            MOV cont, 0         ;reseta o contador
            MOV tem_req, 0      ;reseta tem requisicao
        
            RET 
        
dec_pvet:   DEC pvet            ;decrementa o pvet
            JMP lp_clsv         ;volta para o loop
                
cls_vet ENDP


;---------- Dados -------------------------     

andar   db 1 ;1->1andar, 2->2andar, ...
andar_d db 0 ;indica andar desejado
base    db 1 ;0->falso,   1->esta no terreo
topo    db 0 ;0->falso,   1->esta no 7andar
porta   db 0 ;0->fechada, 1->aberta
pporta  db 0 ;0->livre,   1->bloqueada
foi_obs db 0 ;0->nao foi obstruida  1->foi obstruida
timer   db 0 
tem_req db 0 ;0->nao tem chamada, 1-> tem chamada

msg1:   db ' Subindo... $'
msg2:   db ' Descendo... $'
msg3:   db ' Porta aberta $'
msg4:   db ' Porta fechada $'
msg5:   db ' Andar atual: ? $'
msg6:   db ' Elevador Parado! $'
msg7:   db ' Retomando Operacao! $' 
msg8:   db ' SEM ENERGIA! Resetando o Elevador... $'
msg9:   db ' Porta Abrindo... $'
msg10:  db ' Porta Fechando... $'  
msg11:  db ' Porta Obstruida! $'
msg12:  db ' Porta Liberada! $'
msg13:  db ' Requisicoes: $'
newl:   db 0Dh, 0Ah, '$'
      
cont    dw 0000 ;contador
pvet    dw 0000 ;ponteiro marca o indice da ultima requisicao           
vet     db 0    ;vetor de requisicoes