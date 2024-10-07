
section .data   

section .bss    

section .text   

SUM: 

PUSH RAX;

ADD RAX,RBX;

MOV RCX,RAX;

POP RAX;

RET


global _start 
_start:  


MOV RAX, 0x08

MOV RBX, 0x02

CALL SUM;

MOV EAX , 0x0A














