#include <iostream>
#include <string>

class CaesarCipher {
public:
    CaesarCipher(int key);
    std::string encrypt(const std::string& plaintext) const;
    std::string decrypt(const std::string& ciphertext) const;

private:
    int m_key; // ???? ??? ????? ??????
};

CaesarCipher::CaesarCipher(int key) : m_key(key) {}

std::string CaesarCipher::encrypt(const std::string& plaintext) const {
    std::string ciphertext;
    for (char c : plaintext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char encryptedChar = static_cast<char>((c - base + m_key) % 26 + base);
            ciphertext.push_back(encryptedChar);
        } else {
            ciphertext.push_back(c);
        }
    }
    return ciphertext;
}

std::string CaesarCipher::decrypt(const std::string& ciphertext) const {
    std::string decryptedText;
    for (char c : ciphertext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char decryptedChar = static_cast<char>((c - base - m_key + 26) % 26 + base);
            decryptedText.push_back(decryptedChar);
        } else {
            decryptedText.push_back(c);
        }
    }
    return decryptedText;
}

int main() {
    int key = 3; // ???????? ?? ??? ????
    CaesarCipher caesar(key);

    // ????????? ????? ?? ????????????
    std::string input;
    std::cout << "??????? ?????: ";
    std::getline(std::cin, input);

    // ?????????? ? ????? ??????????
    std::string encryptedText = caesar.encrypt(input);
    std::cout << "???????????: " << encryptedText << std::endl;

    // ??????????? ? ????? ??????????
    std::string decryptedText = caesar.decrypt(encryptedText);
    std::cout << "????????????: " << decryptedText << std::endl;

    return 0;
}