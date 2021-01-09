#		Organizacao e Arquitetura de Computadores
#
#		Prova 1  - Questao 2
#
#	Nome: Murilo Mussatto
#	NUSP: 11234245
#
#
#
#	$s1 - guarda a soma do CNI para inteiros
#	$f1 - guarda a soma do CNF para floats


.data 

	vetor_x:		.word 0, 0, 0
	vetor_w:	.word 0, 0, 0	, 0
	
	
	msg1:	.asciiz "Digite 3 numeros do vetor X e os 4 numeros do vetor W:\n"
	msg2:	.asciiz "A soma pondera eh: "
	msg3:	.asciiz "\nOperacao de Ponto-Fixo (inteiro)\n"
	msg4:	.asciiz "\nOperacao de Ponto-Flutuante (float)\n"
	msg5:	.asciiz "ativado"
	msg6:	.asciiz "zero"
	msg7:	.asciiz "inativo"
	
	
	
.text
	.globl main
	
main:

# ----------------------- Operacao com Inteiros ---------------------------------------------------
	li $v0, 4
	la $a0, msg3
	syscall

	#------ Leitura dos Inteiros ---------------------
	
	li $v0, 4
	la $a0, msg1
	syscall

	li $v0, 5
	syscall
	sw $v0, vetor_x
	
	li $v0, 5
	syscall
	sw $v0, vetor_x+4
	
	li $v0, 5
	syscall
	sw $v0, vetor_x+8
	
	li $v0, 5
	syscall
	sw $v0, vetor_w
	
	li $v0, 5
	syscall
	sw $v0, vetor_w+4
	
	li $v0, 5
	syscall
	sw $v0, vetor_w+8
	
	li $v0, 5
	syscall
	sw $v0, vetor_w+12
	
	
	jal CNI   	#chama subrotina para inteiros 

	#------- Imprime Resultado ----------------------------------------------------------------		
	li $v0, 4
	la $a0, msg2
	syscall
	
	li $v0, 1
	move $a0, $s1
	syscall
	
	bgtz $s1, ativo
	beqz $s1, zero

inativo:
	li $v0, 4
	la $a0, msg7
	syscall
	
	j FLOAT	
	
ativo:
	li $v0, 4
	la $a0, msg5
	syscall
	
	j FLOAT

zero:	
	li $v0, 4
	la $a0, msg6
	syscall
	
	j FLOAT			
				
# ----------------------- Operacao com Floats ---------------------------------------------------	

FLOAT:
	li $v0, 4
	la $a0, msg4
	syscall

	#------ Leitura dos Floats ---------------------
	
	li $v0, 4
	la $a0, msg1
	syscall

	li $v0, 6
	syscall
	s.s $f0, vetor_x
	
	li $v0, 6
	syscall
	s.s $f0, vetor_x+4
	
	li $v0, 6
	syscall
	s.s $f0, vetor_x+8
	
	li $v0, 6
	syscall
	s.s $f0, vetor_w
	
	li $v0, 6
	syscall
	s.s $f0, vetor_w+4
	
	li $v0, 6
	syscall
	s.s $f0, vetor_w+8
	
	li $v0, 6
	syscall
	s.s $f0, vetor_w+12
	
	
	jal CNF   	#chama subrotina para float

	#------- Imprime Resultado ----------------------------------------------------------------		
	li $v0, 4
	la $a0, msg2
	syscall
	
	li $v0, 2
	mov.s $f12, $f1
	syscall	
	
	c.eq.s $f1, $f11 
	bc1t zero_f
	
	c.lt.s $f1, $f11
	bc1t inativo_f
	
ativo_f:
	li $v0, 4
	la $a0, msg5
	syscall
	
	j FIM
	
inativo_f:
	li $v0, 4
	la $a0, msg7
	syscall
	
	j FIM
	
zero_f:	
	li $v0, 4
	la $a0, msg6
	syscall
	
	j FIM	
	
	
# --------------- Fim ------------------------------------------------------------------------
FIM:	
	li   $v0,10
	syscall 		

		
#------ Subrotina de Ativacao dos Neuronios -------------------------------------
CNI:
	lw $s1, vetor_w
	
	lw $t0, vetor_x
	lw $t1, vetor_w+4
	mul $t3, $t0, $t1
	add $s1, $s1, $t3
	
	lw $t0, vetor_x+4
	lw $t1, vetor_w+8
	mul $t3, $t0, $t1
	add $s1, $s1, $t3
	
	lw $t0, vetor_x+8
	lw $t1, vetor_w+12
	mul $t3, $t0, $t1
	add $s1, $s1, $t3
	
	jr $ra 	#return 

CNF:
	l.s $f1, vetor_w
	
	l.s $f2, vetor_x
	l.s $f3, vetor_w+4
	mul.s $f4, $f2, $f3
	add.s $f1, $f1, $f4 
	
	l.s $f2, vetor_x+4
	l.s $f3, vetor_w+8
	mul.s $f4, $f2, $f3
	add.s $f1, $f1, $f4 
	
	l.s $f2, vetor_x+8
	l.s $f3, vetor_w+12
	mul.s $f4, $f2, $f3
	add.s $f1, $f1, $f4 
	
	jr $ra	# return 
	
