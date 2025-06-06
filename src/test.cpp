#include <iostream>
#include <string>
#include "parkingLotManagingSystem.h"
using namespace std;

pair<int,int> extractNumbers(const string& input)
// input: 输入的字符串
// 返回一个pair，包含两个整数
// 第一个整数是第一个逗号之前的数字，第二个整数是第二个逗号之前的数字
{
    int firstNumber = -1;
    int secondNumber = -1;
    pair<int,int> result = {firstNumber,secondNumber};
    size_t commaPos1 = input.find(',');
    size_t commaPos2 = input.find(',', commaPos1 + 1);

    if (commaPos1 != string::npos && commaPos2 != string::npos) {
        try {
            firstNumber = stoi(input.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1));
            secondNumber = stoi(input.substr(commaPos2 + 1));
        } catch (const std::invalid_argument& e) {
            cout << "Invalid input format: non-numeric value detected." << endl;
            return result;
        }
        result.first = firstNumber;
        result.second = secondNumber;  
        return result;
    } else {
        cout << "Invalid input format." << endl;
        return result;
    }
}

int main() {
    string input;
    parkingLotManagingSystem parkingLot(10, 1);
    cin >> input;
    // (A,1,50)
    while(input[1] != 'E')
    {
        switch(input[1]) {
            case 'A': { // 车辆进入
                int carNumber;
                int enterTime;
                carNumber = extractNumbers(input).first;
                enterTime = extractNumbers(input).second;
                parkingLot.arrive(carNumber, enterTime);
                break;
            }
            case 'D': { // 车辆离开
                int carNumber;
                int exitTime;
                carNumber = extractNumbers(input).first;
                exitTime = extractNumbers(input).second;
                parkingLot.depart(carNumber, exitTime);
                break;
            }
            case 'P': { // 打印停车场信息
                parkingLot.display();
                break;
            }
            default: { // 输入错误
                cout << "Invalid input." << endl;
                break;
            }
        }
        cin >> input;
    }

}