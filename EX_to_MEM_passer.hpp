#pragma once

#include<vector>
#include<string>
#include<map>
#include<cmath>
#include<cstring>
#include"line_keeper.hpp"
#include"constant.hpp"

using namespace std;

class EX_to_MEM_passer {
public:
	func command = null_func;
	int cur_line = 0 , next_line = 0;
	int changed_reg = 0, changed_reg_num = 0;
	int arg1_reg = 0, arg2_reg = 0, arg3_reg = 0;
	string label_name = "";
	int reg31 = 0, reg32 = 0, reg33 = 0;
	int arg_num = 0;
	bool ad_type = false;

	void clean() {
		command = null_func;
		cur_line = 0, next_line = 0;
		changed_reg = 0, changed_reg_num = 0;
		arg1_reg = 0, arg2_reg = 0, arg3_reg = 0;
		label_name = "";
		reg31 = 0, reg32 = 0, reg33 = 0;
		arg_num = 0;
		ad_type = false;
	}
};