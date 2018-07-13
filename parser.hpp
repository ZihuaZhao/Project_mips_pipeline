#ifndef PARSER
#define PARSER

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<map>
#include<utility>
#include<cmath>
#include"scanner.hpp"
#include"line_keeper.hpp"

class parser {
private:
	ifstream file;
	bool is_text;
	int line_counter = 0;

public:
	parser(const char*filename) {
		file.open(filename);
	}

	~parser() {
		file.close();
	}

private:

	func string_to_func(string str) {
		if (str == ".align") return _align;
		if (str == ".ascii") return _ascii;
		if (str == ".asciiz") return _asciiz;
		if (str == ".byte") return _byte;
		if (str == ".half") return _half;
		if (str == ".word") return _word;
		if (str == ".space") return _space;
		if (str == ".data") return _data;
		if (str == ".text") return _text;
		if (str == "add") return add;
		if (str == "addu") return addu;
		if (str == "addiu") return addiu;
		if (str == "sub") return sub;
		if (str == "subu") return subu;
		if (str == "mul") return mul;
		if (str == "mulu") return mulu;
		if (str == "div") return divv;
		if (str == "divu") return divu;
		if (str == "xor") return xoor;
		if (str == "xoru") return xoru;
		if (str == "neg") return neg;
		if (str == "negu") return negu;
		if (str == "rem") return rem;
		if (str == "remu") return remu;
		if (str == "li") return li;
		if (str == "seq") return seq;
		if (str == "sge") return sge;
		if (str == "sgt") return sgt;
		if (str == "sle") return sle;
		if (str == "slt") return slt;
		if (str == "sne") return sne;
		if (str == "b") return b;
		if (str == "beq") return beq;
		if (str == "bne") return bne;
		if (str == "bge") return bge;
		if (str == "ble") return ble;
		if (str == "bgt") return bgt;
		if (str == "blt") return blt;
		if (str == "beqz") return beqz;
		if (str == "bnez") return bnez;
		if (str == "blez") return blez;
		if (str == "bgez") return bgez;
		if (str == "bgtz") return bgtz;
		if (str == "bltz") return bltz;
		if (str == "j") return j;
		if (str == "jr") return jr;
		if (str == "jal") return jal;
		if (str == "jalr") return jalr;
		if (str == "la") return la;
		if (str == "lb") return lb;
		if (str == "lh") return lh;
		if (str == "lw") return lw;
		if (str == "sb") return sb;
		if (str == "sh") return sh;
		if (str == "sw") return sw;
		if (str == "move") return mov;
		if (str == "mfhi") return mfhi;
		if (str == "mflo") return mflo;
		if (str == "nop") return nop;
		if (str == "syscall") return syscall;
		if (str == "main:") return mainp;
		else return label;
	}

