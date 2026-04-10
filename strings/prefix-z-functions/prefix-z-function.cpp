#include <iostream>
#include <vector>  
#include <string>

using namespace std;

vector<int> prefix_function(string s) {
    int n = (int)s.size();
    vector<int> p(n, 0);
    for (int i = 1; i < n; i++) {
       
        int c = p[i - 1];
        
        while (s[i] != s[c] && c > 0)
            c = p[c - 1];
        
        if (s[i] == s[c])
            p[i] = c + 1; 
    }
    return p;
}

vector<int> z_function(string s) {
    int n = (int)s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;

    for (int i = 1; i < n; i++) {
        
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;
        
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }

    return z;
}

int main() {
    setlocale(LC_ALL, "RUS");

    string str;
    cout << "строка: ";
    getline(cin, str);

    vector<int> pref = prefix_function(str);
    cout << "префикс функция: ";
    for (int i = 0; i < pref.size(); i++) {
        cout << pref[i] << " ";
    }
    cout << endl;

    vector<int> z = z_function(str);
    cout << "z-функция: ";
    for (int i = 0; i < z.size(); i++) {
        cout << z[i] << " ";
    }
    cout << endl;
}