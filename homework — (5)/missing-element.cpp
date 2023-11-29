#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// ??????? ??? ?????????? ???????????? ???????? ? ???????
int getMissingValue(const std::vector<unsigned>& vec){
    int m = vec.size() + 1;
    int mSum = m * (m + 1) / 2;

    int nSum{0};
    for(size_t i{0}; i < vec.size(); ++i){
        nSum += vec[i];
    }

    return (mSum - nSum);
}

int main(){
    srand(time(0));

    // ???? ??????? ???????
    unsigned n;
    std::cout << "??????? n: ";
    std::cin >> n;
    
    std::vector<unsigned> vec;
    unsigned val = 1 + rand() % n;

    int i{1};

    // ?????????? ??????? ? ????????? ?????? ????????
    while(i <= n){
        if(i != val){
            vec.push_back(i);
        }
        ++i;
    }

    // ????? ???????
    std::cout << "??????:\n";
    for(size_t i{0}; i < vec.size(); ++i){
        std::cout << vec[i] << ' ';
    }

    // ????? ???????????? ????????
    std::cout << "\n??????????? ????????: " << getMissingValue(vec);
}