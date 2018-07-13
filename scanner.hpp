#ifndef SCANNER
#define SCANNER

#include<iostream>
#include<cctype>
#include<string>
#include<cstring>

class Tokenscanner {
private:
	std::string _buffer;
	int cur_pos;

	bool iscomma(char a) {
		if (a == ',')  return true;
		else return false;
	}

	void skipWhitespace() {
		while (cur_pos < _buffer.length() && (isspace(_buffer[cur_pos]) || iscomma(_buffer[cur_pos]))) {
			cur_pos++;
		}
	}
public:
	Tokenscanner() {};

	Tokenscanner(std::string str) {
		setInput(str);
	}

	void setInput(std::string str) {
		_buffer = str;
		cur_pos = 0;
	}

	bool hasMoreTokens() {
		skipWhitespace();
		return cur_pos < _buffer.length();
	}

	std::string nextToken() {
		skipWhitespace();
		if (cur_pos >= _buffer.length()) return "";
		else {
			int start = cur_pos;
			while (cur_pos < _buffer.length() && !isspace(_buffer[cur_pos]) && !iscomma(_buffer[cur_pos])) {
				cur_pos++;
			}
			return _buffer.substr(start, cur_pos - start);
		}
	}
};

#endif