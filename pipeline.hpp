#pragma once
#include<string>
#include<map>
#include<vector>
#include<cmath>
#include<cstring>
#include"constant.hpp"
#include"line_keeper.hpp"
#include"IF_to_ID_passer.hpp"
#include"ID_to_EX_passer.hpp"
#include"EX_to_MEM_passer.hpp"
#include"MEM_to_WB_passer.hpp"

using namespace std;

class pipeline {
private:
	IF_to_ID_passer p1;
	ID_to_EX_passer p2;
	EX_to_MEM_passer p3;
	MEM_to_WB_passer p4;

public:
	pipeline() {}
	~pipeline() {}

	bool Instruction_fetch(int* reg, vector<line_keeper>* linebase) {
		p1.cur_line = reg[34];
		if (p1.cur_line < linebase->size()) return true;
		else  return false;
	}

	void Decode(vector<line_keeper>* linebase, int* reg) {
		line_keeper line = linebase->operator[](p1.cur_line);
		//cout << line.true_num << endl;
		if (line.true_num == 680) {
			int nfvn = 0;
		}
		p2.command = line.command;
		p2.cur_line = p1.cur_line;
		p2.arg_num = line.arg_num;
		if (line.command == add || line.command == addu || line.command == sub || line.command == subu ||
			line.command == xoor || line.command == xoru || line.command == rem || line.command == remu ||
			line.command == seq || line.command == sge || line.command == sgt || line.command == sle ||
			line.command == slt || line.command == sne) {
			p2.changed_reg_num = line.Rdest;
			p2.arg1_reg = reg[line.Rsrc1];
			if (line.Src2_type) p2.arg2_reg = line.Src2_dig;
			else p2.arg2_reg = reg[line.Src2_reg];
			return;
		}
		if (line.command == addiu) {
			p2.changed_reg_num = line.Rdest;
			p2.arg1_reg = reg[line.Rsrc1];
			p2.arg2_reg = line.Imm;
			return;
		}
		if (line.command == mul || line.command == mulu) {
			if (line.arg_num == 3) {
				p2.changed_reg_num = line.Rdest;
				p2.arg1_reg = reg[line.Rsrc1];
				if (line.Src2_type) p2.arg2_reg = line.Src2_dig;
				else p2.arg2_reg = reg[line.Src2_reg];
				return;
			}
			else {
				p2.arg1_reg = reg[line.Rdest];
				if (line.Src2_type) p2.arg2_reg = line.Src2_dig;
				else p2.arg2_reg = reg[line.Src2_reg];
				return;
			}
		}
		if (line.command == divv || line.command == divu) {
			if (line.arg_num == 3) {
				p2.changed_reg_num = line.Rdest;
				p2.arg1_reg = reg[line.Rsrc1];
				if (line.Src2_type) p2.arg2_reg = line.Src2_dig;
				else p2.arg2_reg = reg[line.Src2_reg];
				return;
			}
			else {
				p2.arg1_reg = reg[line.Rsrc1];
				p2.arg2_reg = reg[line.Rsrc2];
				return;
			}
		}
		if (line.command == neg || line.command == negu || line.command == mov) {
			p2.changed_reg_num = line.Rdest;
			p2.arg1_reg = reg[line.Rsrc];
			return;
		}
		if (line.command == li) {
			p2.changed_reg_num = line.Rdest;
			p2.arg1_reg = line.Imm;
			return;
		}
		if (line.command == b || line.command == j || line.command == jal) {
			p2.label_name = line.label_name;
			return;
		}
		if (line.command == beq || line.command == bne || line.command == bge ||
			line.command == ble || line.command == bgt || line.command == blt) {
			p2.arg1_reg = reg[line.Rsrc1];
			if (line.Src2_type) p2.arg2_reg = line.Src2_dig;
			else p2.arg2_reg = reg[line.Src2_reg];
			p2.label_name = line.label_name;
			return;
		}
		if (line.command == beqz || line.command == bnez || line.command == blez ||
			line.command == bgez || line.command == bgtz || line.command == bltz) {
			p2.arg1_reg = reg[line.Rsrc];
			p2.label_name = line.label_name;
			return;
		}
		if (line.command == jr || line.command == jalr) {
			p2.arg1_reg = reg[line.Rsrc];
			return;
		}
		if (line.command == la || line.command == lb ||
			line.command == lh || line.command == lw) {
			p2.changed_reg_num = line.Rdest;
			p2.ad_type = line.ad_type;
			if (line.ad_type) {
				p2.label_name = line.label_name;
				return;
			}
			else {
				p2.arg1_reg = reg[line.ad_reg] + line.ad_dig;
				return;
			}
		}
		if (line.command == sb || line.command == sh || line.command == sw) {
			p2.arg1_reg = reg[line.Rsrc];
			p2.ad_type = line.ad_type;
			if (line.ad_type) {
				p2.label_name = line.label_name;
				return;
			}
			else {
				p2.arg2_reg = reg[line.ad_reg] + line.ad_dig;
				return;
			}
		}
		if (line.command == mfhi || line.command == mflo) {
			p2.changed_reg_num = line.Rdest;
			return;
		}
		if (line.command == nop) {
			return;
		}
		if (line.command == syscall) {
			p2.arg1_reg = reg[4];
			p2.arg2_reg = reg[2];
			p2.arg3_reg = reg[5];
		}
	}

