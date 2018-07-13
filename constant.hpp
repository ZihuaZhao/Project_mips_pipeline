#ifndef CONSTANT
#define CONSTANT


#include<iostream>
#include<cctype>
#include<string>
#include<vector>
#include<map>

enum func {
	_align, _ascii, _asciiz, _byte, _half, _word, _space, _data, _text,
	add, addu, addiu, sub, subu, mul, mulu,
	divv, divu, xoor, xoru, neg, negu, rem, remu,
	li, seq, sge, sgt, sle, slt, sne,
	b, beq, bne, bge, ble, bgt, blt, beqz, bnez, blez, bgez, bgtz, bltz,
	j, jr, jal, jalr, la, lb, lh, lw,
	sb, sh, sw, mov, mfhi, mflo, nop, syscall, label, mainp
};

#endif