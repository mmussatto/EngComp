#		Organizacao e Arquitetura de Computadores
#	Trabalho Pratico 02 - Programacao MIPS - Elevador
#
#	Nome: Murilo Mussatto
#	NUSP: 11234245
#
#
#	Vetores de Requisicao:
#		Sao vetores de 9 posicoes onde cada posicao, a partir do indice 1 respresenta um andar do predio. Quando esta alocado o valor 0, significa que nao ha 
#	requisicoes para aquele andar. Caso haja requisicoes, o valor armazenado sera 1. O valor -1 eh armazenado na posicao zero para facilitar a visualicao dos 
#	vetores na memoria.
#	
#	Leitura:
#		Quando uma tecla tiver sido lida, a funcao "read" sera chamada. Essa funcao compara o caractere lido com varias possibilidade e atribui um valor 
#	de 1 a 8 para o registrado $a0, dependendo do andar relacionado a requisocao designada pelo caractere. Em seguida, a funcao escolhe o vetor de requisicoes
#	apropriado e calcula o indice correto para o valor armazenado em $a0. Por fim, a funcao guarda o valor 1 na posicao calculada para o vetor escolhido, indicando que
#	que ha uma requisicao. 
#	Exemplo: o caractere 'w' foi lido, a funcao read eh chamada e atribui o valor 2 para o registrado $a0, pois esse eh o andar designado pelo caracter. Em seguida, como
#	a letra 'w' define um requisicao interna do E1, o vetor req_E1 eh escolhido. Entao, eh calculado o endereco de req_E1[2] e atribuido a ele o valor 1. 
#
#	Funcao Atribui: seve para escolher um dos elevadores para atender uma chamada externa
#
#	Registradores Salvos:
#	$s0 - vetor de requisicoes externas
# 	$s1 - vetor de requisicoes E1
# 	$s2 - vetor de requisicoes E2
#	$s3 - andar atual E1
#	$s4  - andar atual E2
#	$s5 - ponteiro do arquivo log
#	$s7 - char lido do MIMO


.data
	temp:	.word 0

	andarE1: 	.word 1		#1 - primeiro andar; 2 - segundo andar; ....
	andarE2:	.word 1		#1 - primeiro andar; 2 - segundo andar; ....
	
	andar_dE1:	.word 0		#andar de destino
	andar_dE2:	.word 0		#andar de destino
	
	portaE1:	.word 0		#0 - fechada; 1- aberta
	portaE2:	.word 0		#0 - fechada; 1- aberta
	
	estadoE1:	.word 0		#-1 - parado; 0 - nao se movendo; 1 - subindo; 2 - desccendo
	estadoE2:	.word 0		#-1 - parado; 0 - nao se movendo; 1 - subindo; 2 - desccendo
	
	baseE1:		.word 1		#0 - falso; 1 - verdadeiro
	baseE2:		.word 1		#0 - falso; 1 - verdadeiro
	
	topoE1:		.word 0		#0 - falso; 1 - verdadeiro
	topoE2:		.word 0		#0 - falso; 1 - verdadeiro
	
	#Vetores de Requisicao
	req_ext:		.word -1, 0, 0, 0, 0, 0, 0, 0, 0	
	req_E1:		.word -1, 0, 0, 0, 0, 0, 0, 0, 0
	req_E2:		.word -1, 0, 0, 0, 0, 0, 0, 0, 0
	
	msg1:	.asciiz "  Subindo para o andar: "
	msg2:	.asciiz "  Descendo para o andar: "
	msg3:	.asciiz "  Porta esta aberta\n"
	msg4: 	.asciiz "  Porta esta fechada\n"
	msg5:	.asciiz "  Andar atual: "
	msg6:	.asciiz "  Elevador esta parado!\n"
	msg7: 	.asciiz "  Retomando Operacoes!\n"
	msg8:	.asciiz "Requisicoes Externas: "
	msg9:	.asciiz "Requisicoes do Elevador E1: "
	msg10:	.asciiz "Requisicoes do Elevador E2: "
	msg11:	.asciiz "Elevador E1:\n"
	msg12:	 .asciiz "Elevaodr E2: \n"
	newl:	.asciiz "\n"
	
	file: 	.asciiz "log.txt"
	mlog1:	.asciiz "E1: ? ? ? ?\n"
	mlog2:	.asciiz "E2: ? ? ? ?\n"
	mlog3:	.asciiz "BE: 0 0 0 0 0 0 0 0\n"
	mlog4:	.asciiz "B1: 0 0 0 0 0 0 0 0\n"
	mlog5:	.asciiz "B2: 0 0 0 0 0 0 0 0\n"
	mlog6:	.asciiz "TC:       \n\n"
	espaco:	.asciiz " "
	
