@.TITLE  SHEP,'JERK DOS'
@   6.3 10-6-78
@   32 BIT ASSEMBLER
@.M6502
@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@   (C)  COPYRIGHT 1978  PINEAPPLE COMPUTER, INC
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@ CONSTANTES

.set TIME_SZ, 200
.set MAX_ALARMES, 8 
.set MAX_CALLBACKS, 8 
.set TIME_10MS_INSTRUCTIONS_QTY, 200

@ TZIC REGISTERS
.set TZIC_BASE,             0x0FFFC000
.set TZIC_INTCTRL,          0x0
.set TZIC_INTSEC1,          0x84 
.set TZIC_ENSET1,           0x104
.set TZIC_PRIOMASK,         0xC
.set TZIC_PRIORITY9,        0x424

@ GPT REGISTERS
.set GPT_CR,   0x53FA0000 
.set GPT_PR,   0x53FA0004 
.set GPT_IR,   0x53FA000C 
.set GPT_OCR1, 0x53FA0010
.set GPT_SR,   0x53FA0008

@ GPIO REGISTERS
.set GPIO_DR,   0x53F84000
.set GPIO_GDIR, 0x53F84004
.set GPIO_PSR,  0x53F84008

.set GPIO_GDIR_INIT_MASK, 0xFFFC003E 


@ Local do codigo do usuario
.set USER_CODE, 0x77812000

.org 0x0
.section .iv,"a"

_start:     

interrupt_vector:
    b RESET_HANDLER
.org 0x08
    b SYS_CALL_HANDLER
.org 0x18
    b IRQ_HANDLER


.data

SYSTEM_TIME: .word 0

IRQ_STACK:
    .skip 1024
IRQ_STACK_BEGIN:

SUPERVISOR_STACK:
    .skip 1024
SUPERVISOR_STACK_BEGIN:

USER:
    .skip 1024
USER_STACK_BEGIN:


VETOR_ALARMES:
    .skip 128
QTD_ALARMES:
    .word 0

VETOR_CALLBACKS: 
    .skip 256
QTD_CALLBACKS:
    .word 0

FLAGS: @ flags usada para controle do irq, verifica_alarmes e verifica_callbacks
    .skip 1
    @ os ultimos bits da flag significam:
    @ irq|va|vc
    @ irq: habilitado tratamento do irq (1);
    @ va: verificacao de alarmes ativa (1);
    @ vc: verificacao de callbacks ativa (1);


.text
.align 4

RESET_HANDLER:

    @ Zera o contador
    ldr r2, =SYSTEM_TIME
    mov r0, #0
    str r0, [r2]

    @Faz o registrador que aponta para a tabela de interrupções apontar para a tabela interrupt_vector
    ldr r0, =interrupt_vector
    mcr p15, 0, r0, c12, c0, 0

CONF_IRQ:
    @ Ajustar a pilha do modo IRQ.
    msr CPSR_c, #0xD2
    ldr sp, =IRQ_STACK_BEGIN

CONF_SUPERVISOR:
    @ ajustar a pilha do modo supervisor
    msr CPSR_c, #0x13
    ldr sp, =SUPERVISOR_STACK_BEGIN


    @ configurando gpt
CONF_GPT:
    @ habilitando gpt
    ldr r1, =GPT_CR
    mov r0, #0x41
    str r0, [r1]

    @ zerando prescaler
    ldr r1, =GPT_PR
    mov r0, #0x0
    str r0, [r1]

    @ configurando o valor para contar
    ldr r1, =GPT_OCR1
    ldr r0, =TIME_SZ
    str r0, [r1]

    @ demonstrando interesse na interrupcao
    ldr r1, =GPT_IR
    mov r0, #1
    str r0, [r1]

SET_TZIC:
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
    msr  CPSR_c, #0x13       @ SUPERVISOR mode, IRQ/FIQ enable

SET_GPIO:
    ldr r1, =GPIO_GDIR
    ldr r2, =GPIO_GDIR_INIT_MASK
    str r2, [r1]

    @ inicializa pinos
    mov r0, #0x02040000
    ldr r1, =GPIO_DR
    str r0, [r1]

SET_FLAGS:
    @ habilita as flags para verificar alarmes e callbacks
    ldr r1, =FLAGS
    mov r0, #0b111
    strb r0, [r1]


RUN_USER_CODE:
    @ entra no modo user e roda o codigo do usuario
    msr CPSR_c, #0x10
    ldr sp, =USER_STACK_BEGIN

    ldr r0, =USER_CODE 
    bx r0

