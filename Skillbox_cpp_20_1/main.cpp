#include <iostream>
#include "fstream"
#include "vector"
#include "sstream"

std::string name, surname, date;
int salary;
int D, M, Y;

void input_data(){
    std::cout << "Input\nName:";
    std::cin >> name;
    std::cout << "Surname:";
    std::cin >> surname;
    std::cout << "Date:";
    std::cin >> date;
    std::cout << "Salary:";
    std::cin >> salary;
}

bool dataIsValid(){
    char dayChr[3]={0,},monthChr[3]={0,},yearChr[10]={0,};
    std::stringstream ssDate(date);
    if(!ssDate.eof())ssDate.getline((char*)dayChr,   3,'.');
    if(!ssDate.eof())ssDate.getline((char*)monthChr, 3,'.');
    if(!ssDate.eof())ssDate.getline((char*)yearChr,  10,'.');
    D = std::stoi(dayChr);
    M = std::stoi(monthChr);
    Y = std::stoi(yearChr);
    return (D > 0 && (
        (D<=31 && (M==1||M==3||M==5||M==7||M==8||M==10||M==12)) ||
        (D<=30 && (M==4||M==6||M==9||M==11))       ||
        (M==2  && ((D<=29 && (Y%4==0 && Y%100!=0)) ||
                  (D<=28 && ((Y%4==0 && Y%100==0)  || Y%4!=0)) ))));
}
void writeToFile(){
    std::string filepath = "C:\\Users\\Azamat\\CLionProjects\\Skillbox\\module_20\\Skillbox_cpp_20_1\\resources\\accounts.txt";
    std::ofstream file(filepath,std::ios::app);
    file.setf(std::ios::fixed);
    file <<name<<" "<<surname<<" "<<D<<'.'<<M<<'.'<<Y<<" "<<salary<<std::endl;
    file.close();
}

int main() {

    bool notFinished=false;
    do{
        input_data();
        notFinished=!dataIsValid();
    if (notFinished) std::cout << "DATE IS INVALID. Try again";
    } while (notFinished);
    writeToFile();

}