.text 
	.globl main
	
main:

	la $s0, req_ext
	la $s1, req_E1
	la $s2, req_E2
	lw $s3 andarE1
	lw $s4 andarE2
	
	# .............Open Log File
	li   $v0, 13      	 # open file
	la   $a0, file     	# file name
	li   $a1, 1      		# flag for writing 
	#li   $a2, 0        	# mode is ignored
	syscall            	
	move $s5, $v0    	# save the file descriptor
	
	jal log
	jal print_console
	
	key_wait:
	lw      $t0, 0xffff0000
	andi    $t0, $t0, 0x00000001  # Isolate ready bit
	beqz    $t0, main_move
	
	lbu     $a0, 0xffff0004	#read character
	move    $s7, $a0  		# Save Key
	
	la $t0, mlog6	#salva a tecla na mensagem mlog6 - TC:
	sb  $s7, 4($t0)

	jal read

	
main_move:	
	jal movimentacao
	jal atribui	#atribui as requisicoes externas a um elevador
	
main_log:	
	jal print_console
	jal log

	li $v0, 32
	li $a0, 2500
	syscall

	j key_wait
	
##------------- Movimentacao ---------------------------------------------
movimentacao:

#........Elevador E1
	li $a1, 0
	sw $a1, portaE1			#porta fechada
	
	lw $t1, estadoE1
	beq $t1, -1, movimenta_E2	#elevador E1 esta parado

	lw $t1, andar_dE1		#carrega andar de destino de E1
	beqz $t1, aloca_E1
	blt $t1, $s3, desce_E1	#destino menor que andar atual
	bgt $t1, $s3, sobe_E1 	#destino maior que andar atual

chegou_E1:				
	#E1 esta no andar de destino
	sw $zero,  andar_dE1	#nao tem andar de destino
	sw $zero, estadoE1		#esta parado
	li $a1, 1
	sw $a1, portaE1			#porta aberta
		
	sll $t0, $t1, 2		#calcula o endereco de req_E1[$t2]
	add, $t0, $t0, $s1
	li $a1, 0
	sw $a1, 0($t0)		#atribui o valor 0 a posicao correta do vetor, indica que ja atendeu a requisicao
	
	sll $t0, $t1, 2		#calcula o endereco de req_ext[$t2]
	add, $t0, $t0, $s0
	li $a1, 0
	sw $a1, 0($t0)		#atribui o valor 0 a posicao correta do vetor, indica que ja atendeu a requisicao
	
	j movimenta_E2	

aloca_E1:	.
	li $t0, 0	#reseta contador
	move $t3, $t1
	