@ Handler de interrupcao IRQ
IRQ_HANDLER:
    push {r0-r12, lr}

    @ TODO desabilita outras interrupcoes do tipo IRQ
    @mov r0, #0b10000000
    @mrs r1, CPSR
    @orr r1, r1, r0
    @msr CPSR, r1	

    @ verifica se deve executar irq
    ldr r1, =FLAGS
    ldr r0, [r1]
    
    tst r0, #0b100
    bleq IRQ_HANDLER_END
    
    @ desabilita irq handler 
    bic r0, r0, #0b100
    str r0, [r1]

    ldr r1, =GPT_SR
    mov r0, #1
    str r0, [r1]

    @ incrementa o contador
    ldr r1, =SYSTEM_TIME
    ldr r0, [r1]
    add r0, r0, #1

    @ salva o novo tempo de sistema
    str r0, [r1]
    mov r5, r0 @ r5 == tempo do sistema

    @ verifica os alarmes e callbacks ativos
    push {r0-r1}

    @ carrega as flags
    ldr r0, =FLAGS
    ldrb r0, [r0]
    
    tst r0, #0b10
    push {r0}
    mov r0, r5
    blne verifica_alarmes
    pop {r0}

    tst r0, #0b01
    blne verifica_callbacks

    pop {r0-r1}

    @ TODO habilita outras interrupcoes do tipo IRQ
    @mov r0, #0b10000000
    @mrs r1, CPSR
    @bic r1, r1, r0
    @msr CPSR, r1	

    @ habilita novamente irq
    ldr r1, =FLAGS
    ldr r0, [r1]
    
    orr r0, r0, #0b100
    str r0, [r1]
	
IRQ_HANDLER_END:
    @ retornando da interrupcao
    pop {r0-r12, lr}
    sub lr, lr, #4
    movs pc, lr

@ Funcao para verificar quais alarmes estao ativos
@ parametros:
@ - r0: tempo do sistema
@
@ retorno:
verifica_alarmes:
    push {r4-r7, lr}

    mov r5, r0 @ r5 == tempo do sistema
    @ carrega o numero de alarmes
    ldr r4, =QTD_ALARMES
    ldr r4, [r4] @ r4 == numero de alarmes
    mov r0, #0 @ r0 == indice do loop

    @ TODO DEBUG verifica erro de nenhum alarme
    @cmp r4, #0
    @beq verifica_alarmes_erro

    @ itera sobre todos os alarmes
