#include <iostream>

#define ir_(b) ;return b; }
#define ff_(b) { b
std::string* sanitize(std::string &s, std::string r = "") ff_(for) (char &c : std::string(s)) (c == ' ') ? r : r += c, s = r ir_(&s) 
std::string CaesarEncrypt(std::string s, const int offset) ff_(for) (char &c : *sanitize(s)) (c == ' ') ? c : c = 'a' + (tolower(c) - 'a' + offset + 26) % 26 ir_(s) 
std::string VignereEncrypt(std::string s, const std::string key, bool r = false, int idx = 0) ff_(for) (char &c : *sanitize(s)) c = 'a' + (tolower(c) - 'a' + ((key[idx] - 'a') * ((r) ? -1 : 1)) + 26) % 26, idx = (idx + 1) % key.size() ir_(s) 
std::string CaesarDecrypt(std::string s, const int offset) ff_( ) ir_(CaesarEncrypt(s, offset * -1)) 
std::string VignereDecrypt(std::string s, std::string key) ff_() ir_(VignereEncrypt(s, key, true))



int main() { 
    std::string a = "ABCdef asd";
    std::cout << CaesarEncrypt(a, 5) << '\n';
    std::cout << CaesarDecrypt(CaesarEncrypt("abcdef asd", 3), 3) << '\n';
    std::string key = "abcd";
    std::cout << VignereDecrypt(VignereEncrypt("abcdez asd", key), key) << '\n';
    /*
    int offset = 5;
    std::string s = "abc d99";
    for(char &c : *sanitize(s)) c = std::string("abcdefghijklmnopqrstuvwxyz0123456789")[(std::string("abcdefghijklmonpqrstuvwxyz0123456789").find(tolower(c)) + offset + std::string("abcdefghijklmonpqrstuvwxyz0123456789").size()) % std::string("abcdefghijklmonpqrstuvwxyz0123456789").size()];
    */
    //std::cout << s << '\n';
    return 0;
}