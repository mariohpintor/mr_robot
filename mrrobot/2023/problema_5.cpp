#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool anagrama(string s1, string s2){
    for(char &c : s1) c = tolower(c);
    for(char &c : s2) c = tolower(c);

    // Si miden diferente, no pueden ser anagramas
    if (s1.length() != s2.length()) return false;

    int cuenta[26] = {0}; 

    for (int i = 0; i < s1.length(); i++){
        // Restamos 'a' para que el índice sea de 0 a 25
        cuenta[s1[i] - 'a']++; 
        cuenta[s2[i] - 'a']--; 
    }

    // Si al final todos son 0, eran anagramas
    for (int i = 0; i < 26; i++){
        if (cuenta[i] != 0) return false;
    }
    return true;
}

int main(){
    string a = "roma";
    string b = "amor";
    string c = "perro";

    cout << "roma y amor: " << (anagrama(a, b) ? "Es anagrama" : "No es anagrama") << endl;
    cout << "roma y perro: " << (anagrama(a, c) ? "Es anagrama" : "No es anagrama") << endl;
    cout << "Roma y amor: " << (anagrama("Roma", "amor") ? "Es anagrama" : "No es anagrama") << endl;
    
    return 0;
}