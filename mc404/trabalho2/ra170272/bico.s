.global set_motor_speed
.global set_motors_speed
.global read_sonar
.global read_sonars
.global register_proximity_callback
.global add_alarm
.global get_time
.global set_time

.align 4

@ Set Motor function
set_motor_speed:
	push {r7, lr}
	
	@ carrega o id do motor (1o byte)
	ldrb r1, [r0]
	@ carrega a velocidade do motor (2o byte)
	add r0, r0, #1
	ldrb r2, [r0]
	
	@ chama a syscall
	mov r0, r1
	mov r1, r2
	mov r7, #18
	svc 0x0

	pop {r7, lr}
	mov pc, lr
	
@ Set Motors function
set_motors_speed:
	push {r4-r7, lr}

	ldrb r4, [r0]
	ldrb r5, [r1]
	ldrb r6, [r0, #1]
	ldrb r7, [r1, #1]
	
	@ verifica qual é o motor id 0
	cmp r4, r5
	bhi set_motors_else
set_motors_then:
	mov r1, r7
	mov r0, r6
	b   set_motors_endif
set_motors_else:
	mov r1, r6
	mov r0, r7
set_motors_endif:	
	mov r7, #19
	svc 0x0

	pop {r4-r7, lr}
	mov pc, lr

@ Read Sonar function	
read_sonar:
	push {r7, lr}

	@ chama a syscall
	mov r7, #16
	svc 0x0

	pop {r7, lr}
	mov pc, lr
	
@ Read Sonars function
read_sonars:
	push {r4-r7, lr}

	@ r0-inicio  r1-fim  r2-endereco inicial do vetor
	cmp r0, r1
	bhi read_sonars_end

	
	mov r4, r0 		@ r4==indice de iteracao do sonar
	mov r5, #0		@ r5==indice de posicao no vetor de saida
read_sonars_loop:
	cmp r4, r1		@ verifica se loop chegou ao fim
	bhi read_sonars_end

	@ lê o i-esimo sonar
	mov r0, r4
	bl read_sonar
	
	@ salva o valor na i-esima posicao do vetor
	str r0, [r2, r5, lsl #2]
	
	add r5, r5, #1
	add r4, r4, #1
	b   read_sonars_loop
read_sonars_end:	
	pop {r4-r7, lr}
	mov pc, lr

@ Register Proximity function
register_proximity_callback:
    push {r7, lr}

    @ chama a syscall
    mov r7, #17
    svc 0x0

    pop {r7, lr}
    mov pc, lr

@ Add Alarm function	
add_alarm:
    push {r7, lr}

    @ chama a syscall
    mov r7, #22
    svc 0x0

    pop {r7, lr}
    mov pc, lr

@ Get Time function	
get_time:
    push {r4, r7, lr}

    mov r4, r0

    mov r7, #20
    svc 0x0

    str r0, [r4]

    pop {r4, r7, lr}
	mov pc, lr
	
@ Set Time function
set_time:
    push {r7, lr}

    mov r7, #21
    svc 0x0

    pop {r7, lr}
    mov pc, lr
