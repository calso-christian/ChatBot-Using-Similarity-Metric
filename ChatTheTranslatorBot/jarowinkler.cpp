#include <iostream>
#include <algorithm>
#include <string>
#include "jarowinkler.h"

using namespace std;

double jarowinkler::jaro_distance(string s1, string s2) {
    if (s1 == s2) return 1.0;
    int len1 = s1.length();
    int len2 = s2.length();
    if (len1 == 0 || len2 == 0)
        return 0.0;
    int max_dist = floor(max(len1, len2) / 2) - 1;
    int match = 0;
    int* hash_s1 = new int[len1];
    int* hash_s2 = new int[len2];

    for (int i = 0; i < len1; i++) { hash_s1[i] = 0; }
    for (int i = 0; i < len2; i++) { hash_s2[i] = 0; }
    for (int i = 0; i < len1; i++) {
        for (int j = max(0, i - max_dist); j < min(len2, i + max_dist + 1); j++) {
            if (s1[i] == s2[j] && hash_s2[j] == 0) {
                hash_s1[i] = 1;
                hash_s2[j] = 1;
                match++;
                break;
            }
        }
    }
    if (match == 0) return 0.0;
    double t = 0; int point = 0;
    for (int i = 0; i < len1; i++) {
        if (hash_s1[i]) {
            while (hash_s2[point] == 0) {
                point++;
            }
            if (s1[i] != s2[point++])
                t++;
        }
    }
    t /= 2;
    return (((double)match) / ((double)len1)
        + ((double)match) / ((double)len2)
        + ((double)match - t) / ((double)match))
        / 3.0;
}
double jarowinkler::jaro_Winkler(string s1, string s2){
    double jaro_dist = jaro_distance(s1, s2);
    if (jaro_dist > 0.7) {
        int prefix = 0;
        for (int i = 0;
            i < min(s1.length(), s2.length()); i++) {
            if (s1[i] == s2[i])
                prefix++;
            else
                break;
        }
        prefix = min(4, prefix);
        jaro_dist += 0.1 * prefix * (1 - jaro_dist);
    }
    return jaro_dist;
}

double jarowinkler::accept(string A, string B) {
    transform(B.begin(), B.end(), B.begin(), ::tolower);
    return jaro_Winkler(A, B);
}