	int string_to_reg(string str) {
		if (str == "$zero") return 0;
		if (str == "$at") return 1;
		if (str == "$v0") return 2;
		if (str == "$v1") return 3;
		if (str == "$a0") return 4;
		if (str == "$a1") return 5;
		if (str == "$a2") return 6;
		if (str == "$a3") return 7;
		if (str == "$t0") return 8;
		if (str == "$t1") return 9;
		if (str == "$t2") return 10;
		if (str == "$t3") return 11;
		if (str == "$t4") return 12;
		if (str == "$t5") return 13;
		if (str == "$t6") return 14;
		if (str == "$t7") return 15;
		if (str == "$s0") return 16;
		if (str == "$s1") return 17;
		if (str == "$s2") return 18;
		if (str == "$s3") return 19;
		if (str == "$s4") return 20;
		if (str == "$s5") return 21;
		if (str == "$s6") return 22;
		if (str == "$s7") return 23;
		if (str == "$t8") return 24;
		if (str == "$t9") return 25;
		if (str == "$k0") return 26;
		if (str == "$k1") return 27;
		if (str == "$gp") return 28;
		if (str == "$sp") return 29;
		if (str == "$fp") return 30;
		if (str == "$ra") return 31;
		if (str == "$hi") return 32;
		if (str == "$lo") return 33;
		if (str == "$ra") return 34;
		if (str == "$0") return 0;
		if (str == "$1") return 1;
		if (str == "$2") return 2;
		if (str == "$3") return 3;
		if (str == "$4") return 4;
		if (str == "$5") return 5;
		if (str == "$6") return 6;
		if (str == "$7") return 7;
		if (str == "$8") return 8;
		if (str == "$9") return 9;
		if (str == "$10") return 10;
		if (str == "$11") return 11;
		if (str == "$12") return 12;
		if (str == "$13") return 13;
		if (str == "$14") return 14;
		if (str == "$15") return 15;
		if (str == "$16") return 16;
		if (str == "$17") return 17;
		if (str == "$18") return 18;
		if (str == "$19") return 19;
		if (str == "$20") return 20;
		if (str == "$21") return 21;
		if (str == "$22") return 22;
		if (str == "$23") return 23;
		if (str == "$24") return 24;
		if (str == "$25") return 25;
		if (str == "$26") return 26;
		if (str == "$27") return 27;
		if (str == "$28") return 28;
		if (str == "$29") return 29;
		if (str == "$30") return 30;
		if (str == "$31") return 31;
		if (str == "$32") return 32;
		if (str == "$33") return 33;
		if (str == "$34") return 34;
	}

