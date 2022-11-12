#pragma once
#include "converse.h"
#include <ctime>
#include<string>
#include<algorithm>
#include <fstream>
#include <sstream>
#include <random>

const double accept_prob = 0.65, retain_prob = 0.4;

converse::converse(){
	fstream file;
	string line;
	int _ = 0, __ = 0;
	file.open("AI.txt");
	while (getline(file, line)) {
		stringstream ss(line);
		while (getline(ss, line, '\t') && __ < 2) {
			database.push_back(line);
			__ += 1;
		}
		__ = 0;
	}
	file.close();
}

void converse::check(string s) {
    srand(time(0));
	random_device rd{}; mt19937 rng{ rd() };
	bernoulli_distribution bern(retain_prob);

	int c = 0, patience = 20; bool run = false;
    c = 1 + (rand() % 5);
    transform(s.begin(), s.end(), s.begin(), ::tolower);
	string best; double max_p = 0.0, __; 

	for (int i = 0; i < database.size() && patience > 0; i++) {
		if (i % 2 != 0) {
			continue;
		}
		__ = accept(s, database[i]);
		if (__ > accept_prob && __ >= max_p) {
			max_p = __;
			best = database[i + 1];
			if (__ > 0.98) {
				if (bern(rng) == 1) {
					break;
				}
				else {
					run = true;
				}
			}
			if (run) {
				patience -= 1;
			}
		}
	}


	if (max_p > 0) {
		cout << "FOO\t"  << best << endl;
	}
	else {
		cout << "FOO:\tSorry, I did not understand you.\n";
	}
}

void converse::banner() {
    cout << "\t\t\t\t_________________________________________________" << endl;
    cout << "\t\t\t\t|                                               |" << endl;
    cout << "\t\t\t\t| Hello and Welcome to FOO the Translator Bot!  |" << endl;
    cout << "\t\t\t\t|       Your FRIEND and your INTERPRETER.       |\n";
    cout << "\t\t\t\t|               Start Chatting Now:             |\n";
    cout << "\t\t\t\t|                                               |" << endl;
    cout << "\t\t\t\t|_______________________________________________|\n" << endl;
}