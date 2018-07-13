#pragma once

#include<vector>
#include<string>
#include<map>
#include<cmath>
#include<cstring>
#include"line_keeper.hpp"
#include"constant.hpp"

using namespace std;

class ID_to_EX_passer {
public:
	func command;
	int reg_to_change_num = 0;
	int arg1_reg = 0;
	int arg2_reg = 0;
	int arg3_reg = 0;
	string label_name = "";
	int cur_line = 0;
	int arg_num = 0;
	bool ad_type = false;

	void clean() {
		reg_to_change_num = 0;
		arg1_reg = 0;
		arg2_reg = 0;
		arg3_reg = 0;
		label_name = "";
		cur_line = 0;
		arg_num = 0;
		ad_type = false;
	}
};