#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

char getMaxColor(string s) {
    map<char, int> count;
    for (string::iterator it = s.begin(); it != s.end(); it++) {
        count[*it]++;
    }
    pair<char,int> max;
    for (map<char,int>::iterator it = count.begin(); it != count.end(); it++) {
        pair<char,int> p = *it;
        if (max.second < p.second) {
            max = p;
        }

    }
    return max.first;
}


bool sameColorAll(string s) {
    char first = s[0];
    for (string::iterator it = s.begin(); it != s.end(); it++) {
        if (first != (*it)) {
            return false;
        }
    }
    return true;

}

int paints(string stripes, char first) {
    cout << stripes << endl;
    if (stripes.size() == 0) { return 0; }
    if (sameColorAll(stripes)) { return 1; }

    if (first == '') {
        string colors = "ABC";
        for (string::iterator it = colors.begin(); it != colors.end(); it++) {
            return min(paintCount, paints(stripes, *it));
        }
    } else {
        cout << first << endl;
        int paintCount = 1;

        string block = "";
        for (string::iterator it = stripes.begin(); it != stripes.end(); it++) {
            const char c = *it;
            if (c == first) {
                paintCount += paint(block);
                block = "";
            } else {
                block.append(1, c);
            }
        }
        paintCount += paint(block);

        return paintCount;
    }

}

int paint(string stripes) {
    cout << stripes << endl;
    if (stripes.size() == 0) { return 0; }
    if (sameColorAll(stripes)) { return 1; }

    char painted = getMaxColor(stripes);
    cout << painted << endl;
    int paintCount = 1;

    string block = "";
    for (string::iterator it = stripes.begin(); it != stripes.end(); it++) {
        const char c = *it;
        if (c == painted) {
            paintCount += paint(block);
            block = "";
        } else {
            block.append(1, c);
        }
    }
    paintCount += paint(block);

    return paintCount;
}

int miniStrokes(string stripes) {
    return paint(stripes);
}


int main() {
    printf("%d\n", miniStrokes("BECBBDDEEBABDCADEAAEABCACBDBEECDEDEACACCBEDABEDADD"));
}