loop_alocaE1:
	
	add $t0, $t0, 1	#contador++
	bgt $t0, 8, movimenta_E2
	
	#acesa vetor  req_E1 no indice [contador]
	move $t2, $t0	
	sll $t2, $t2, 2	
	add, $t2, $t2, $s1
	lw $t2, 0($t2)
	
	beqz $t2, loop_alocaE1  	#se for zero, nao tem req
	bnez $t3, if_aloca_E1		#multiplas requisicoes
	
	move $t3, $t0	#salva o andar com requisicao
	sw $t3, andar_dE1
	
	j loop_alocaE1

	if_aloca_E1:			#multiplas requisicoes
	subu $t4, $t3, $s3	#req_antiga - andar_E1
	abs $t4, $t4
	
	subu $t5, $t0, $s3 	#req_nova - andar_E1
	abs $t5, $t5
	
	bge $t5, $t4, loop_alocaE1	#requisao nova esta mais longe que antiga
	
	move $t3, $t0	#salva andar com requisicao mais proxima
	sw $t3, andar_dE1	
	
	j loop_alocaE1
			
desce_E1:
	subi $s3, $s3, 1	#andar_atual --
	sw $s3, andarE1
	
	li $t0, 2			#descendo
	sw $t0, estadoE1
	
	beq $t1, $s3, chegou_E1	#chegou no andar de destino
	
	j movimenta_E2
	
				
sobe_E1:
	addi $s3, $s3, 1	#andar_atual ++
	sw $s3, andarE1
	
	li $t0, 1			#subindo
	sw $t0, estadoE1
	
	beq $t1, $s3, chegou_E1	#chegou no andar de destino
	
	j movimenta_E2
							
																					
movimenta_E2:
	li $a1, 0
	sw $a1, portaE2			#porta fechada

	lw $t2, estadoE2
	beq $t2, -1, sai_movimenta
	
	lw $t2, andar_dE2		#carrega andar de destino de E2
	beqz $t2, aloca_E2
	blt $t2, $s4, desce_E2	#destino menor que andar atual
	bgt $t2, $s4, sobe_E2 	#destino maior que andar atual																																																															

chegou_E2:		
	#E2 esta no andar de destino
	sw $zero,  andar_dE2
	sw $zero, estadoE2
	li $a1, 1
	sw $a1, portaE2			#porta aberta
	
	sll $t0, $t2, 2		#calcula o endereco de req_E2[$t2]
	add, $t0, $t0, $s2
	li $a1, 0
	sw $a1, 0($t0)		#atribui o valor 0 a posicao correta do vetor indica que ja atendeu a requisicao
	
	sll $t0, $t2, 2		#calcula o endereco de req_ext[$t2]
	add, $t0, $t0, $s0
	li $a1, 0
	sw $a1, 0($t0)		#atribui o valor 0 a posicao correta do vetor, indica que ja atendeu a requisicao
	
	j sai_movimenta	
	
aloca_E2:
	li $t0, 0	#reseta contador
	move $t3, $t2
	
	loop_alocaE2:
	
	add $t0, $t0, 1	#contador++
	bgt $t0, 8, sai_movimenta
	
	#acesa vetor  req_E2 no indice [contador]
	move $t2, $t0	
	sll $t2, $t2, 2	
	add, $t2, $t2, $s2
	lw $t2, 0($t2)
	
	beqz $t2, loop_alocaE2  	#se for zero, nao tem req
	bnez $t3, if_aloca_E2		#multiplas requisicoes
	
	move $t3, $t0	#salva o andar com requisicao
	sw $t3, andar_dE2
	
	j loop_alocaE2

	if_aloca_E2:			#multiplas requisicoes
	subu $t4, $t3, $s4	#req_antiga - andar_E2
	abs $t4, $t4
	
	subu $t5, $t0, $s4 	#req_nova - andar_E2
	abs $t5, $t5
	
	bge $t5, $t4, loop_alocaE2	#requisao nova esta mais longe que antiga
	
	move $t3, $t0	#salva andar com requisicao mais proxima
	sw $t3, andar_dE2	
	
	j loop_alocaE2
																										
desce_E2:																									
	subi $s4, $s4, 1	#andar_atual --
	sw $s4, andarE2
	
	li $t0, 2			#descendo
	sw $t0, estadoE2
	
	beq $t2, $s4, chegou_E2	#chegou no andar de destino
	
	j sai_movimenta	
																																
