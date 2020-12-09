LW      x1, 0(x5)
SW      x2, 128(x3)
ADDI    x3, x4, 10
DIV     x1, x3, x1
NEG     x4, x5
JALR    x5
ADDI    x7, x1, 10
RET 

ADDI      x1, x0, 32
ADDI      x5, x0, 10
ADD       x2, x5, x1

ADDI x4, x0, 3
ADDI x2, x4, 20
ADDI x2, x2, 5
ADDI x6, x0, 6
JALR x4
ADDI x7, x0, 4
ADD x0, x0, x4
ADD x0, x0, x2