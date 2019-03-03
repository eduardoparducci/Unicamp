.globl _start

.set SIZE 16380
        
.data

input_buffer:   .skip 32
output_buffer:  .skip 32
vetor_a:        .skip SIZE
vetor_b:        .skip SIZE
.text
.align 4

@ Funcao inicial
_start:
    @ Chama a funcao "read" para ler 4 caracteres da entrada padrao
    ldr r0, =input_buffer
    mov r1, #4             @ 3 caracteres + '\n'
    bl  read
    mov r5, r0             @ copia o retorno para r5.

    @ Chama a funcao "atoi" para converter a string para um numero
    ldr r0, =input_buffer
    mov r1, r5
    bl  atoi
    mov r5, r0             @ copia o retorno para r5.

    
    @ Chama a funcao "itoa" para converter o numero para uma string
    ldr r0, =output_buffer
    mov r1, #4
    mov r2, r5             @ copia o numero para r2
    bl  itoa
    mov r5, r0             @ copia o retorno para r5.
        
    @ Chama a funcao "write" para escrever os 3 bytes e
    @ o ' ' na saida padrao.
    ldr r0, =output_buffer
    mov r1, #4         @ 3 caracteres + ' '
    bl  write


    @ Chama a funcao exit para finalizar processo.
    mov r0, #0
    bl  exit

@ Leitura de dados da entrada padrao.
@ parametros:
@  r0: endereco inicial do buffer de entrada.
@  r1: tamanho do buffer.
@ retorno:
@  r0: numero de bytes lidos.
read:
    push {r4,r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, #0         @ stdin file descriptor = 0
    mov r1, r4         @ endereco do buffer
    mov r2, r5         @ tamanho maximo.
    mov r7, #3         @ read
    svc 0x0
    pop {r4, r5, lr}
    mov pc, lr


@ Escreve uma sequencia de bytes na saida padrao.
@ parametros:
@  r0: endereco do buffer de memoria que contem a sequencia de bytes.
@  r1: numero de bytes a serem escritos
write:
    push {r4,r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, #1         @ stdout file descriptor = 1
    mov r1, r4         @ endereco do buffer
    mov r2, r5         @ tamanho do buffer.
    mov r7, #4         @ write
    svc 0x0
    pop {r4, r5, lr}
    mov pc, lr

@ Finaliza a execucao de um processo.
@  r0: codigo de finalizacao (Zero para finalizacao correta)
exit:    
    mov r7, #1         @ syscall number for exit
svc 0x0

@ Converte uma sequencia de caracteres hexadecimais para um numero binario
@ parametros:
@  r0: endereco do buffer de memoria
@  r1: numero de caracteres
@ retorno:
@  r0: numero binario
atoi:
    push {r4, r5, lr}
    mov r4, r0         @ r4 == endereco do buffer de caracteres
    mov r5, r1         @ r5 == numero de caracteres a ser considerado 
    mov r0, #0         @ number = 0
    mov r1, #0         @ loop indice
atoi_loop:
    cmp r1, r5         @ se indice == tamanho maximo
    beq atoi_end       @ finaliza conversao
    mov r0, r0, lsl #4 
    ldrb r2, [r4, r1]
    cmp r2, #'A'       @ identifica o caractere
    blo numero
    sub r2, r2, #'7'
    b atoi_byte_end
numero:
    sub r2, r2, #'0'
atoi_byte_end:
    orr r0, r0, r2
    add r1, r1, #1     @ indice++
    b atoi_loop
atoi_end:
    pop {r4, r5, lr}
    mov pc, lr

@ Converte um numero binario em uma sequencia de caracteres alfanumericos
@ parametros:
@  r0: endereco do buffer de memoria que recebera a sequencia de caracteres.
@  r1: numero de caracteres a ser considerado na conversao
@  r2: numero binario
itoa:
    push {r4, r5, lr}
    mov r4, r0          @ copia endereco do buffer para r4
itoa_loop:
    sub r1, r1, #1      @ decremento do indice
    cmp r1, #0          @ verifica se ainda ha bits a serem lidos
    blt itoa_end
    mov r1, r1, lsl #2  @ multiplica r1 por 4    
    and r3, r2, #0b1111, lsl r1
    mov r3, r3, lsr r1
    mov r1, r1, lsr #2  @ divide r1 por 4
    cmp r3, #10
    bhs letra
    add r3, r3, #'0'
    b itoa_byte_end    
letra:
    add r3, r3, #'7'
itoa_byte_end:
    strb r3, [r4, r1]   @ escreve caractere na memoria
    b itoa_loop
itoa_end:
    pop {r4, r5, lr}
    mov pc, lr    