sobe_E2:																																																													
	addi $s4, $s4, 1	#andar_atual ++
	sw $s4, andarE2
	
	li $t0, 1			#subindo
	sw $t0, estadoE2
	
	beq $t2, $s4, chegou_E2	#chegou no andar de destino
	
	j sai_movimenta																																																																							
																																																																																					
																																																																																																																																																																																																												
sai_movimenta:																																																																																																																																																																																																																																					
	jr $ra   # Return
##-------------------- Read ---------------------------------------------------	
read:

	# Push: Salva RA
    	subu $sp,$sp,4
    	sw  $ra,0($sp)
    	
    	li $t1, 'p'
    	beq $s7, $t1, exit
    	
    	
    	#Botoes de Parada
    	li $t1, 'z'
    	beq $s7, $t1, paraE1
    	
    	li $t1, 'x'
    	beq $s7, $t1, liberaE1
    	
    	li $t1, 'c'
    	beq $s7, $t1, paraE2
    	
    	li $t1, 'v'
    	beq $s7, $t1, liberaE2
    	
	
	#Requisicoes Externas
	li      $t1,'1'				#compare
	beq     $s7, $t1, read1	#jump 
	
	li      $t1,'2'				#compare
	beq     $s7, $t1, read2	#jump 
	
	li      $t1,'3'				#compare
	beq     $s7, $t1, read3	#jump 
	
	li      $t1,'4'				#compare
	beq     $s7, $t1, read4	#jump 
	
	li      $t1,'5'				#compare
	beq     $s7, $t1, read5	#jump 
	
	li      $t1,'6'				#compare
	beq     $s7, $t1, read6	#jump 
	
	li      $t1,'7'				#compare
	beq     $s7, $t1, read7	#jump 
	
	li      $t1,'8'				#compare
	beq     $s7, $t1, read8	#jump 
	
	#Requisicoes internas do E1
	li      $t1,'q'				#compare
	beq     $s7, $t1, read1E1	#jump 
	
	li      $t1,'w'				#compare
	beq     $s7, $t1, read2E1	#jump 
	
	li      $t1,'e'				#compare
	beq     $s7, $t1, read3E1	#jump 
	
	li      $t1,'r'				#compare
	beq     $s7, $t1, read4E1	#jump 
	
	li      $t1,'t'				#compare
	beq     $s7, $t1, read5E1	#jump 
	
	li      $t1,'y'				#compare
	beq     $s7, $t1, read6E1	#jump 
	
	li      $t1,'u'				#compare
	beq     $s7, $t1, read7E1	#jump 
	
	li      $t1,'i'				#compare
	beq     $s7, $t1, read8E1	#jump
	
	#Requeisicoes internas do E2
	li      $t1,'a'				#compare
	beq     $s7, $t1, read1E2	#jump 
	
	li      $t1,'s'				#compare
	beq     $s7, $t1, read2E2	#jump 
	
	li      $t1,'d'				#compare
	beq     $s7, $t1, read3E2	#jump 
	
	li      $t1,'f'				#compare
	beq     $s7, $t1, read4E2	#jump 
	
	li      $t1,'g'				#compare
	beq     $s7, $t1, read5E2	#jump 
	
	li      $t1,'h'				#compare
	beq     $s7, $t1, read6E2	#jump 
	
	li      $t1,'j'				#compare
	beq     $s7, $t1, read7E2	#jump 
	
	li      $t1,'k'				#compare
	beq     $s7, $t1, read8E2	#jump
	
	j fim_read	#entrada invalida
	
	#Atribuicao de Indices
	read1:
	li $a0, 1		
	j readExt
	
	read2:
	li $a0, 2
	j readExt
	
	read3:
	li $a0, 3
	j readExt
	
	read4:
	li $a0, 4
	j readExt
	
	read5:
	li $a0, 5
	j readExt
	
	read6:
	li $a0, 6
	j readExt
	
	read7:
	li $a0, 7
	j readExt
	
	read8:
	li $a0, 8
	j readExt
	
	read1E1:
	li $a0, 1
	j readE1
	
	read2E1:
	li $a0, 2
	j readE1
	
	read3E1:
	li $a0, 3
	j readE1
	
	read4E1:
	li $a0, 4
	j readE1
	
	read5E1:
	li $a0, 5
	j readE1
	
	read6E1:
	li $a0, 6
	j readE1
	
	read7E1:
	li $a0, 7
	j readE1
	
	read8E1:
	li $a0, 8
	j readE1
	
	read1E2:
	li $a0, 1
	j readE2
	
	read2E2:
	li $a0, 2
	j readE2
	
	read3E2:
	li $a0, 3
	j readE2
	
	read4E2:
	li $a0, 4
	j readE2
	
	read5E2:
	li $a0, 5
	j readE2
	
	read6E2:
	li $a0, 6
	j readE2
	
	read7E2:
	li $a0, 7
	j readE2
	
	read8E2:
	li $a0, 8
	j readE2
	
	#Marcacao das Chamadas nos vetores 
	readExt:
	sll $t0, $a0, 2		#calcula o endereco de req_ext[$a0]
	add, $t0, $t0, $s0
	li $a1, 1
	sw $a1, 0($t0)		#atribui o valor 1 a posicao correta do vetor 
	li $v0, 1				#indica que tem requsicao externa
	jal atribui
	j fim_read
	
	readE1:
	sll $t0, $a0, 2		#calcula o endereco de req_E1[$a0]
	add, $t0, $t0, $s1	
	li $a0, 1
	sw $a0, 0($t0)		#atribui o valor 1 a posicao correta do vetor
	li $v0, 0				#indica que nao tem requsicao externa 
	j fim_read
	
	readE2:
	sll $t0, $a0, 2		#calcula o endereco de req_E2[$a0]
	add, $t0, $t0, $s2	
	li $a0, 1			
	sw $a0, 0($t0)		#atribui o valor 1 a posicao correta do vetor
	li $v0, 0				#indica que nao tem requsicao externa 
	j fim_read
	
	#Atribuicao das Paradas
	paraE1:
	li $t1, -1
	sw $t1, estadoE1 
	j fim_read
	
	paraE2:
	li $t1, -1
	sw $t1, estadoE2 
	j fim_read
	
	liberaE1:
	li $t1, 0
	sw $t1, estadoE1 
	j fim_read
	
	liberaE2:
	li $t1, 0
	sw $t1, estadoE2 
	j fim_read
	
	fim_read:
	# Pop: Recupera RA
    	lw $ra,0($sp)
    	addu $sp,$sp,4 
    	
	jr $ra   # Return
	
