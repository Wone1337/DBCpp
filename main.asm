
section .text

;---------------------------CIN---------------------------
CIN:

PUSH RAX
PUSH RDI
PUSH RSI
PUSH RDX
PUSH RCX

MOV RAX , 0

MOV RDI , 0

MOV RSI , buffer

MOV RDX , 0x64

SYSCALL

POP RCX
POP RDX
POP RSI
POP RDI
POP RAX

RET

;---------------------------COUT--------------------------------

COUT:

PUSH RAX
PUSH RDI
PUSH RSI
PUSH RDX
PUSH RCX

MOV RAX , 1

MOV RDI , 1

MOV RSI , buffer

MOV RDX , 0x64

SYSCALL

POP RCX
POP RDX
POP RSI
POP RDI
POP RAX

RET
 

;---------------------------STR_TO_INT---------------------------
STR_TO_INT: 

PUSH RAX
PUSH RBX
PUSH RSI

XOR RAX , RAX 

XOR RBX , RBX 

MOV RSI , buffer

MINI_LOOP:

MOV BL , [RSI]

CMP BL , '0'

JB IDONE

CMP BL , '9'

JA IDONE

SUB BL ,  '0'

IMUL RAX , 10

ADD  RAX , RBX

INC RSI

JMP MINI_LOOP

IDONE:

MOV [buffer] , RAX 

POP RSI
POP RBX
POP RAX

RET

;---------------------------INT_TO_STR---------------------------

INT_TO_STR: ;TODO: переделать



RET

;---------------------------CALL_EXIT----------------------------

CALL_EXIT:

XOR RAX , RAX

XOR RBX , RBX

MOV RAX ,  60

MOV RDI ,  0

SYSCALL


;---------------------------MAIN--------------------------------
global _start

_start:

CALL CIN

CALL STR_TO_INT

;MOV RBX , [buffer]

;MOV [biba] , RBX

ADD RBX , [buffer]

CALL CIN

CALL STR_TO_INT

ADD RBX , [buffer]
;MOV RBX , [buffer]

;MOV [boba] , RBX



;ADD RBX , [biba]

;ADD RBX , [boba]

MOV [buffer] , RBX

XOR RBX , RBX

CALL INT_TO_STR

CALL COUT

CALL CALL_EXIT









section .data

section .bss

buffer resb 100




;1)
;Задача: сложить два 32-разрядных числа, 
;содержащихся в переменных number1 и number 2 , а результат сохранить в переменной result.
;2)
;Задача: сложить два 32-битных числа. Регистр EDI содержит указатель на
;первое слагаемое, второе слагаемое расположено непосредственно за первым.
;Результат записать в EDX .
;3)
;Задача: вычислить сумму массива 8 -разрядных чисел, если в ESI загружен
;адрес первого элемента массива. Массив заканчивается нулевым байтом.
;4)
;Задача: определить, четное или нечетное значение содержит регистр АХ.
;5)
;Задача: реверсируем порядок битов числа, сохраненного в AL, то есть пере­ставим 
;младший бит на место старшего, второй справа — на место второго
;слева и т.д. Полученный результат сохраним в АН .
;6)
;Задача: определить, заканчивается ли десятичная запись числа цифрой
;нуль.
;
;
;
;
;