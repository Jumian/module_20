#include <iostream>
#include "fstream"
#include "vector"
#include "cstdlib"
#include "ctime"


const int notes = 6;
/*  6 banknotes:
 *  0- 5000 RUB
 *  1- 2000 RUB
 *  2- 1000 RUB
 *  3- 500 RUB
 *  4- 200 RUB
 *  5- 100 RUB
 */
std::vector<int>    banknotes = {5000, 2000, 1000, 500, 200, 100},
                    atm_cash(notes,0),
                    withdrawal_set(notes,0);

const std::string filepath = "C:\\Users\\Azamat\\CLionProjects\\Skillbox\\module_20\\Skillbox_cpp_20_4\\resources\\atm.bin";
void init (int arr[],int size){
    for(int i = 0;i<size;++i)arr[i]=0;
}

void print_atm(std::vector<int> &vec) {
    int count = 0;
    for (int i = 0; i < notes; ++i) {
        if (vec[i]) {
            std::cout << banknotes[i] << " RUB - " << vec[i] << std::endl;
            count += vec[i];
        }
    }
    std::cout << "Total banknotes = " << count << std::endl;
}

bool isNumber(std::string str) {
    for (int i = 0; i < str.size(); ++i)
        if (str[i] < '0' || str[i] > '9') return false;
    return true;
}

void save() {
    std::ofstream ofile(filepath, std::ios::binary);
    if (ofile.is_open()) {
        int size = notes;
        ofile.write((char *) &size, sizeof(int));
        ofile.write((char *) &banknotes[0], sizeof(int) * size);
        ofile.write((char *) &atm_cash[0], sizeof(int) * size);
        ofile.close();
    }
}

void get_money() {
    int vector_size = 0;
    std::ifstream file(filepath, std::ios::binary);
    file.read((char *) &vector_size, sizeof(vector_size));
    if (file.is_open()) {
        file.read((char *) &banknotes[0], sizeof(int) * vector_size);
        file.read((char *) &atm_cash[0], sizeof(int) * vector_size);
        file.close();
    }
}

void put_money() {
    std::srand(std::time(nullptr));
    int atm_banknotes = 0;
    for (int i = 0; i < 1000 - atm_banknotes; ++i) {
        atm_cash[rand() % 6] += 1;
    }
    save();
    print_atm(atm_cash);
}

std::string input(std::string prompt) {
    std::string input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}


bool isAvailable(int money) {
    std::fill(withdrawal_set.begin(), withdrawal_set.end(),0);
    for (int i = 0; i < notes; ++i) {
        withdrawal_set[i] = (money / banknotes[i] > atm_cash[i] ? atm_cash[i] : money / banknotes[i]);
        money -= withdrawal_set[i] * banknotes[i];
    }
    return money == 0;
}

bool withdrawal() {
    int money;
    bool isNumberb = false;
    std::string money_str;
    do {
        money_str = input("Withdrawal[multiple " + std::to_string(banknotes[notes-1]) + "]:");
        isNumberb = isNumber(money_str);
        if (isNumberb) money = std::stol(money_str);
    } while (!((isNumberb) && (money % banknotes[notes-1] == 0)));
    if (isAvailable(money)) {
        for (int i = 0; i < notes; ++i) {
            atm_cash[i] -= withdrawal_set[i];
        }
        save();
        print_atm(withdrawal_set);
        return true;
    } else {
        std::cout << "This transaction is not available\n";
    }
    return false;
}

int main() {
    std::fill(withdrawal_set.begin(), withdrawal_set.end(),0);
    std::fill(atm_cash.begin(), atm_cash.end(),0);
    std::string input_str = input("input command[+-]:");
    if (input_str == "+") {
        put_money();
    } else if (input_str == "-") {
        get_money();
        withdrawal();
    } else if (input_str == "?") {
        get_money();
        print_atm(atm_cash);
    }
    std::cout << "END" << std::endl;
    return 0;
}

