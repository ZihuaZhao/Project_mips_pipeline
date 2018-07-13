#include<iostream>
#include<cctype>
#include<string>
#include<map>
#include<vector>
#include"scanner.hpp"
#include"parser.hpp"
#include"line_keeper.hpp"
#include"constant.hpp"
#include"execution.hpp"
#include"pipeline.hpp"

using namespace std;
char vir_mem[4 * 1024 * 1024];

int main(int argc , char **argv) {
	memset(&vir_mem[0], 0, 4 * 1024 * 1024);
	int static_seg = 0;
	int heap_seg = 0;
	int stack_seg = 4 * 1024 * 1024 - 1;
	map<string, int> funcbase;
	map<string, int> database;
	vector<line_keeper> linebase;
	int mainpos;
	int reg[34];
	memset(reg, 0, 34*sizeof(int));
	reg[29] = 4 * 1024 * 1024 - 1;
	parser p(argv[1]);
	int x = 1;
	while (p.pre_deal(&database, &funcbase, &linebase,
		reg, mainpos, vir_mem, static_seg, heap_seg, stack_seg, x)) {
		x++;
	}
	reg[34] = mainpos;
	/*for (int i = 0; i < linebase.size(); ++i) {
		linebase[i].out000();
	}*/
	/*execution e;
	e.execute(&database, &funcbase, &linebase,
		reg, mainpos, vir_mem, static_seg, heap_seg, stack_seg);*/
	pipeline pipe;
	while (pipe.execute(reg, &database, &funcbase, &linebase, vir_mem, static_seg, heap_seg, stack_seg)){}
	return 0;
}