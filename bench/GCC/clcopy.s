.intel_syntax noprefix
.data
.align 64
SCALAR:
.double 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0
.align 64
SSCALAR:
.single 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0
.align 64
ISCALAR:
.int 1, 1
.align 16
OMM:
.int 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
.align 16
IOMM:
.int 0,16,32,48,64,80,96,128,144,160,176,192,208,224,240,256
.align 16
TOMM:
.int 0,2,4,6,16,18,20,22,32,34,36,38,48,50,52,54
.text
.global clcopy
.type clcopy, @function
clcopy :
push rbp
mov rbp, rsp
push rbx
push r12
push r13
push r14
push r15
xor   rax, rax
.align 16
1:
movaps xmm0, [rsi + rax * 8 ]
movaps xmm1, [rsi + rax * 8 + 64 ]
movaps xmm2, [rsi + rax * 8 + 128 ]
movaps xmm3, [rsi + rax * 8 + 192 ]
movaps [rdx + rax * 8 ], xmm0
movaps [rdx + rax * 8 + 64 ], xmm1
movaps [rdx + rax * 8 + 128 ], xmm2
movaps [rdx + rax * 8 + 192 ], xmm3
add rax, 32
cmp rax, rdi
jl 1b

pop r15
pop r14
pop r13
pop r12
pop rbx
mov  rsp, rbp
pop rbp
ret
.size clcopy, .-clcopy