## ----------------- Atribuicao das Chamadas ----------------------------	
atribui:

	# Push: Salva RA
    	subu $sp,$sp,4
    	sw  $ra,0($sp)
    	
	li $t0, 0	#reseta contador
	
	loop1:
	
	lw $t5,  andar_dE1
	lw $t6, andar_dE2
	
	add $t0, $t0, 1	#contador++
	bgt $t0, 8, fim_atribui
	
	#acesa vetor  req_ext no indice [contador]
	move $t1, $t0	
	sll $t1, $t1, 2	
	add, $t1, $t1, $s0
	lw $t1, 0($t1)
	
	bne $t1, 1, loop1 	#nao tem requisicao nesse indice
	beq $t0, $t5, loop1	#E1 esta atendendo a chamada
	beq $t0, $t6, loop1	#E2 esta atendendo a chamada
	
			
	tem_req:
	bnez $t5, alocaE2		#E1 ja esta se movendo para algum andar
	bnez $t6, fim_atribui		#E2 tambem ja esta se movendo 
	
	subu $t2, $t0, $s3	#req - andar_E1
	abs $t2, $t2
	
	subu $t3, $t0, $s4	#req - andar_E2
	abs $t3, $t3
	
	ble $t2, $t3, alocaE1	#se E1 esta mais perto, aloca chamada para E1
	
	#E2 esta mais perto
	alocaE2:
	bnez $t6, fim_atribui		
	#move $t4, $t0
	#sll $t4, $t4, 2	
	#add, $t4, $t4, $s2
	#sw $t1, 0($t4)	
	sw $t0, andar_dE2
	j loop1
	
	alocaE1:
	#move $t4, $t0
	#sll $t4, $t4, 2	
	#add, $t4, $t4, $s1
	#sw $t1, 0($t4)
	sw $t0, andar_dE1
	j loop1

	fim_atribui:
	# Pop: Recupera RA
    	lw $ra,0($sp)
    	addu $sp,$sp,4 
    	
	jr $ra   # Return

