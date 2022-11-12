#include <fstream>
#include <string>
#include <sstream>
#include "translator.h"
#include <algorithm>
#include "jarowinkler.h"
#include <random>

const double accept_prob = 0.65, retain_prob = 0.5;
const int db_count = 5;
const string db_path[db_count] = { "tgl.txt", "ita.txt", "ceb.txt", "ilo.txt" ,"ind.txt" };
const string langList[db_count] = { "Tagalog", "Italian", "Cebuano", "Ilocano", "Indonesian" };


bool translate::valid(string a) {
	if (translate::language >= 0) {
		if (a.find(":") + 1 == a.length()) {
			return false;
		}
		else {
			translate::key = a.substr(a.find(':') + 2);
			return true;
		}
	}
	else { return false; }
}

bool translate::lang(string a) {
	string lang = a;
	transform(lang.begin(), lang.end(), lang.begin(), ::tolower);

	if (lang.find(langList[0]) >= 0 && lang.find(langList[0]) < lang.length()) { translate::language = 0; return true; }
	else if (lang.find(langList[1]) >= 0 && lang.find(langList[1]) < lang.length()) { translate::language = 1; return true; }
	else if (lang.find(langList[2]) >= 0 && lang.find(langList[2]) < lang.length()) { translate::language = 2; return true; }
	else if (lang.find(langList[3]) >= 0 && lang.find(langList[3]) < lang.length()) { translate::language = 3; return true; }
	else if (lang.find(langList[4]) >= 0 && lang.find(langList[4]) < lang.length()) { translate::language = 4; return true; }
	else { return false; }
}

void translate::match() {
	random_device rd{}; mt19937 rng{ rd() };
	bernoulli_distribution bern(retain_prob);
	string line, best; int _ = 0, patience = 10; bool hit = false, run = true; double max_p = 0.0, __; fstream file;
	string key_l = key;
	transform(key_l.begin(), key_l.end(), key_l.begin(), ::tolower);
	file.open(db_path[translate::language]);
	while (getline(file, line) && run == true && patience != 0) {
		stringstream ss(line);

		while (getline(ss, line, '\t')) {
			if (_ == 2) {
				_ = 0;
			}
			else {
				if (hit) {
					best = line;
					hit = false;
					if (max_p > 0.99) {
						if (bern(rng) == 1) {
							run = false;
							break;
						}
					}

				}
				__ = accept(key_l, line);


				if (_ == 0 && __ > accept_prob && __ >= max_p) {
					max_p = __;
					hit = true;
				}
				_ += 1;
			}
		}
		if (max_p > 0.99) {
			patience -= 1;
		}

	}
	if (max_p > 0) {
		cout << "FOO\t '" << key << "' is '" << best << "' in " << langList[language] << endl;
	}
	else {
		cout << "FOO:\tNo match\n";
	}

}

