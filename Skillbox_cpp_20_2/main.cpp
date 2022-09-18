#include <iostream>
#include "fstream"
#include "cstdlib"
#include "ctime"

const std::string filepath="C:\\Users\\Azamat\\CLionProjects\\Skillbox\\module_20\\Skillbox_cpp_20_2\\resources\\picture.txt";

int main() {
    int rows=0,cols =0;
    std::cout << "Input rows & cols:";
    std::cin >> rows >> cols;
    

    std::srand(std::time(nullptr));
    std::ofstream file(filepath);
    for (int k=0;k<rows;++k) {
        for (int i = 0; i < cols; ++i) {
            file << std::rand() % 2;
        }
        file << std::endl;
    }
    file.close();
    std::cout << "Write is ended! Check result:\n" << filepath  << std::endl;
}