##------------------- Print -------------------------------------------------
print_console:

	# Push: Salva RA
    	subu $sp,$sp,4
    	sw  $ra,0($sp)

#.........Elevador E1
	la $a0, msg11	#E1:
	jal print 
	
	la $a0, msg5	#Andar atual
	jal print 
	
	li $v0, 1
	lw $a0, andarE1 #Valor andar atual
	syscall
	
	la $a0, newl 	#Nova linha
	jal print 
	
	lw $t0, estadoE1
	ble  $t0, 0, print_E1p	 	#E1 esta parado
	beq $t0, 1, print_E1s		#E1 esta subindo
	
	la $a0, msg2	#E1 esta descendo
	jal print
	
	li $v0, 1
	lw $a0, andar_dE1 #Valor andar destino E1
	syscall
	
	la $a0, newl 	#Nova linha
	jal print
	
	j print_E2
	
print_E1p:	
	la $a0, msg6	#E1 esta parado
	jal print
	j print_E2
	
print_E1s:
	la $a0, msg1	#E1 esta subindo
	jal print
	
	li $v0, 1
	lw $a0, andar_dE1 #Valor andar destino E1
	syscall
	
	la $a0, newl 	#Nova linha
	jal print
	
	j print_E2
	
#..............Elevador E2
print_E2:				
	
	la $a0, msg12	#E2:
	jal print 
	
	la $a0, msg5	#Andar atual
	jal print 
	
	li $v0, 1
	lw $a0, andarE2 #Valor andar atual
	syscall
	
	la $a0, newl 	#Nova linha
	jal print 
	
	lw $t0, estadoE2
	ble  $t0, 0, print_E2p		 #E2 esta parado
	beq $t0, 1, print_E2s		#E2 esta subindo
	
	la $a0, msg2
	jal print
	
	li $v0, 1
	lw $a0, andar_dE2 	#Valor andar destino E2
	syscall
	
	la $a0, newl 	#Nova linha
	jal print
	
	j print_req
	
print_E2p:	
	la $a0, msg6	#E2 esta parado
	jal print
	j print_req
	
print_E2s:
	la $a0, msg1	#E2 esta subindo
	jal print
	
	li $v0, 1
	lw $a0, andar_dE2 #Valor andar destino E2
	syscall
	
	la $a0, newl 	#Nova linha
	jal print
	
	j print_req

#................Requisicoes Externas
print_req:
	la $a0, msg8	#Requisicoes Externas
	jal print
	
	li $t0, 0	#reseta contador
	
loop_print_req:	
	add $t0, $t0, 1	#contador++
	bgt $t0, 8, fim_print_req
	
	#acesa vetor  req_ext no indice [contador]
	move $t1, $t0	
	sll $t1, $t1, 2	
	add, $t1, $t1, $s0
	lw $t1, 0($t1)
	
	li $v0, 1
	move $a0, $t1 	#imprime requisicao
	syscall
	
	la $a0, espaco	#espaco
	jal print
	
	j loop_print_req

fim_print_req:	
	la $a0, newl 	#Nova linha
	jal print

#.......... Requisicoes E1
print_reqE1:
	la $a0, msg9	#Requisicoes do E1
	jal print
	
	li $t0, 0	#reseta contador
	
