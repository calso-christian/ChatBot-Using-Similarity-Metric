#pragma once
#include<iostream>

using namespace std;

class jarowinkler {

	public:
		double jaro_distance(string s1, string s2);
		double jaro_Winkler(string s1, string s2);
		double accept(string A, string B);
};