	void Execution(map<string, int>* database, map<string, int>* funcbase) {
		p3.cur_line = p2.cur_line;
		p3.command = p2.command;
		p3.arg_num = p2.arg_num;
		p3.arg1_reg = p2.arg1_reg;
		p3.arg2_reg = p2.arg2_reg;
		p3.arg3_reg = p2.arg3_reg;
		p3.label_name = p2.label_name;
		p3.changed_reg_num = p2.changed_reg_num;
		p3.ad_type = p2.ad_type;
		if (p3.command == add) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = p2.arg1_reg + p2.arg2_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == addu || p3.command == addiu) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = (unsigned int)p2.arg1_reg + (unsigned int)p2.arg2_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == sub) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = p2.arg1_reg - p2.arg2_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == subu) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = (unsigned int)p2.arg1_reg - (unsigned int)p2.arg2_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == mul) {
			if (p3.arg_num == 3) {
				p3.changed_reg_num = p2.changed_reg_num;
				p3.changed_reg = p2.arg1_reg * p2.arg2_reg;
				p3.next_line = p3.cur_line + 1;
				return;
			}
			else {
				p3.reg32 = p2.arg1_reg * p2.arg2_reg >> 32;
				p3.reg33 = p2.arg1_reg * p2.arg2_reg & (0xffffffff);
				p3.next_line = p3.cur_line + 1;
				return;
			}
		}
		if (p3.command == mulu) {
			if (p3.arg_num == 3) {
				p3.changed_reg_num = p2.changed_reg_num;
				p3.changed_reg = (unsigned int)p2.arg1_reg * (unsigned int)p2.arg2_reg;
				p3.next_line = p3.cur_line + 1;
				return;
			}
			else {
				p3.reg32 = (unsigned int)p2.arg1_reg * (unsigned int)p2.arg2_reg >> 32;
				p3.reg33 = (unsigned int)p2.arg1_reg * (unsigned int)p2.arg2_reg & (0xffffffff);
				p3.next_line = p3.cur_line + 1;
				return;
			}
		}
		if (p3.command == divv) {
			if (p3.arg_num == 3) {
				p3.changed_reg_num = p2.changed_reg_num;
				p3.changed_reg = p2.arg1_reg / p2.arg2_reg;
				p3.next_line = p3.cur_line + 1;
				return;
			}
			else {
				p3.reg32 = p2.arg1_reg % p2.arg2_reg;
				p3.reg33 = p2.arg1_reg / p2.arg2_reg;
				p3.next_line = p3.cur_line + 1;
				return;
			}
		}
		if (p3.command == divu) {
			if (p3.arg_num == 3) {
				p3.changed_reg_num = p2.changed_reg_num;
				p3.changed_reg = (unsigned int)p2.arg1_reg / (unsigned int)p2.arg2_reg;
				p3.next_line = p3.cur_line + 1;
				return;
			}
			else {
				p3.reg32 = (unsigned int)p2.arg1_reg % (unsigned int)p2.arg2_reg;
				p3.reg33 = (unsigned int)p2.arg1_reg / (unsigned int)p2.arg2_reg;
				p3.next_line = p3.cur_line + 1;
				return;
			}
		}
		if (p3.command == xoor) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = p2.arg1_reg ^ p2.arg2_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == xoru) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = (unsigned int)p2.arg1_reg ^ (unsigned int)p2.arg2_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == neg) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = -p2.arg1_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == negu) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = ~(unsigned int)p2.arg1_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == rem) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = p2.arg1_reg % p2.arg2_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == remu) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = (unsigned int)p2.arg1_reg % (unsigned int)p2.arg2_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == li) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = p2.arg1_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == seq) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = (p2.arg1_reg == p2.arg2_reg);
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == sge) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = (p2.arg1_reg >= p2.arg2_reg);
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == sgt) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = (p2.arg1_reg > p2.arg2_reg);
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == sle) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = (p2.arg1_reg <= p2.arg2_reg);
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == slt) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = (p2.arg1_reg < p2.arg2_reg);
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == sne) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = (p2.arg1_reg != p2.arg2_reg);
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == b || p3.command == j) {
			p3.next_line = funcbase->operator[](p2.label_name);
			return;
		}
		if (p3.command == beq) {
			if (p2.arg1_reg == p2.arg2_reg) p3.next_line = funcbase->operator[](p2.label_name);
			else p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == bne) {
			if (p2.arg1_reg != p2.arg2_reg) p3.next_line = funcbase->operator[](p2.label_name);
			else p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == bge) {
			if (p2.arg1_reg >= p2.arg2_reg) p3.next_line = funcbase->operator[](p2.label_name);
			else p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == ble) {
			if (p2.arg1_reg <= p2.arg2_reg) p3.next_line = funcbase->operator[](p2.label_name);
			else p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == bgt) {
			if (p2.arg1_reg > p2.arg2_reg) p3.next_line = funcbase->operator[](p2.label_name);
			else p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == blt) {
			if (p2.arg1_reg < p2.arg2_reg) p3.next_line = funcbase->operator[](p2.label_name);
			else p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == beqz) {
			if (p2.arg1_reg == 0) p3.next_line = funcbase->operator[](p2.label_name);
			else p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == bnez) {
			if (p2.arg1_reg != 0) p3.next_line = funcbase->operator[](p2.label_name);
			else p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == blez) {
			if (p2.arg1_reg <= 0) p3.next_line = funcbase->operator[](p2.label_name);
			else p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == bgez) {
			if (p2.arg1_reg >= 0) p3.next_line = funcbase->operator[](p2.label_name);
			else p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == bgtz) {
			if (p2.arg1_reg > 0) p3.next_line = funcbase->operator[](p2.label_name);
			else p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == bltz) {
			if (p2.arg1_reg < 0) p3.next_line = funcbase->operator[](p2.label_name);
			else p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == jr) {
			p3.next_line = p2.arg1_reg;
			return;
		}
		if (p3.command == jal) {
			p3.reg31 = p3.cur_line + 1;
			p3.next_line = funcbase->operator[](p2.label_name);
			return;
		}
		if (p3.command == jalr) {
			p3.reg31 = p3.cur_line + 1;
			p3.next_line = p2.arg1_reg;
			return;
		}
		if (p3.command == nop) {
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == mov) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = p2.arg1_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == mfhi) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = p2.arg1_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
		if (p3.command == mflo) {
			p3.changed_reg_num = p2.changed_reg_num;
			p3.changed_reg = p2.arg1_reg;
			p3.next_line = p3.cur_line + 1;
			return;
		}
	}

	void Memery_access(map<string, int>* database, map<string, int>* funcbase, char* vir_mem, int& heap_seg, int& static_seg, int& stack_seg) {
		p4.command = p3.command;
		p4.cur_line = p3.cur_line;
		p4.next_line = p3.next_line;
		p4.changed_reg_num = p3.changed_reg_num;
		p4.changed_reg = p3.changed_reg;
		p4.reg31 = p3.reg31;
		p4.reg32 = p3.reg32;
		p4.reg33 = p3.reg33;
		p4.arg_num = p3.arg_num;
		if (p4.command == la) {
			p4.changed_reg_num = p3.changed_reg_num;
			p4.changed_reg = database->operator[](p3.label_name);
			p4.next_line = p4.cur_line + 1;
			return;
		}
		if (p4.command == lb) {
			if (p3.ad_type) {
				int pos = database->operator[](p3.label_name);
				p4.changed_reg_num = p3.changed_reg_num;
				p4.changed_reg = 0;
				memcpy(&p4.changed_reg, &vir_mem[pos], 1);
				p4.next_line = p4.cur_line + 1;
				return;
			}
			else {
				int pos = p3.arg1_reg;
				p4.changed_reg_num = p3.changed_reg_num;
				p4.changed_reg = 0;
				memcpy(&p4.changed_reg, &vir_mem[pos], 1);
				p4.next_line = p4.cur_line + 1;
				return;
			}
		}
		if (p4.command == lh) {
			if (p3.ad_type) {
				int pos = database->operator[](p3.label_name);
				p4.changed_reg_num = p3.changed_reg_num;
				p4.changed_reg = 0;
				memcpy(&p4.changed_reg, &vir_mem[pos], 2);
				p4.next_line = p4.cur_line + 1;
				return;
			}
			else {
				int pos = p3.arg1_reg;
				p4.changed_reg_num = p3.changed_reg_num;
				p4.changed_reg = 0;
				memcpy(&p4.changed_reg, &vir_mem[pos], 2);
				p4.next_line = p4.cur_line + 1;
				return;
			}
		}
		if (p4.command == lw) {
			if (p3.ad_type) {
				int pos = database->operator[](p3.label_name);
				p4.changed_reg_num = p3.changed_reg_num;
				memcpy(&p4.changed_reg, &vir_mem[pos], 4);
				p4.next_line = p4.cur_line + 1;
				return;
			}
			else {
				int pos = p3.arg1_reg;
				p4.changed_reg_num = p3.changed_reg_num;
				memcpy(&p4.changed_reg, &vir_mem[pos], 4);
				p4.next_line = p4.cur_line + 1;
				return;
			}
		}
		if (p4.command == sb) {
			if (p3.ad_type) {
				int pos = database->operator[](p3.label_name);
				memcpy(&vir_mem[pos], &p3.arg1_reg, 1);
				p4.next_line = p4.cur_line + 1;
				return;
			}
			else {
				int pos = p3.arg2_reg;
				memcpy(&vir_mem[pos], &p3.arg1_reg, 1);
				p4.next_line = p4.cur_line + 1;
				return;
			}
		}
		if (p4.command == sh) {
			if (p3.ad_type) {
				int pos = database->operator[](p3.label_name);
				memcpy(&vir_mem[pos], &p3.arg1_reg, 2);
				p4.next_line = p4.cur_line + 1;
				return;
			}
			else {
				int pos = p3.arg2_reg;
				memcpy(&vir_mem[pos], &p3.arg1_reg, 2);
				p4.next_line = p4.cur_line + 1;
				return;
			}
		}
		if (p4.command == sw) {
			if (p3.ad_type) {
				int pos = database->operator[](p3.label_name);
				memcpy(&vir_mem[pos], &p3.arg1_reg, 4);
				p4.next_line = p4.cur_line + 1;
				return;
			}
			else {
				int pos = p3.arg2_reg;
				memcpy(&vir_mem[pos], &p3.arg1_reg, 4);
				p4.next_line = p4.cur_line + 1;
				return;
			}
		}
		if (p4.command == syscall) {
			if (p3.arg2_reg == 1) {
				p4.syscall_type = 1;
				cout << p3.arg1_reg;
				p4.next_line = p4.cur_line + 1;
				return;
			}
			if (p3.arg2_reg == 4) {
				p4.syscall_type = 4;
				int a = p3.arg1_reg;
				for (int i = a;; ++i) {
					if (vir_mem[i] == '\0') break;
					cout << vir_mem[i];
				}
				p4.next_line = p4.cur_line + 1;
				return;
			}
			if (p3.arg2_reg == 5) {
				p4.syscall_type = 5;
				cin >> p4.changed_reg;
				p4.changed_reg_num = 2;
				p4.next_line = p4.cur_line + 1;
				return;
			}
			if (p3.arg2_reg == 8) {
				p4.syscall_type = 8;
				string str;
				cin >> str;
				int x;
				if (str.size() <= (p3.arg3_reg + 1)) x = str.size();
				else x = p3.arg3_reg + 1;
				for (int i = 0; i < x; ++i) {
					vir_mem[p3.arg1_reg + i] = str[i];
				}
				p4.next_line = p4.cur_line + 1;
				return;
			}
			if (p3.arg2_reg == 9) {
				p4.syscall_type = 9;
				int x = p3.arg1_reg;
				p4.changed_reg = heap_seg;
				p4.changed_reg_num = 2;
				heap_seg += x;
				while (heap_seg % 4 != 0) heap_seg += 1;
				p4.next_line = p4.cur_line + 1;
				return;
			}
			if (p3.arg2_reg == 10) {
				//system("PAUSE");
				p4.syscall_type = 10;
				exit(0);
				p4.next_line = p4.cur_line + 1;
				return;
			}
			if (p3.arg2_reg == 17) {
				//system("PAUSE");
				p4.syscall_type = 17;
				exit(p4.arg1_reg);
				p4.next_line = p4.cur_line + 1;
				return;
			}
		}
	}

	void Write_back(int * reg) {
		reg[34] = p4.next_line;
		if (p4.command == add || p4.command == addu || p4.command == addiu || p4.command == sub || p4.command == subu ||
			p4.command == xoor || p4.command == xoru || p4.command == neg || p4.command == negu || p4.command == rem || p4.command == remu ||
			p4.command == li || p4.command == seq || p4.command == sge || p4.command == sgt || p4.command == sle ||
			p4.command == slt || p4.command == sne || p4.command == mov) {
			reg[p4.changed_reg_num] = p4.changed_reg;
		}
		if (p4.command == mul || p4.command == mulu || p4.command == divv || p4.command == divu) {
			if (p4.arg_num == 3) {
				reg[p4.changed_reg_num] = p4.changed_reg;
			}
			else {
				reg[32] = p4.reg32;
				reg[33] = p4.reg33;
			}
		}
		if (p4.command == b || p4.command == beq || p4.command == bne || p4.command == bge || p4.command == ble || p4.command == bgt ||
			p4.command == blt || p4.command == beqz || p4.command == bnez || p4.command == blez || p4.command == bgez || p4.command == bgtz ||
			p4.command == bltz || p4.command == j || p4.command == jr) {
			return;
		}
		if (p4.command == jal || p4.command == jalr) {
			reg[31] = p4.reg31;
		}
		if (p4.command == la || p4.command == lb || p4.command == lw || p4.command == lh) {
			reg[p4.changed_reg_num] = p4.changed_reg;
		}
		if (p4.command == sw || p4.command == sh || p4.command == sb) {
			return;
		}
		if (p4.command == mflo) {
			reg[p4.changed_reg_num] = reg[33];
			return;
		}
		if (p4.command == mfhi) {
			reg[p4.changed_reg_num] = reg[32];
			return;
		}
		if (p4.command == syscall) {
			if (p4.syscall_type == 1) {
				return;
			}
			if (p4.syscall_type == 4) {
				return;
			}
			if (p4.syscall_type == 5) {
				reg[p4.changed_reg_num] = p4.changed_reg;
				return;
			}
			if (p4.syscall_type == 8) {
				return;
			}
			if (p4.syscall_type == 9) {
				reg[p4.changed_reg_num] = p4.changed_reg;
				return;
			}
			if (p4.syscall_type == 10 || p4.syscall_type == 17) {
				return;
			}
		}
	}

	bool execute(int* reg , map<string, int>* database, map<string, int>* funcbase, vector<line_keeper>* linebase, char* vir_mem, int& heap_seg, int& static_seg, int& stack_seg) {
		if (Instruction_fetch(reg, linebase)) {
			Decode(linebase, reg);
			Execution(database, funcbase);
			Memery_access(database, funcbase, vir_mem, heap_seg, static_seg, stack_seg);
			Write_back(reg);
			return true;
		}
		else return false;
	}
};