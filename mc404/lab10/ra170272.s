	.org 0x0
	.section .iv, "a"

_start:

interrupt_vector:
	b RESET_HANDLER

	.org 0x18
	b IRQ_HANDLER 


@ <<<SESSÃO DE DADOS>>>
	.data
COUNTER:
	.skip 4

IRQ_STACK:
	.skip 1024
IRQ_STACK_BEGIN:


@ <<<SESSÃO DE CÓDIGO>>>
	.org 0x100
	.text
	.align 4
	
RESET_HANDLER:
	@ Zera o contador
	ldr r2, =COUNTER
	mov r0, #0
	str r0, [r2]

	@ Configura endereco da tabela 'interrupt_vector'
	ldr r0, =interrupt_vector
	mcr p15, 0, r0, c12, c0, 0


	
	@ Troca para o modo IRQ
	mrs r0, cpsr 		@ lê o conteúdo de cpsr para r0
	bic r0, r0, #0x1F	@ limpa os bits Mode [0:4] de cpsr
	orr r0, r0, #0x12	@ carrega mascara do modo IRQ (0b10010)
	msr CPSR_c, r0 		@ salva conteudo de r0 em cpsr, trocando de modo

	@ Configura o apontador para a pilha do modo IRQ
	ldr r13_irq, =IRQ_STACK_BEGIN 
	
	@ Retorna para o modo SUPERVISOR
	mrs r0, cpsr 		@ lê o conteúdo de cpsr para r0
	bic r0, r0, #0x1F	@ limpa os bits Mode [0:4] de cpsr
	orr r0, r0, #0x13	@ carrega mascara do modo SUPERVISOR (0b10011)
	msr CPSR_c, r0 		@ salva conteudo de r0 em cpsr, trocando de modo

SET_GPT:
	@ Endereços dos registradores de GPT
	.set GPT_CR, 	#0x53FA0000
	.set GPT_PR, 	#0x53FA0004
	.set GPT_IR,	#0X53FA000C
	.set GPT_OCR1,	#0X53FA0010

	@ Configura registrador de controle GPT_CR
	ldr r0, =GPT_CR
	mov r1, #0x41		@ clock_scr para 'periférico'
	str r1, [r0] 		@ configura clock_scr
	@ Configura valores iniciais e finais para contagem
	ldr r0, GPT_PR
	mov r1, #0x0		@ valor inicial
	str r1, [r0]
	ldr r0, GPT_OCR1
	mov r1, #100		@ valor final
	str r1, [r0]
	@ Configura registrador de interrupção GPT_IR
	ldr r0, GPT_IR
	mov r1, #0x1		@ habilita interrupção
	str r1, [r0]
		
SET_TZIC:
	@ Constantes para os enderecos do TZIC
	.set TZIC_BASE,             0x0FFFC000
	.set TZIC_INTCTRL,          0x0
	.set TZIC_INTSEC1,          0x84 
	.set TZIC_ENSET1,           0x104
	.set TZIC_PRIOMASK,         0xC
	.set TZIC_PRIORITY9,        0x424
	
	@ Liga o controlador de interrupcoes
	@ R1 <= TZIC_BASE
	
	ldr	r1, =TZIC_BASE
	
	@ Configura interrupcao 39 do GPT como nao segura
	mov	r0, #(1 << 7)
	str	r0, [r1, #TZIC_INTSEC1]
	
	@ Habilita interrupcao 39 (GPT)
	@ reg1 bit 7 (gpt)
	
	mov	r0, #(1 << 7)
	str	r0, [r1, #TZIC_ENSET1]
	
	@ Configure interrupt39 priority as 1
	@ reg9, byte 3
	
	ldr r0, [r1, #TZIC_PRIORITY9]
	bic r0, r0, #0xFF000000
	mov r2, #1
	orr r0, r0, r2, lsl #24
	str r0, [r1, #TZIC_PRIORITY9]
	
	@ Configure PRIOMASK as 0
	eor r0, r0, r0
	str r0, [r1, #TZIC_PRIOMASK]
	
	@ Habilita o controlador de interrupcoes
	mov	r0, #1
	str	r0, [r1, #TZIC_INTCTRL]
	
	@instrucao msr - habilita interrupcoes
	msr  CPSR_c, #0x13       @ SUPERVISOR mode, IRQ/FIQ enabled

laco:
	b laco
	
IRQ_HANDLER:
	mov GPT_SR, 0x1 @???????
	
	ldr r0, =COUNTER
	ldr r1, [r0]
	add r1, r1, #1
	str r1, [r0]
	sub lr, lr, #4
	movs pc, lr
