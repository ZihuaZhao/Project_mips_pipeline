#pragma once

#include<vector>
#include<string>
#include<map>
#include<cmath>
#include<cstring>
#include"line_keeper.hpp"
#include"constant.hpp"

using namespace std;

class IF_to_ID_passer {
public:
	int cur_line = 0;
	bool line_is_over = false;
	
	IF_to_ID_passer(){}

	void clean() {
		cur_line = 0;
		line_is_over = false;
	}
};