verifica_alarmes_loop:
    @ verifica se chegou ao fim
    cmp r0, r4
    beq verifica_alarmes_endloop

    @ carrega o alarme em r2 e r3
    ldr r1, =VETOR_ALARMES 
    add r1, r1, r0, LSL #3 @ calcula o indice do registro
    
    @ carrega o registro
    ldr r6, [r1]     @ r6 == tempo que deve chamar a interrupcao
    ldr r7, [r1, #4] @ r7 == ponteiro para a funcao

    @ verifica se esta no momento de chamar a funcao
    cmp r6, r5
    bhi verifica_alarmes_endif
    verifica_alarmes_then:
        @ remove a callback do vetor
        sub r4, r4, #1
        mov r1, r0 @ r1 == indice j para mover os proximos elementos
        verifica_alarmes_move_loop:
            cmp r1, r4
            beq verifica_alarmes_move_endloop

            @ pega o elemento j+1 e coloca na posicao j
            ldr r2, =VETOR_ALARMES
            add r2, r2, r1, LSL #3 @ calcula o indice do registro
            
            @ carrega o proximo e salva em j
            ldr r3, [r2, #8]
            str r3, [r2]
            ldr r3, [r2, #12]
            str r3, [r2, #4]

            add r1, r1, #1 @ j++
            b verifica_alarmes_move_loop
        verifica_alarmes_move_endloop:

        @ salva a nova quantidade de callbacks
        ldr r3, =QTD_ALARMES
        str r4, [r3]

        @ chama o callback
        push {r0-r3}

        @ muda para o modo de usuario
        msr CPSR_c, #0x10
        @ roda a callback
        blx r7
        @ retorna ao modo irq chamando a callback 30
        mov r7, #30
        add r0, pc, #0 @ carrega o endereco de retorno como parametro
        svc 0x0

        pop {r0-r3}

        @ carrega novamente a quantidade de callbacks
        ldr r3, =QTD_ALARMES
        ldr r4, [r3]

        @ carrega novamente o tempo do sistema
        ldr r5, =SYSTEM_TIME
        ldr r5, [r5]

        @ retorna uma posicao i: i--
        sub r0, r0, #1
    verifica_alarmes_endif:

    add r0, r0, #1 @ i++
    b verifica_alarmes_loop
verifica_alarmes_endloop:

    pop {r4-r7, lr}
    mov pc, lr

verifica_alarmes_erro: @ TODO DEBUG
    mov r0, r0
    b verifica_alarmes_endloop

@ Funcao para verificar quais callbacks estão ativas
@ parametros:
@ retorno:
verifica_callbacks:
    push {r4-r8, lr}

    @ desativa as callbacks
    bl desativar_callbacks

    @ carrega o numero de callbacks
    ldr r4, =QTD_CALLBACKS
    ldr r4, [r4] @ r4 == numero de callbacks
    mov r0, #0 @ r0 == indice do loop

    @ itera sobre todos as callbacks
verifica_callbacks_loop:
    @ verifica se chegou ao fim
    cmp r0, r4
    beq verifica_callbacks_endloop

    @ calcula a posicao da callback
    ldr r1, =VETOR_CALLBACKS 
    mov r2, #12
    mul r2, r0, r2
    add r1, r1, r2 @ indice base do registro
    
    @ carrega o registro
    ldr r5, [r1]     @ r5 == identificador do sonar
    ldr r6, [r1, #4] @ r6 == threshold de distancia
    ldr r7, [r1, #8] @ r7 == ponteiro para a funcao

    @ calcula a distancia para esse sonar
    push {r0-r3}
    mov r0, r5
    bl read_sonar
    @ move a distancia lida para r8
    mov r8, r0
    pop {r0-r3}

    @ verifica se passa do threshold
    cmp r8, r6
    bhi verifica_callbacks_endif
    verifica_callbacks_then:

        @ remove a callback do vetor
        sub r4, r4, #1
        mov r1, r0 @ r1 == indice j para mover os proximos elementos
        verifica_callbacks_move_loop:
            cmp r1, r4
            beq verifica_callbacks_move_endloop

            @ pega o elemento j+1 e coloca na posicao j
            ldr r2, =VETOR_CALLBACKS
            mov r3, #12
            mul r3, r1, r3
            add r2, r2, r3 @ calcula o indice do registro j
            
            @ carrega o proximo e salva em j
            ldr r3, [r2, #12]
            str r3, [r2]
            ldr r3, [r2, #16]
            str r3, [r2, #4]
            ldr r3, [r2, #20]
            str r3, [r2, #8]

            add r1, r1, #1 @ j++
            b verifica_callbacks_move_loop
        verifica_callbacks_move_endloop:

        @ salva a nova quantidade de callbacks
        ldr r3, =QTD_CALLBACKS
        str r4, [r3]

        @ chama o callback
        push {r0-r3}

        @ muda para o modo de usuario
        msr CPSR_c, #0x10
        @ roda a callback
        blx r7
        @ retorna ao modo irq chamando a callback 30
        mov r7, #30
        add r0, pc, #0 @ carrega o endereco de retorno como parametro
        svc 0x0

        pop {r0-r3}

        @ carrega novamente a quantidade de callbacks
        ldr r3, =QTD_CALLBACKS
        ldr r4, [r3]

        @ retorna uma posicao i: i--
        sub r0, r0, #1
    verifica_callbacks_endif:

    add r0, r0, #1 @ i++
    b verifica_callbacks_loop
verifica_callbacks_endloop:
    @ ativa as callbacks
    bl ativar_callbacks

    pop {r4-r8, lr}
    mov pc, lr

SYS_CALL_HANDLER:
    push {lr}

    @ checa o numero da syscall
    cmp r7, #16
    bleq read_sonar

    cmp r7, #17
    bleq register_proximity_callback

    cmp r7, #18
    bleq set_motor_speed

    cmp r7, #19
    bleq set_motors_speed

    cmp r7, #20
    bleq get_time

    cmp r7, #21
    bleq set_time

    cmp r7, #22
    bleq set_alarm

    pop {lr}

    @ trata a syscall para retornar ao modo irq
    cmp r7, #30
    beq load_irq_mode

    @ retorna da syscall
    movs pc, lr

@ Funcao para syscall de leitura de sonar
@ parametros:
@ - r0: id do sonar a ser lido
@
@ retorno:
@ - r0: valor do sonar ou -1 se for invalido
read_sonar:
    push {r4-r5, lr}

    ldr r4, =GPIO_DR @ R4 == GPIO DATA REGISTER
    ldr r5, =GPIO_PSR @ R5 == GPIO DATA REGISTER

    cmp r0, #15
    movhi r0, #-1
    bhi read_sonar_end

    @ escreve o id do sonar nos pinos mux
    mov r0, r0, LSL #2
    @ le o data register
    ldr r2, [r4]

    @ escreve o id do sonar
    bic r2, r2, #0b111110
    orr r2, r2, r0
    str r2, [r4]

    @ tempo de 10ms
    ldr r0, =TIME_10MS_INSTRUCTIONS_QTY
    bl wait_for_it

    @ sobe o trigger
    mov r0, #0b10
    orr r2, r2, r0
    str r2, [r4]

    @ tempo de 10ms
    ldr r0, =TIME_10MS_INSTRUCTIONS_QTY
    bl wait_for_it

    @ desce o trigger
    mov r0, #0b10
    bic r2, r2, r0
    str r2, [r4]

    @ entra em loop verificando a flag
read_sonar_loop:
    @ tempo de 10ms
    ldr r0, =TIME_10MS_INSTRUCTIONS_QTY
    bl wait_for_it

    @ le os dados
    ldr r0, [r4]

    @ verifica a flag
    and r0, r0, #1
    cmp r0, #1
    beq read_sonar_endloop

    b read_sonar_loop
read_sonar_endloop:
    
    @ leitura da distancia do sonar
    ldr r0, [r4]
    mov r0, r0, LSL #14
    mov r0, r0, LSR #20

read_sonar_end:
    pop {r4-r5, lr}
    mov pc, lr

@ Funcao para syscall para setar a velocidade do motor
@ parametros:
@ - r0: id do motor a ser escrito
@ - r1: valor do motor
@
@ retorno:
@ - r0: 0 caso tudo ok, -1 caso id invalido, -2 caso velocidade invalida
set_motor_speed:
    push {r4}

    @ checa identificador do motor
    cmp r0, #1
    movhi r0, #-1
    bhi set_motor_speed_end

    @ checa velocidade do motor
    cmp r1, #0b111111
    movhi r0, #-2
    bhi set_motor_speed_end

    ldr r4, =GPIO_DR @ R4 == GPIO DATA REGISTER
    @ le o data register
    ldr r2, [r4]

    mov r3, #0b1111111 @ mascara base para zerar o motor

    @ verifica se eh o motor 0
    cmp r0, #0
    bne set_motor_speed_else
set_motor_speed_then:
    @ desloca a velocidade para a posicao correta
    mov r0, r1, LSL #19
    mov r3, r3, LSL #18
    b set_motor_speed_endif
set_motor_speed_else:
    @ desloca a velocidade para a posicao correta
    mov r0, r1, LSL #26
    mov r3, r3, LSL #25
set_motor_speed_endif:
    bic r2, r2, r3 @ zera a velocidade e habilita escrita
    orr r0, r0, r2
     
    str r0, [r4] 

    @ TODO subir pino de write (desabilitar escrita)

    @ retorno ok
    mov r0, #0
set_motor_speed_end:
    pop {r4}
    mov pc, lr


@ Funcao para syscall para setar a velocidade dos motor
@ parametros:
@ - r0: valor do motor 0
@ - r1: valor do motor 1
@
@ retorno:
@ - r0: 0 caso tudo ok, -1 caso vel do motor 0 invalida, -2 caso vel do motor 1 invalida
set_motors_speed:
    push {r4-r6, lr}

    @ checa velocidade dos motores
    cmp r0, #0b111111
    movhi r0, #-1
    bhi set_motors_speed_end

    cmp r1, #0b111111
    movhi r0, #-2
    bhi set_motors_speed_end
   
    mov r5, r0 @ R5 == VELOCIDADE DO MOTOR 0
    mov r6, r1 @ R6 == VELOCIDADE DO MOTOR 1

    ldr r4, =GPIO_DR @ R4 == GPIO DATA REGISTER

    @ le o data register
    ldr r2, [r4]

    mov r3, #0b1111111 @ mascara base para zerar o motor

    @ desloca a velocidade para a posicao correta dos motores
    mov r0, r5, LSL #19
    mov r1, r3, LSL #18

    orr r0, r0, r6, LSL #26
    orr r1, r1, r3, LSL #25

    bic r2, r2, r1 @ zera a velocidade e habilita escrita
    orr r2, r2, r0
     
    str r0, [r4] 

    @ TODO subir pino de write (desabilitar escrita)

    @ retorno ok
    mov r0, #0
set_motors_speed_end:
    pop {r4-r6, lr}
    mov pc, lr


@ Funcao para syscall de retornar o tempo do sistema
@ parametros:
@ retorno:
@ - r0: tempo do sistema
get_time:
    ldr r0, =SYSTEM_TIME
    ldr r0, [r0]
    mov pc, lr

@ Funcao para syscall de setar novo tempo de sistema
@ parametros:
@ - r0: novo tempo do sistema
@
@ retorno:
set_time:
    ldr r1, =SYSTEM_TIME
    str r0, [r1]
    mov pc, lr

@ Funcao para syscall de setar novo alarme de sistema
@ parametros:
@ - r0: ponteiro para a funcao
@ - r1: tempo do sistema
@
@ retorno:
@ -1 caso ja exista o maximo de alarmes ativos, -2 caso seja um tempo menor que o sistema
set_alarm:
    push {r4-r8, lr}

    mov r6, r0 @ r6 == ponteiro para a funcao
    mov r7, r1 @ r7 == tempo do sistema

    @ verifica a quantidade de alarmes ativos
    ldr r4, =QTD_ALARMES
    ldr r2, [r4]

    @ retorna o maximo de alarmes
    ldr r5, =MAX_ALARMES
    
    cmp r2, r5
    moveq r0, #-1
    beq set_alarm_end

    @ verifica o tempo do sistema
    bl get_time
    cmp r7, r0
    movls r0, #-2
    bls set_alarm_end

    @ adiciona o alarme na posicao r2 do vetor de alarmes
    ldr r8, =VETOR_ALARMES @ r8 == base do vetor de alarmes

    @ calcula a posicao inicial do registro
    mov r0, r8
    add r0, r0, r2, LSL #3
    
    @ salva o registro
    str r7, [r0]
    str r6, [r0, #4]

    @ incrementa o numero de alarmes
    add r2, r2, #1
    str r2, [r4]

    @ retorna tudo ok
    mov r0, #0
set_alarm_end:
    pop {r4-r8, lr}
    mov pc, lr

@ Funcao para syscall de setar nova callback de proximidade
@ parametros:
@ - r0: identificador do sonar
@ - r1: limiar de distancia
@ - r2: ponteiro para a funcao
@
@ retorno:
@ -1 caso ja exista o maximo de callbacks ativos, -2 caso o identificador do sonar seja invalido
@ 0 caso contrario
register_proximity_callback:
    push {r4-r9, lr}

    mov r6, r2 @ r6 == ponteiro para a funcao
    mov r7, r0 @ r7 == identificador do sonar
    mov r8, r1 @ r8 == limiar de distancia

    @ verifica a quantidade de alarmes ativos
    ldr r4, =QTD_CALLBACKS
    ldr r2, [r4]

    @ retorna o maximo de alarmes
    ldr r5, =MAX_CALLBACKS
    
    cmp r2, r5
    moveq r0, #-1
    beq register_proximity_callback_end

    @ verifica o identificador do sonar
    cmp r7, #15
    movhi r0, #-2
    bhi register_proximity_callback_end

    @ adiciona o callback na posicao r2 do vetor de callbacks
    ldr r9, =VETOR_CALLBACKS @ r9 == base do vetor de callbacks

    @ calcula a posicao inicial do registro
    mov r0, r9
    mov r3, #12
    mul r1, r2, r3
    add r0, r0, r1
    
    @ salva o registro
    str r7, [r0]
    str r8, [r0, #4]
    str r6, [r0, #8]

    @ incrementa o numero de alarmes
    add r2, r2, #1
    str r2, [r4]

    @ retorna tudo ok
    mov r0, #0
register_proximity_callback_end:
    pop {r4-r9, lr}
    mov pc, lr


@ Syscall para carregar o modo irq, util para ser chamada apos uma callback no modo
@ usuario
@ parametros:
@ - r0: endereco para retorno (lr)
@ retorno:
load_irq_mode:
    @ muda de modo
    msr CPSR_c, #0xD2
    @ carrega o endereco de retorno
    mov lr, r0
    @ retorna
    mov pc, lr


@@ UTILS FUNCS

@ Funcao para ficar um tempo sem fazer nada
@ parametros:
@ - r0: quantidade de iteracoes
@ 
@ retorno:
wait_for_it:
    mov r1, #0

wait_for_it_loop:
    cmp r1, r0
    beq wait_for_it_endloop

    add r1, r1, #1
    b wait_for_it_loop
wait_for_it_endloop:

    mov pc, lr

@ Funcao para desativar o tratamento das callbacks
@ parametros:
@ retorno:
desativar_callbacks:
    ldr r1, =FLAGS
    ldrb r0, [r1]
    bic r0, r0, #0b01
    strb r0, [r1]
   
    mov pc, lr

@ Funcao para ativar o tratamento das callbacks
@ parametros:
@ retorno:
ativar_callbacks:
    ldr r1, =FLAGS
    ldrb r0, [r1]
    orr r0, r0, #0b01
    strb r0, [r1]
   
    mov pc, lr
