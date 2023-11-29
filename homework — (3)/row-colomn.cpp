#include <cmath>
#include <iostream>
#include <vector>

class RowsAndColsMachine {
public:
  RowsAndColsMachine(int key);
  int getKey() const;
  std::string encode(const std::string &plaintext) const;
  std::string decode(const std::string &ciphertext) const;

private:
  int m_key;
  void algorithm(std::string &text, int key) const;
};

RowsAndColsMachine::RowsAndColsMachine(int key) : m_key{key} {}

int RowsAndColsMachine::getKey() const { return m_key; }

std::string RowsAndColsMachine::encode(const std::string &plaintext) const {
  std::string text{plaintext};
  algorithm(text, m_key);
  return text;
}

std::string RowsAndColsMachine::decode(const std::string &ciphertext) const {
  std::string text{ciphertext};
  algorithm(text, ceil(static_cast<double>(ciphertext.length()) / m_key));
  return text;
}

void RowsAndColsMachine::algorithm(std::string &text, int key) const {
  int len = text.length();
  int rows = key;
  int cols = ceil(static_cast<double>(len) / rows);

  // ????????? ???????
  std::vector<std::vector<char>> matrix(rows);

  int c = 0;
  // ?????? ?????? ? ???????
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (c < len) {
        matrix[i].push_back(text[c]);
        ++c;
      } else {
        matrix[i].push_back(' ');
      }
    }
  }

  c = 0;
  // ?????? ?? ??????? ? ???????????? ????????
  for (int i = 0; i < cols; ++i) {
    for (int j = 0; j < rows; ++j) {
      if (c < len) {
        text[c] = matrix[j][i];
        ++c;
      }
    }
  }
}

int main() {
  RowsAndColsMachine machine(2); // ????

  // ????????? ????? ?? ????????????
  std::string input;
  std::cout << "??????? ?????????? ????????: ";
  std::getline(std::cin, input);

  // ??????????? ? ????? ??????????
  std::string encodedText = machine.encode(input);
  std::cout << "????????????: " << encodedText << std::endl;

  // ????????????? ? ????? ??????????
  std::string decodedText = machine.decode(encodedText);
  std::cout << "????????????: " << decodedText << std::endl;

  return 0;
}