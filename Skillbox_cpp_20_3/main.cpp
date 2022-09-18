#include <iostream>
#include "fstream"
#include "string"


std::string dir_path="C:\\Users\\Azamat\\CLionProjects\\Skillbox\\module_20\\Skillbox_cpp_20_3\\resources\\",
            river_file_path =dir_path+"river.txt",
            basket_file_path=dir_path+"basket.txt";
const int buf_size=100;
int counter=0;
bool get_fish(std::string fish_type){
    char fish[buf_size]={0,};

    std::ifstream river_file(river_file_path);
    while(!river_file.eof()){
        river_file.getline( fish,buf_size,'\n');
        std::string fish_str(fish);
        if(fish_str==fish_type) return true;
    }
    river_file.close();
    return false;
}

void put_fish(std::string fish){
    std::ofstream basket_file(basket_file_path,std::ios::app);
    basket_file << fish << std::endl;
    basket_file.close();
    ++counter;
}

int main() {
    std::string fish;
    std::cout << "Input fish type to get:";
    std::cin >> fish;
    if(get_fish(fish)) put_fish(fish);
    std::cout << "You get "<< counter<<" fish(es)!" << std::endl;
}
