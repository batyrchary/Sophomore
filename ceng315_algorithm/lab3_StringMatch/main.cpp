#include "lab3.h"
#include <iostream>

using namespace std;

int main()
{
    char *T;
    unsigned text_size;
    char P[21];
    unsigned pattern_size;
    char c1, c2;
    vector<unsigned> output;
    cin >> text_size >> pattern_size;
    T = new char[text_size+1];
    cin >> T >> P >> c1 >> c2;
    output = find_occurrences(T, text_size, P, pattern_size, c1, c2);
    cout << "\x01\x01\x01";
    for (vector<unsigned>::iterator it = output.begin(); it!= output.end(); ++it)
    {
        cout << (*it) << " ";
    }
    return 0;
}
