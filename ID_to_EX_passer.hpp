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
	int changed_reg_num = 0;
	int arg1_reg = 0;
	int arg2_reg = 0;
	int arg3_reg = 0;
	string label_name = "";
	int cur_line = 0;
	int arg_num = 0;
	bool ad_type = false;
};