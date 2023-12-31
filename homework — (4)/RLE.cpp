#include <iostream>
#include <string>

using namespace std;

// ??????? ??? ??????????? ?????? ? ?????????????? ?????? Run-Length Encoding (RLE)
string encodeRLE(const string& input) {
    string encoded = "";
    int length = input.length();

    for (int i = 0; i < length; i++) {
        int count = 1;

        // ??????? ?????????? ?????? ?????? ?????????? ????????
        while (i < length - 1 && input[i] == input[i + 1]) {
            count++;
            i++;
        }

        // ?????????? ??????? ? ??? ?????????? ? ?????????????? ??????
        encoded += input[i];
        encoded += to_string(count);
    }

    return encoded;
}

// ??????? ??? ????????????? ??????, ??????????????? RLE
string decodeRLE(const string& encoded) {
    string decoded = "";
    int length = encoded.length();

    for (int i = 0; i < length; i += 2) {
        char character = encoded[i];
        int count = stoi(encoded.substr(i + 1, 1));

        // ?????????? ??????? ? ?????????????? ?????? ?????? ?????????? ???
        for (int j = 0; j < count; j++) {
            decoded += character;
        }
    }

    return decoded;
}

int main() {
    string input;

    cout << "??????? ????? ??? ???????????: ";
    getline(cin, input);

    // ??????????? ? ????????????? ?????? ? ?????????????? RLE
    string encodedText = encodeRLE(input);
    string decodedText = decodeRLE(encodedText);

    cout << "\n?????????????? ?????: " << encodedText << endl;
    cout << "?????????????? ?????: " << decodedText << endl;

    return 0;
}