	string process(string str)
	{
		string tmp="";
		for (size_t i = 0; i < str.size(); i++)
		{
			if (str[i] == '\\')
			{
				i++;
				if (str[i] == '\\')
				{
					tmp += '\\';
				}
				if (str[i] == '\"')
				{
					tmp += '\"';
				}
				if (str[i] == 'n')
				{
					tmp += '\n';
				}
				if (str[i] == 't')
				{
					tmp += '\t';
				}
				if (str[i] == 'r')
				{
					tmp += '\r';
				}
				if (str[i] == '0')
				{
					tmp += '\0';
				}
			}
			else
			{
				tmp += str[i];
			}
		}
		return tmp;
	}

public:
	bool pre_deal(map<string, int>*database, map<string, int>*funcbase, vector<line_keeper>*linebase, 
		int* reg, int& mainpos, char* vir_mem, int& static_seg, int& heap_seg, int& stack_seg , int x) {
		if (file.eof()) return false;
		else {
			string _buffer;
			getline(file, _buffer);
			if (_buffer == "") return true;
			Tokenscanner token(_buffer);
			token.setInput(_buffer);
			line_keeper line;
			string fir = token.nextToken();
			line.command = string_to_func(fir);
			line.true_num = x;
			if (line.command == _data) {
				is_text = false;
				return true;
			}
			if (line.command == _text) {
				is_text = true;
				return true;
			}
			if (line.command == mainp) {
				mainpos = line_counter;
				return true;
			}
			if (line.command == _align) {
				string str = token.nextToken();
				int n = stoi(str);
				n = pow(2, n);
				if (static_seg % n == 0) return true;
				else {
					int x = (static_seg / n + 1) * n - static_seg;
					static_seg += x;
					heap_seg += x;
					return true;
				}
			}
			if (line.command == _ascii || line.command == _asciiz) {
				int a = _buffer.find_first_of('\"');
				int b = _buffer.find_last_of('\"');
				string str1 = _buffer.substr(a + 1, b - a - 1);
				string str = process(str1);
				for (int i = 0; i < str.size(); ++i) {
					vir_mem[i + static_seg] = str[i];
				}
				static_seg += str.size();
				heap_seg += str.size();
				if (line.command == _asciiz) {
					vir_mem[static_seg] = '\0';
					static_seg += 1;
					heap_seg += 1;
				}
				return true;
			}
			if (line.command == _byte) {
				while (token.hasMoreTokens()) {
					string str1 = token.nextToken();
					int x = stoi(str1);
					memcpy(&vir_mem[static_seg], &x, 1);
					static_seg += 1;
					heap_seg += 1;
				}
				return true;
			}
			if (line.command == _half) {
				while (token.hasMoreTokens()) {
					string str1 = token.nextToken();
					int x = stoi(str1);
					memcpy(&vir_mem[static_seg], &x, 2);
					static_seg += 2;
					heap_seg += 2;
				}
				return true;
			}
			if (line.command == _word) {
				while (token.hasMoreTokens()) {
					string str1 = token.nextToken();
					int x = stoi(str1);
					memcpy(&vir_mem[static_seg], &x, 4);
					static_seg += 4;
					heap_seg += 4;
				}
				return true;
			}
			if (line.command == _space) {
				string str = token.nextToken();
				int n = stoi(str);
				static_seg += n;
				heap_seg += n;
				return true;
			}
			if (line.command == label) {
				if (is_text) {
					fir = fir.substr(0, fir.size() - 1);
					funcbase->operator[](fir) = line_counter;
					return true;
				}
				else {
					fir = fir.substr(0, fir.size() - 1);
					database->operator[](fir) = static_seg;
					return true;
				}
			}
			line_counter++;
			if (line.command == add || line.command == addu || line.command == sub ||
				line.command == subu || line.command == xoor || line.command == xoru ||
				line.command == rem || line.command == remu || line.command == seq ||
				line.command == sge || line.command == sgt || line.command == sle ||
				line.command == slt || line.command == sne) {
				string str = token.nextToken();
				line.Rdest = string_to_reg(str);
				str = token.nextToken();
				line.Rsrc1 = string_to_reg(str);
				str = token.nextToken();
				if (str[0] == '$') {
					line.Src2_reg = string_to_reg(str);
					line.Src2_type = false;
				}
				else {
					line.Src2_dig = stoi(str);
					line.Src2_type = true;
				}
				line.arg_num = 3;
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
			if (line.command == addiu) {
				string str = token.nextToken();
				line.Rdest = string_to_reg(str);
				str = token.nextToken();
				line.Rsrc1 = string_to_reg(str);
				str = token.nextToken();
				line.Imm = stoi(str);
				line.arg_num = 3;
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
			if (line.command == mul || line.command == mulu) {
				string str = token.nextToken();
				line.Rdest = string_to_reg(str);
				str = token.nextToken();
				if (token.hasMoreTokens()) {
					line.Rsrc1 = string_to_reg(str);
					str = token.nextToken();
					if (str[0] == '$') {
						line.Src2_reg = string_to_reg(str);
						line.Src2_type = false;
					}
					else {
						line.Src2_dig = stoi(str);
						line.Src2_type = true;
					}
					line.arg_num = 3;
				}
				else {
					if (str[0] == '$') {
						line.Src2_reg = string_to_reg(str);
						line.Src2_type = false;
					}
					else {
						line.Src2_dig = stoi(str);
						line.Src2_type = true;
					}
					line.arg_num = 2;
				}
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
			if (line.command == divv || line.command == divu) {
				string str1 = token.nextToken();
				string str2 = token.nextToken();
				if (token.hasMoreTokens()) {
					string str3 = token.nextToken();
					line.Rdest = string_to_reg(str1);
					line.Rsrc1 = string_to_reg(str2);
					if (str3[0] == '$') {
						line.Src2_reg = string_to_reg(str3);
						line.Src2_type = false;
					}
					else {
						line.Src2_dig = stoi(str3);
						line.Src2_type = true;
					}
					line.arg_num = 3;
				}
				else {
					line.Rsrc1 = string_to_reg(str1);
					line.Rsrc2 = string_to_reg(str2);
					line.arg_num = 2;
					line.Src2_type = false;
				}
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
			if (line.command == neg || line.command == negu || line.command == mov) {
				string str = token.nextToken();
				line.Rdest = string_to_reg(str);
				str = token.nextToken();
				line.Rsrc = string_to_reg(str);
				line.arg_num = 2;
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
			if (line.command == li) {
				string str = token.nextToken();
				line.Rdest = string_to_reg(str);
				str = token.nextToken();
				line.Imm = stoi(str);
				line.arg_num = 2;
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
			if (line.command == b || line.command == j || line.command == jal) {
				string str = token.nextToken();
				line.label_name = str;
				line.arg_num = 1;
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
			if (line.command == beq || line.command == bne || line.command == bge ||
				line.command == ble || line.command == bgt || line.command == blt) {
				string str = token.nextToken();
				line.Rsrc1 = string_to_reg(str);
				str = token.nextToken();
				if (str[0] == '$') {
					line.Src2_reg = string_to_reg(str);
					line.Src2_type = false;
				}
				else {
					line.Src2_dig = stoi(str);
					line.Src2_type = true;
				}
				str = token.nextToken();
				line.label_name = str;
				line.arg_num = 3;
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
			if (line.command == beqz || line.command == bnez || line.command == blez ||
				line.command == bgez || line.command == bgtz || line.command == bltz) {
				string str = token.nextToken();
				line.Rsrc = string_to_reg(str);
				str = token.nextToken();
				line.label_name = str;
				line.arg_num = 2;
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
			if (line.command == jr || line.command == jalr) {
				string str = token.nextToken();
				line.Rsrc = string_to_reg(str);
				line.line_num = line_counter;
				line.arg_num = 1;
				linebase->push_back(line);
				return true;
			}
			if (line.command == la || line.command == lb ||
				line.command == lh || line.command == lw) {
				string str = token.nextToken();
				line.Rdest = string_to_reg(str);
				str = token.nextToken();
				for (int i = 0; i < str.size(); ++i) {
					if (str[i] == '(') {
						line.ad_type = false;
						int n, m;
						for (n = 0; n < str.size(); ++n) {
							if (str[n] == '(') {
								break;
							}
						}
						for (m = n; m < str.size(); ++m) {
							if (str[m] == ')') {
								break;
							}
						}
						string str1 = str.substr(0, n);
						string str2 = str.substr(n + 1, m - 1 - n);
						line.ad_dig = stoi(str1);
						line.ad_reg = string_to_reg(str2);
						line.arg_num = 2;
						line.line_num = line_counter;
						linebase->push_back(line);
						return true;
					}
				}
				line.ad_type = true;
				line.label_name = str;
				line.arg_num = 2;
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
			if (line.command == sb || line.command == sh || line.command == sw) {
				string str = token.nextToken();
				line.Rsrc = string_to_reg(str);
				str = token.nextToken();
				for (int i = 0; i < str.size(); ++i) {
					if (str[i] == '(') {
						line.ad_type = false;
						int n, m;
						for (n = 0; n < str.size(); ++n) {
							if (str[n] == '(') {
								break;
							}
						}
						for (m = n; m < str.size(); ++m) {
							if (str[m] == ')') {
								break;
							}
						}
						string str1 = str.substr(0, n);
						string str2 = str.substr(n + 1, m - 1 - n);
						line.ad_dig = stoi(str1);
						line.ad_reg = string_to_reg(str2);
						line.arg_num = 2;
						line.line_num = line_counter;
						linebase->push_back(line);
						return true;
					}
				}
				line.ad_type = true;
				line.label_name = str;
				line.arg_num = 2;
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
			if (line.command == mfhi || line.command == mflo) {
				string str = token.nextToken();
				line.Rdest = string_to_reg(str);
				line.arg_num = 1;
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
			if (line.command == nop || line.command == syscall) {
				line.arg_num = 0;
				line.line_num = line_counter;
				linebase->push_back(line);
				return true;
			}
		}
	}

};




#endif