loop_print_reqE1:	
	add $t0, $t0, 1	#contador++
	bgt $t0, 8, fim_print_reqE1
	
	#acesa vetor  req_ext no indice [contador]
	move $t1, $t0	
	sll $t1, $t1, 2	
	add, $t1, $t1, $s1
	lw $t1, 0($t1)
	
	li $v0, 1
	move $a0, $t1 	#imprime requisicao
	syscall
	
	la $a0, espaco	#espaco
	jal print
	
	j loop_print_reqE1

fim_print_reqE1:	
	la $a0, newl 	#Nova linha
	jal print

#.............Requisicoes E2
print_reqE2:
	la $a0, msg10	#Requisicoes do E2
	jal print
	
	li $t0, 0	#reseta contador
loop_print_reqE2:	
	add $t0, $t0, 1	#contador++
	bgt $t0, 8, fim_print_reqE2
	
	#acesa vetor  req_ext no indice [contador]
	move $t1, $t0	
	sll $t1, $t1, 2	
	add, $t1, $t1, $s2
	lw $t1, 0($t1)
	
	li $v0, 1
	move $a0, $t1 	#imprime requisicao
	syscall
	
	la $a0, espaco	#espaco
	jal print
	
	j loop_print_reqE2

fim_print_reqE2:	
	la $a0, newl 	#Nova linha
	jal print
	
	la $a0, newl 	#Nova linha
	jal print

	# Pop: Recupera RA
    	lw $ra,0($sp)
    	addu $sp,$sp,4 
    
    	jr $ra   # Return

print:
	li $v0, 4	#imprime string passada no $a0
	syscall		
	jr $ra

##------------------ Log File ---------------------------------------------------------------------
log:	
#.........Modificacao dos Vetores de Mensagem
	#E1: ----------------------------------------------
	la $t0, mlog1
	lb $t1, andarE1	#andar atual E1
	add $t1, $t1, '0'	#transforma em char
	sb  $t1, 4($t0)
	
	lb $t1, andar_dE1 #andar destino
	add $t1, $t1, '0'	#transforma em char
	sb $t1, 6($t0)
	
	lb $t1, portaE1 	#situacao porta E1
	beqz $t1, E1pFechada
	
	li $t1, 'A'	#porta Aberta
	j E1p

	E1pFechada:
	li $t1, 'F'	#porta Fechada
	
	E1p:
	sb $t1, 8($t0) #escreve situacao da porta em mlog1 - E1:
	
	lb $t1, estadoE1 	#status do E1
	ble $t1, 0,  E1sParado
	
	li $t1, 'M'	#E1 movendo
	j E1s

	E1sParado:
	li $t1, 'P'	#E1 parado
	
	E1s:
	sb $t1, 10($t0)	#escreve status do elevador em mlog1 - E1:		
	
	#E2	 ------------------------------------
	la $t0, mlog2
	lb $t1, andarE2	#andar atual E2
	add $t1, $t1, '0'	#transforma em char
	sb  $t1, 4($t0)
	
	lb $t1, andar_dE2 #andar destino
	add $t1, $t1, '0'	#transforma em char
	sb $t1, 6($t0)
	
	lb $t1, portaE2 	#situacao porta E2
	beqz $t1, E2pFechada
	
	li $t1, 'A'	#porta Aberta
	j E2p
	
E2pFechada:
	li $t1, 'F'	#porta Fechada
E2p:
	sb $t1, 8($t0) #escreve situacao da porta em mlog1 - E2:
	
	lb $t1, estadoE2 	#status do E2
	ble $t1, 0, E2sParado
	
	li $t1, 'M'	#E2 movendo
	j E2s

E2sParado:
	li $t1, 'P'	#E2 parado
E2s:
	sb $t1, 10($t0)	#escreve status do elevador em mlog2 - E2:		
		
			
					
	#BE -------------------------------------------------------------
	la $t0, mlog3 	#guarda endereco da mlog3 - BE:
	li $t1, 0	#reseta contador
	add $t0, $t0, 2
	
