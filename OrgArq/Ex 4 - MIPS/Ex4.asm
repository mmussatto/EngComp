#
# Ex Lista 4
#
#Nome:	Murilo Mussatto
#NUSP:	11234245
#
# $s1 --  endereco do comeco da lista
# $s2 -- Tamanho da Lista
# $s3 --  endereco do vetor de dados
# $s4 --  no atual
# $s5 --  endereco proximo no
# $s6 -- contador


.data
	Vetor : 		.word 15, 31, 63, 127, 255, 511, 1023, 2047, 4097, 65536, 0
	TamLista:	.word 0
	LI:			.word 0 		#ponteiro incio lista
	Contador:	.word 0
	
	msg1:		.asciiz "Lista:"
	msg2:		.asciiz "\n"

.text
	.globl main
	
main:
		lw $s2, TamLista	#s2 = TamLista
		la $s3, Vetor		#s3 = &Vetor
		lw $s6, Contador
	
loop:	
		mulu $t2,  $s2, 4		# t2 = TamLista*4
		add $t1, $s3, $t2		# t1 = EnderecoVetor+(TamLista*4)
		lw $t1, ($t1)			# coloca o dado que esta no endereco t1 em t1
	
		bnez  $s2, store		#if  TamLista != 0 -- lista ja foi iniciada

inicia:	li $a0, 8 	#bytes de memoria
		li $v0, 9		#instrucao sbrk
		syscall
	
		#guarda endereco do comeco da lista
		sw $v0, LI 	
		move $s1, $v0	#s1 = LI
		move $s4, $s1	#no atual = LI

		sw $t1, 0($s4)		#guarda o primeiro elemento do vetor na lista 
		addiu $s2, $s2, 1	#TamLista++
		
		j loop
	
store:	li $a0, 8 	#bytes de memoria
		li $v0, 9		#instrucao sbrk
		syscall
	
		add $s5, $s4, 4	#espaco para o endereco do proximo no
		sw $v0, 0($s5) 	#guarda endereco do proximo nó
		
		move $s4, $v0
		sw $t1, 0($s4)		#guarda o primeiro elemento do vetor na lista 
		addiu $s2, $s2, 1	#TamLista++
		
		bnez $t1, loop 		#valor no vetor != zero -- recomeca rotina


		#Inicia printa da lista
		li $v0,4
    		la $a0,msg1 	#"Lista:"
    		syscall
    		
		li $v0,4
    		la $a0,msg2		#"\n"
    		syscall    		

		move $s4, $s1 	#no atual = LI
		
imprime:	
		lw $a0, ($s4)	#imprime valor do no atual
		li $v0, 1
		syscall
		
		li $v0,4
    		la $a0,msg2		#"\n"
    		syscall		
		
		lw $s4, 4($s4)	# no atual = prox no
		
		addiu $s6, $s6, 1 #contador++

		bne $s2, $s6, imprime	#se Contador != TamLista -- continua imprimindo	 					

fim: 	li $v0,10	#FIM
    		syscall