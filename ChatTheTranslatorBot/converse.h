#pragma once
#include<iostream>
#include "jarowinkler.h"
#include <vector>
using namespace std;


class converse : public jarowinkler{

	public:
		vector<string> database;
		void check(string s);
		void banner();
		converse();
};