#pragma once
#include <iostream>
#include "jarowinkler.h"

using namespace std;

class translate : public jarowinkler {

	public:
		int language;
		string key;
		string langList[5] = { "tagalog", "italian", "cebuano", "ilocano", "indonesian"};
		bool lang(string s);
		bool valid(string s);
		void match();
};