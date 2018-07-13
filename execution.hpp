#pragma once
#include<string>
#include<map>
#include<vector>
#include<cmath>
#include<cstring>
#include"constant.hpp"
#include"line_keeper.hpp"

using namespace std;

class execution {
public:
	void execute(map<string, int>*database, map<string, int>*funcbase, vector<line_keeper>*linebase,
		int*reg, int& mainpos, char*vir_mem, int& static_seg, int& heap_seg, int& stack_seg) {
		int n = mainpos;
		while (n < linebase->size()) {
			line_keeper line = linebase->operator[](n);
			if (line.command == add) {
				if (line.Src2_type) {
					reg[line.Rdest] = reg[line.Rsrc1] + line.Src2_dig;
				}
				else {
					reg[line.Rdest] = reg[line.Rsrc1] + reg[line.Src2_reg];
				}
				n++;
				continue;
			}
			if (line.command == addu) {
				if (line.Src2_type) {
					reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] + (unsigned int)line.Src2_dig;
				}
				else {
					reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] + (unsigned int)reg[line.Src2_reg];
				}
				n++;
				continue;
			}
			if (line.command == addiu) {
				reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] + (unsigned int)line.Imm;
				n++;
				continue;
			}
			if (line.command == sub) {
				if (line.Src2_type) {
					reg[line.Rdest] = reg[line.Rsrc1] - line.Src2_dig;
				}
				else {
					reg[line.Rdest] = reg[line.Rsrc1] - reg[line.Src2_reg];
				}
				n++;
				continue;
			}
			if (line.command == subu) {
				if (line.Src2_type) {
					reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] - (unsigned int)line.Src2_dig;
				}
				else {
					reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] - (unsigned int)reg[line.Src2_reg];
				}
				n++;
				continue;
			}
			if (line.command == mul) {
				if (line.arg_num == 3) {
					if (line.Src2_type) {
						reg[line.Rdest] = reg[line.Rsrc1] * line.Src2_dig;
					}
					else {
						reg[line.Rdest] = reg[line.Rsrc1] * reg[line.Src2_reg];
					}
				}
				else {
					if (line.Src2_type) {
						int a = (reg[line.Rdest] * line.Src2_dig) & (0xffffffff);
						int b = (reg[line.Rdest] * line.Src2_dig) >> 32;
						reg[32] = b;
						reg[33] = a;
					}
					else {
						int a = (reg[line.Rdest] * reg[line.Src2_reg]) & (0xffffffff);
						int b = (reg[line.Rdest] * reg[line.Src2_reg]) >> 32;
						reg[32] = b;
						reg[33] = a;
					}
				}
				n++;
				continue;
			}
			if (line.command == mulu) {
				if (line.arg_num == 3) {
					if (line.Src2_type) {
						reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] * (unsigned int)line.Src2_dig;
					}
					else {
						reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] * (unsigned int)reg[line.Src2_reg];
					}
				}
				else {
					if (line.Src2_type) {
						int a = (unsigned int)reg[line.Rdest] * (unsigned int)line.Src2_dig & (0xffffffff);
						int b = (unsigned int)reg[line.Rdest] * (unsigned int)line.Src2_dig >> 32;
						reg[32] = b;
						reg[33] = a;
					}
					else {
						int a = (unsigned int)reg[line.Rdest] * (unsigned int)reg[line.Src2_reg] & (0xffffffff);
						int b = (unsigned int)reg[line.Rdest] * (unsigned int)reg[line.Src2_reg] >> 32;
						reg[32] = b;
						reg[33] = a;
					}
				}
				n++;
				continue;
			}
			if (line.command == divv) {
				if (line.arg_num == 3) {
					if (line.Src2_type) {
						reg[line.Rdest] = reg[line.Rsrc1] / line.Src2_dig;
					}
					else {
						reg[line.Rdest] = reg[line.Rsrc1] / reg[line.Src2_reg];
					}
				}
				else {
					int a = reg[line.Rsrc1] / reg[line.Rsrc2];
					int b = reg[line.Rsrc1] % reg[line.Rsrc2];
					reg[32] = b;
					reg[33] = a;
				}
				n++;
				continue;
			}
			if (line.command == divu) {
				if (line.arg_num == 3) {
					if (line.Src2_type) {
						reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] / (unsigned int)line.Src2_dig;
					}
					else {
						reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] / (unsigned int)reg[line.Src2_reg];
					}
				}
				else {
					if (line.Src2_type) {
						int a = (unsigned int)reg[line.Rsrc1] / (unsigned int)line.Src2_dig;
						int b = (unsigned int)reg[line.Rsrc1] % (unsigned int)line.Src2_dig;
						reg[32] = b;
						reg[33] = a;
					}
					else {
						int a = (unsigned int)reg[line.Rsrc1] / (unsigned int)reg[line.Src2_reg];
						int b = (unsigned int)reg[line.Rsrc1] % (unsigned int)reg[line.Src2_reg];
						reg[32] = b;
						reg[33] = a;
					}
				}
				n++;
				continue;
			}
			if (line.command == xoor) {
				if (line.Src2_type) {
					reg[line.Rdest] = reg[line.Rsrc1] ^ line.Src2_dig;
				}
				else {
					reg[line.Rdest] = reg[line.Rsrc1] ^ reg[line.Src2_reg];
				}
				n++;
				continue;
			}
			if (line.command == xoru) {
				if (line.Src2_type) {
					reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] ^ (unsigned int)line.Src2_dig;
				}
				else {
					reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] ^ (unsigned int)reg[line.Src2_reg];
				}
				n++;
				continue;
			}
			if (line.command == neg) {
				reg[line.Rdest] = -reg[line.Rsrc];
				n++;
				continue;
			}
			if (line.command == negu) {
				reg[line.Rdest] = ~(unsigned int)reg[line.Rsrc];
				n++;
				continue;
			}
			if (line.command == rem) {
				if (line.Src2_type) {
					reg[line.Rdest] = reg[line.Rsrc1] % line.Src2_dig;
				}
				else {
					reg[line.Rdest] = reg[line.Rsrc1] % reg[line.Src2_reg];
				}
				n++;
				continue;
			}
			if (line.command == remu) {
				if (line.Src2_type) {
					reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] % (unsigned int)line.Src2_dig;
				}
				else {
					reg[line.Rdest] = (unsigned int)reg[line.Rsrc1] % (unsigned int)reg[line.Src2_reg];
				}
				n++;
				continue;
			}
			if (line.command == li) {
				reg[line.Rdest] = line.Imm;
				n++;
				continue;
			}
			if (line.command == seq) {
				if (line.Src2_type) {
					if (reg[line.Rsrc1] == line.Src2_dig) {
						reg[line.Rdest] = 1;
					}
					else {
						reg[line.Rdest] = 0;
					}
				}
				else {
					if (reg[line.Rsrc1] == reg[line.Src2_reg]) {
						reg[line.Rdest] = 1;
					}
					else {
						reg[line.Rdest] = 0;
					}
				}
				n++;
				continue;
			}
			if (line.command == sge) {
				if (line.Src2_type) {
					if (reg[line.Rsrc1] >= line.Src2_dig) {
						reg[line.Rdest] = 1;
					}
					else {
						reg[line.Rdest] = 0;
					}
				}
				else {
					if (reg[line.Rsrc1] >= reg[line.Src2_reg]) {
						reg[line.Rdest] = 1;
					}
					else {
						reg[line.Rdest] = 0;
					}
				}
				n++;
				continue;
			}
			if (line.command == sgt) {
				if (line.Src2_type) {
					if (reg[line.Rsrc1] > line.Src2_dig) {
						reg[line.Rdest] = 1;
					}
					else {
						reg[line.Rdest] = 0;
					}
				}
				else {
					if (reg[line.Rsrc1] > reg[line.Src2_reg]) {
						reg[line.Rdest] = 1;
					}
					else {
						reg[line.Rdest] = 0;
					}
				}
				n++;
				continue;
			}
			if (line.command == sle) {
				if (line.Src2_type) {
					if (reg[line.Rsrc1] <= line.Src2_dig) {
						reg[line.Rdest] = 1;
					}
					else {
						reg[line.Rdest] = 0;
					}
				}
				else {
					if (reg[line.Rsrc1] <= reg[line.Src2_reg]) {
						reg[line.Rdest] = 1;
					}
					else {
						reg[line.Rdest] = 0;
					}
				}
				n++;
				continue;
			}
			if (line.command == slt) {
				if (line.Src2_type) {
					if (reg[line.Rsrc1] < line.Src2_dig) {
						reg[line.Rdest] = 1;
					}
					else {
						reg[line.Rdest] = 0;
					}
				}
				else {
					if (reg[line.Rsrc1] < reg[line.Src2_reg]) {
						reg[line.Rdest] = 1;
					}
					else {
						reg[line.Rdest] = 0;
					}
				}
				n++;
				continue;
			}
			if (line.command == sne) {
				if (line.Src2_type) {
					if (reg[line.Rsrc1] != line.Src2_dig) {
						reg[line.Rdest] = 1;
					}
					else {
						reg[line.Rdest] = 0;
					}
				}
				else {
					if (reg[line.Rsrc1] != reg[line.Src2_reg]) {
						reg[line.Rdest] = 1;
					}
					else {
						reg[line.Rdest] = 0;
					}
				}
				n++;
				continue;
			}
			if (line.command == b || line.command == j) {
				n = funcbase->operator[](line.label_name);
				continue;
			}
			if (line.command == beq) {
				if (line.Src2_type) {
					if (reg[line.Rsrc1] == line.Src2_dig) {
						n = funcbase->operator[](line.label_name);
						continue;
					}
					else {
						n++;
						continue;
					}
				}
				else {
					if (reg[line.Rsrc1] == reg[line.Src2_reg]) {
						n = funcbase->operator[](line.label_name);
						continue;
					}
					else {
						n++;
						continue;
					}
				}
			}
			if (line.command == bne) {
				if (line.Src2_type) {
					if (reg[line.Rsrc1] != line.Src2_dig) {
						n = funcbase->operator[](line.label_name);
						continue;
					}
					else {
						n++;
						continue;
					}
				}
				else {
					if (reg[line.Rsrc1] != reg[line.Src2_reg]) {
						n = funcbase->operator[](line.label_name);
						continue;
					}
					else {
						n++;
						continue;
					}
				}
			}
			if (line.command == bge) {
				if (line.Src2_type) {
					if (reg[line.Rsrc1] >= line.Src2_dig) {
						n = funcbase->operator[](line.label_name);
						continue;
					}
					else {
						n++;
						continue;
					}
				}
				else {
					if (reg[line.Rsrc1] >= reg[line.Src2_reg]) {
						n = funcbase->operator[](line.label_name);
						continue;
					}
					else {
						n++;
						continue;
					}
				}
			}
			if (line.command == ble) {
				if (line.Src2_type) {
					if (reg[line.Rsrc1] <= line.Src2_dig) {
						n = funcbase->operator[](line.label_name);
						continue;
					}
					else {
						n++;
						continue;
					}
				}
				else {
					if (reg[line.Rsrc1] <= reg[line.Src2_reg]) {
						n = funcbase->operator[](line.label_name);
						continue;
					}
					else {
						n++;
						continue;
					}
				}
			}
			if (line.command == bgt) {
				if (line.Src2_type) {
					if (reg[line.Rsrc1] > line.Src2_dig) {
						n = funcbase->operator[](line.label_name);
						continue;
					}
					else {
						n++;
						continue;
					}
				}
				else {
					if (reg[line.Rsrc1] > reg[line.Src2_reg]) {
						n = funcbase->operator[](line.label_name);
						continue;
					}
					else {
						n++;
						continue;
					}
				}
			}
			if (line.command == blt) {
				if (line.Src2_type) {
					if (reg[line.Rsrc1] < line.Src2_dig) {
						n = funcbase->operator[](line.label_name);
						continue;
					}
					else {
						n++;
						continue;
					}
				}
				else {
					if (reg[line.Rsrc1] < reg[line.Src2_reg]) {
						n = funcbase->operator[](line.label_name);
						continue;
					}
					else {
						n++;
						continue;
					}
				}
			}
			if (line.command == beqz) {
				if (reg[line.Rsrc] == 0) {
					n = funcbase->operator[](line.label_name);
					continue;
				}
				else {
					n++;
					continue;
				}
			}
			if (line.command == bnez) {
				if (reg[line.Rsrc] != 0) {
					n = funcbase->operator[](line.label_name);
					continue;
				}
				else {
					n++;
					continue;
				}
			}
			if (line.command == blez) {
				if (reg[line.Rsrc] <= 0) {
					n = funcbase->operator[](line.label_name);
					continue;
				}
				else {
					n++;
					continue;
				}
			}
			if (line.command == bgez) {
				if (reg[line.Rsrc] >= 0) {
					n = funcbase->operator[](line.label_name);
					continue;
				}
				else {
					n++;
					continue;
				}
			}
			if (line.command == bgtz) {
				if (reg[line.Rsrc] > 0) {
					n = funcbase->operator[](line.label_name);
					continue;
				}
				else {
					n++;
					continue;
				}
			}
			if (line.command == bltz) {
				if (reg[line.Rsrc] < 0) {
					n = funcbase->operator[](line.label_name);
					continue;
				}
				else {
					n++;
					continue;
				}
			}
			if (line.command == jr) {
				n = reg[line.Rsrc];
				continue;
			}
			if (line.command == jal) {
				reg[31] = n + 1;
				n = funcbase->operator[](line.label_name);
				continue;
			}
			if (line.command == jalr) {
				reg[31] = n + 1;
				n = reg[line.Rsrc];
				continue;
			}
			if (line.command == la) {
				reg[line.Rdest] = database->operator[](line.label_name);
				n++;
				continue;
			}
			if (line.command == lb) {
				if (line.ad_type) {
					int pos = database->operator[](line.label_name);
					reg[line.Rdest] = 0;
					memcpy(&reg[line.Rdest], &vir_mem[pos], 1);
					n++;
					continue;
				}
				else {
					int pos = reg[line.ad_reg] + line.ad_dig;
					reg[line.Rdest] = 0;
					memcpy(&reg[line.Rdest], &vir_mem[pos], 1);
					n++;;
					continue;
				}
			}
			if (line.command == lh) {
				if (line.ad_type) {
					int pos = database->operator[](line.label_name);
					reg[line.Rdest] = 0;
					memcpy(&reg[line.Rdest], &vir_mem[pos], 2);
					n++;
					continue;
				}
				else {
					int pos = reg[line.ad_reg] + line.ad_dig;
					reg[line.Rdest] = 0;
					memcpy(&reg[line.Rdest], &vir_mem[pos], 2);
					n++;;
					continue;
				}
			}
			if (line.command == lw) {
				if (line.ad_type) {
					int pos = database->operator[](line.label_name);
					memcpy(&reg[line.Rdest], &vir_mem[pos], 4);
					n++;
					continue;
				}
				else {
					int pos = reg[line.ad_reg] + line.ad_dig;
					memcpy(&reg[line.Rdest], &vir_mem[pos], 4);
					n++;;
					continue;
				}
			}
			if (line.command == sb) {
				if (line.ad_type) {
					int pos = database->operator[](line.label_name);
					memcpy(&vir_mem[pos], &reg[line.Rsrc], 1);
					n++;
					continue;
				}
				else {
					int pos = reg[line.ad_reg] + line.ad_dig;
					memcpy(&vir_mem[pos], &reg[line.Rsrc], 1);
					n++;
					continue;
				}
			}
			if (line.command == sh) {
				if (line.ad_type) {
					int pos = database->operator[](line.label_name);
					memcpy(&vir_mem[pos], &reg[line.Rsrc], 2);
					n++;
					continue;
				}
				else {
					int pos = reg[line.ad_reg] + line.ad_dig;
					memcpy(&vir_mem[pos], &reg[line.Rsrc], 2);
					n++;
					continue;
				}
			}
			if (line.command == sw) {
				if (line.ad_type) {
					int pos = database->operator[](line.label_name);
					memcpy(&vir_mem[pos], &reg[line.Rsrc], 4);
					n++;
					continue;
				}
				else {
					int pos = reg[line.ad_reg] + line.ad_dig;
					memcpy(&vir_mem[pos], &reg[line.Rsrc], 4);
					n++;
					continue;
				}
			}
			if (line.command == mov) {
				reg[line.Rdest] = reg[line.Rsrc];
				n++;
				continue;
			}
			if (line.command == mfhi) {
				reg[line.Rdest] = reg[32];
				n++;
				continue;
			}
			if (line.command == mflo) {
				reg[line.Rdest] = reg[33];
				n++;
				continue;
			}
			if (line.command == nop) {
				n++;
				continue;
			}
			if (line.command == syscall) {
				if (reg[2] == 1) {
					cout << reg[4];
					n++;
					continue;
				}
				if (reg[2] == 4) {
					int a = reg[4];
					for (int i = a;; ++i) {
						if (vir_mem[i] == '\0') break;
						cout << vir_mem[i];
					}
					n++;
					continue;
				}
				if (reg[2] == 5) {
					cin >> reg[2];
					n++;
					continue;
				}
				if (reg[2] == 8) {
					string str;
					cin >> str;
					int x;
					if (str.size() <= (reg[5] + 1)) x = str.size();
					else x = reg[5] + 1;
					for (int i = 0; i < x; ++i) {
						vir_mem[reg[4] + i] = str[i];
					}
					n++;
					continue;
				}
				if (reg[2] == 9) {
					int x = reg[4];
					reg[2] = heap_seg;
					heap_seg += x;
					while (heap_seg % 4 != 0) heap_seg += 1;
					n++;
					continue;
				}
				if (reg[2] == 10) {
					//system("PAUSE");
					exit(0);
					n++;
					continue;
				}
				if (reg[2] == 17) {
					//system("PAUSE");
					exit(reg[4]);
					n++;
					continue;
				}
			}
		}
	}
};