log_BE:
	add $t1, $t1, 1	#contador++

	
	#acesa vetor  req_ext no indice [contador]
	move $t2, $t1	
	sll $t2, $t2, 2	
	add, $t2, $t2, $s0
	lw $t2, 0($t2)
	add $t2, $t2, '0'	#transforma em char
	
	add $t0, $t0, 2	#desloca 2 unidades para o proximo char
	sb $t2, ($t0)		#escreve na mlog3 o valor da chamada do andar <contador>
	
	ble  $t1, 8, log_BE	#percorre todo o vetor de chamadas

	#B1 -------------------------------------------------------------
	la $t0, mlog4 	#guarda endereco da mlog4 - B1:
	li $t1, 0	#reseta contador
	add $t0, $t0, 2
	
log_B1:
	add $t1, $t1, 1	#contador++

	#acesa vetor  req_E1 no indice [contador]
	move $t2, $t1	
	sll $t2, $t2, 2	
	add, $t2, $t2, $s1
	lw $t2, 0($t2)	#guarda o valor de req_E1[contador]
	add $t2, $t2, '0'	#transforma em char
	
	add $t0, $t0, 2	#desloca 2 unidades para o proximo char
	sb $t2, ($t0)		#escreve na mlog3 o valor da chamada do andar <contador>
	
	ble  $t1, 8, log_B1	#percorre todo o vetor de chamadas		
	
	#B2 -------------------------------------------------------------
	la $t0, mlog5 	#guarda endereco da mlog4 - B1:
	li $t1, 0	#reseta contador
	add $t0, $t0, 2
	
log_B2:
	add $t1, $t1, 1	#contador++

	#acesa vetor  req_E2 no indice [contador]
	move $t2, $t1	
	sll $t2, $t2, 2	
	add, $t2, $t2, $s2
	lw $t2, 0($t2)	#guarda o valor de req_E2[contador]
	add $t2, $t2, '0'	#transforma em char
	
	add $t0, $t0, 2	#desloca 2 unidades para o proximo char
	sb $t2, ($t0)		#escreve na mlog3 o valor da chamada do andar <contador>
	
	ble  $t1, 8, log_B2	#percorre todo o vetor de chamadas
	
	
#..........Escrita do Log
	li   $v0, 15       	# system call for write to file
	move $a0, $s5     # file descriptor 
	la   $a1, mlog1    	#msg 1 - E1:
	li   $a2, 12      	# hardcoded buffer length (Tam)
	syscall            
	
	li   $v0, 15       	
	move $a0, $s5     
	la   $a1, mlog2    	# msg 2  - E2:
	li   $a2, 12    		
	syscall   
	
	li   $v0, 15       	
	move $a0, $s5     
	la   $a1, mlog3    	# amsg 3 - BE:
	li   $a2, 20     	
	syscall   
	
	li   $v0, 15       	
	move $a0, $s5     
	la   $a1, mlog4    	#msg 4 - B1:
	li   $a2, 20      	
	syscall   
	
	li   $v0, 15       	
	move $a0, $s5     
	la   $a1, mlog5    	# msg 5 - B2:
	li   $a2, 20      	
	syscall   
	
	li   $v0, 15       	
	move $a0, $s5    
	la   $a1, mlog6    	#mdg 6 - TC:
	li   $a2, 12      		
	syscall   
	
	la $t0, mlog6	#salva a tecla na mensagem mlog6 - TC:
	li $t1, ' '
	sb  $t1, 4($t0)
	
			
#.....	Return
	jr $ra   # Return
	
## ------------------------ Exit -----------------------------------------------------	
exit:
	jal log

#.......Fecha Arquivo
	li   $v0, 16       	# close file
	move $a0, $s6    	# file descriptor 
	syscall
	
	li $v0, 10
	syscall
