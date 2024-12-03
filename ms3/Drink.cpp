#include "Drink.h"
#include <iostream>
#include <iomanip>  // Để set định dạng in số
#include <fstream>  // Để đọc từ file
using namespace std;
namespace seneca {
    Drink::Drink() : m_size('\0') {
        m_name = nullptr;
        m_price = 0.0;
    }

    // Copy constructor
    Drink::Drink(const Drink& other) : Billable(other), m_size(other.m_size) {}

    // Assignment operator
    Drink& Drink::operator=(const Drink& other) {
        if (this != &other) {
            Billable::operator=(other);  // Sao chép phần dữ liệu từ Billable
            m_size = other.m_size;  // Sao chép kích thước đồ uống
        }
        return *this;
    }

    // Destructor
    Drink::~Drink() {}

    // Phương thức tính giá đồ uống
    double Drink::price() const {
        double adjustedPrice = m_price;

        // Điều chỉnh giá dựa trên kích thước
        switch (m_size) {
            case 'S': adjustedPrice /= 2; break;  // Nhỏ: giảm một nửa giá
            case 'M': adjustedPrice *= 0.75; break;  // Vừa: giảm 25%
            case 'L': break;  // Lớn: giữ nguyên giá
            case 'X': adjustedPrice *= 1.5; break;  // Extra Large: tăng 50%
            default: break;
        }

        return adjustedPrice;
    }

    // Phương thức in thông tin đồ uống
    ostream& Drink::print(ostream& ostr) const {
        ostr << left << setw(28) << setfill('.') << m_name << " | ";

        // In kích thước đồ uống
        switch (m_size) {
            case 'S': ostr << "SML.."; break;
            case 'M': ostr << "MID.."; break;
            case 'L': ostr << "LRG.."; break;
            case 'X': ostr << "XLR.."; break;
            default: ostr << "....."; break;
        }

        ostr << " | " << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price() << endl;
        return ostr;
    }

    // Phương thức đặt đồ uống
    bool Drink::order() {
        cout << "Drink Size Selection\n";
        cout << "   1- Small\n";
        cout << "   2- Medium\n";
        cout << "   3- Large\n";
        cout << "   4- Extra Large\n";
        cout << "   0- Back\n";
        cout << ">";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: setSize('S'); break;
            case 2: setSize('M'); break;
            case 3: setSize('L'); break;
            case 4: setSize('X'); break;
            case 0: return false;
            default: cout << "Invalid choice, try again!" << endl; return false;
        }

        return true;
    }
    // Phương thức kiểm tra xem đồ uống đã được đặt chưa
    bool Drink::ordered() const {
        return m_size != ' ';
    }
    // Phương thức đọc thông tin đồ uống từ file
    ifstream& Drink::read(ifstream& file) {
        if (file) {
            char temp[100];
            file.getline(temp, 100, ',');  // Đọc tên đồ uống
            name(temp);
            
            file >> m_price;  // Đọc giá đồ uống
            file.ignore();  // Bỏ qua dấu '\n' còn lại

            m_size = ' ';  // Đặt lại kích thước đồ uống mặc định

            return file;
        }
        return file;
    }

    // Phương thức thiết lập kích thước đồ uống
    void Drink::setSize(char size) {
        m_size = size;
    }
}
