# VARIAVEIS E ESPACOS RESERVADOS

.org 0x100
I:      .word 0x9       #100
G:      .word 0xA       #101
CTE:    .word 0x1       #102
K:      .skip 0x1       #103
Y:      .skip 0x1       #104
X:      .word 0xDAC     #105

# INICIO DO PROGRAMA

.org 0X000
LOAD MQ,M(X)
MUL M(G)
LOAD MQ
STOR M(Y)
RSH
STOR M(K)

laco:
LOAD M(Y)
DIV M(K)
LOAD MQ
ADD M(K)
RSH
STOR M(K)
LOAD M(I)
SUB M(CTE)
STOR M(I)
JUMP+ M(laco)

LOAD M(K)
JUMP M(0x400)