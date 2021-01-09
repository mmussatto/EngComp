#		Organizacao e Arquitetura de Computadores
#
#		Prova 1 - Questao 1
#
#	Nome: Murilo Mussatto
#	NUSP: 11234245
#
#
#	$s0 - ponteiro do file original
#	$s1 - pontieiro do file novo
#	$s2 - contador
#	$s3 - novo pixel
#	

.data 
				.align 2
	arq_nome:	.asciiz "image.pgm"
				
				.align 2
	arq2_nome:	.asciiz "conv.pgm"
	
				.align 2
	bufferin:	.space 10038
	
				.align 2
	bufferout:	.space 10038
	
	
.text
	.globl main
	
main:

# -------- Abre Arquivo -------------------
	li $v0, 13
	la $a0, arq_nome
	li $a1, 0		#leitura
	li $a2, 0
	syscall
	move $s0, $v0
	
	li $v0, 13
	la $a0, arq2_nome
	li $a1, 1		#escrita
	li $a2, 0
	syscall
	move $s1, $v0	
	
# ------- Le arquivo ------------------------ 
	li   $v0, 14
	move $a0, $s0
	la   $a1, bufferin
	li   $a2,  10038
	syscall
	
	
# ---------- Copia Cabecalho ------------------------

	move $s2, $zero #reseta contador
loop:	
	lb $t0,  bufferin +0($s2)
	sb $t0, bufferout + 0($s2)
	
	addiu $s2, $s2, 1	#contador ++
	blt $s2, 38, loop		# while contador < 38

			
# --------- Convolucao ---------------------------------
convolucao:
	move $s3, $zero		#reseta novo pixel

	lb $t0,  bufferin + -1($s2) 
	mul $t0, $t0, -3
	add $s3, $s3, $t0 	#primeira operacao
	
	lb $t0,  bufferin + 0($s2)
	mul $t0, $t0, 10
	add $s3, $s3, $t0	#segunda operacao
	
	lb $t0,  bufferin + 1($s2)
	mul $t0, $t0, -3
	add $s3, $s3, $t0	#terceira operacao
	
	sb $s3, bufferout + 0($s2) 	#salva o novo byte no bufferout 
	
	addiu $s2, $s2, 1	# contador ++
	blt $s2, 10038, convolucao	#loop
	
	
# ----------- Escreve no Arquivo ------------------------------- 
	li   $v0, 15      
	move $a0, $s1    
	la   $a1, bufferout    
	li   $a2, 10038       
	syscall
	
	
# -------------- Fecha Arquivo ----------------------------------
	li   $v0, 16      
	move $a0, $s0
	syscall    
	
	li   $v0, 16      
	move $a0, $s1
	syscall         
	
# --------------- Fim ----------------------------------------------
	li   $v0,10
	syscall 