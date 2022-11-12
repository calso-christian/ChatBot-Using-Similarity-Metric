// ChatTheTranslatorBot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "converse.h"
#include <string> 
#include "translator.h"

using namespace std;
int main()
{
    converse conv;
    string s;
    conv.banner();

   
    while (true) {
        cout << "You:\t";
        getline(cin, s);
        string in = s.substr(0, 2);
        translate t;
        
        if (t.lang(s)) {
            if (t.valid(s)) {
                t.match();
            }
            else { cout<<"FOO:\tSorry, It's either I don't know that language yet or There's no input detected.\n"; }
        }
        else {
            conv.check(s);
        }
        
        if (s == "Bye" || s == "Goodbye") {
            cout << "Foo: It's nice meeting you! See you soon!"<<endl;
            break;
        }
    };
    return 0;
}

