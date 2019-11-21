
    std::string a = "abcdef asd";
    std::cout << CaesarEncrypt("abcdez asd", 3) << '\n';
    std::cout << CaesarDecrypt(CaesarEncrypt("abcdez asd", 3), 3) << '\n';
    std::string key = "abcd";
    std::cout << VignereDecrypt(VignereEncrypt("abcdez asd", key), key) << '\n';