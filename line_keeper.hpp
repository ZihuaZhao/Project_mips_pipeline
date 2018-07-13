#ifndef LINE_KEEPER
#define LINE_KEEPER


#include<string>
#include<cstring>
#include<vector>
#include<map>
#include"constant.hpp"

using namespace std;

class line_keeper {
private:
	void func_to_out(func str) {
		if (str == _align) cout << "_align";
		if (str == _ascii) cout << "_ascii";
		if (str == _asciiz) cout << "_asciiz";
		if (str == _byte) cout << "_byte";
		if (str == _half) cout << "_half";
		if (str == _word) cout << "_word";
		if (str == _space) cout << "_space";
		if (str == _data) cout << "_data";
		if (str == _text) cout << "_text";
		if (str == add) cout << "add";
		if (str == addu) cout << "addu";
		if (str == addiu) cout << "addiu";
		if (str == sub) cout << "sub";
		if (str == subu) cout << "subu";
		if (str == mul) cout << "mul";
		if (str == mulu) cout << "mulu";
		if (str == divv) cout << "divv";
		if (str == divu) cout << "divu";
		if (str == xoor) cout << "xoor";
		if (str == xoru) cout << "xoru";
		if (str == neg) cout << "neg";
		if (str == negu) cout << "negu";
		if (str == rem) cout << "rem";
		if (str == remu) cout << "remu";
		if (str == li) cout << "li";
		if (str == seq) cout << "seq";
		if (str == sge) cout << "sge";
		if (str == sle) cout << "sle";
		if (str == slt) cout << "slt";
		if (str == sne) cout << "sne";
		if (str == b) cout << "b";
		if (str == beq) cout << "beq";
		if (str == bge) cout << "bge";
		if (str == ble) cout << "ble";
		if (str == bgt) cout << "bgt";
		if (str == blt) cout << "blt";
		if (str == beqz) cout << "beqz";
		if (str == bnez) cout << "bnez";
		if (str == blez) cout << "blez";
		if (str == bgez) cout << "bgez";
		if (str == bgtz) cout << "bgtz";
		if (str == bltz) cout << "bltz";
		if (str == j) cout << "j";
		if (str == jr) cout << "jr";
		if (str == jal) cout << "jal";
		if (str == jalr) cout << "jalr";
		if (str == la) cout << "la";
		if (str == lb) cout << "lb";
		if (str == lh) cout << "lh";
		if (str == lw) cout << "lw";
		if (str == sb) cout << "sb";
		if (str == sh) cout << "sh";
		if (str == sw) cout << "sw" ;
		if (str == mov) cout << "move";
		if (str == mfhi) cout << "mfhi";
		if (str == mflo) cout << "mflo";
		if (str == nop) cout << "nop";
		if (str == syscall) cout << "syscall";
		if (str == mainp) cout << "main";
		if (str == label) cout << "label";
	}

public:
	int line_num, arg_num;
	func command;
	int Rdest = 0, Rsrc = 0, Rsrc1 = 0, Rsrc2 = 0, Src2_reg = 0;
	int Src2_dig = 0, Imm = 0, ad_reg = 0, ad_dig = 0;
	bool Src2_type = false;
	bool ad_type;
	string label_name = "";
	int true_num;

	void out000() {
		cout << true_num << " ";
		func_to_out(command);
		cout << " " << ad_dig << " " << ad_reg << " " << Rdest << " " << Rsrc << " " << Rsrc1 << " " << Rsrc2 << " " << Src2_reg << " " << Src2_dig << " "<< label_name << " " << Imm << endl;
	}
};

#endif