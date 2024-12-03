#include "Food.h"
using namespace std;
#include <cstring> 
#include <iomanip>

namespace seneca {
    Food::Food() : m_ordered(false), m_child(false), m_customize(nullptr) {
        m_name = nullptr;
        m_price = 0.0;
    }

    Food::Food(const Food& other) : Billable(other), m_ordered(other.m_ordered), m_child(other.m_child) {
        if (other.m_customize) {
            m_customize = new char[strlen(other.m_customize) + 1];
            strcpy(m_customize, other.m_customize);
        } else {
            m_customize = nullptr;
        }
    }

    // Assignment operator
    Food& Food::operator=(const Food& other) {
        if (this != &other) {
            Billable::operator=(other);  // Sao chép phần dữ liệu từ Billable
            m_ordered = other.m_ordered;
            m_child = other.m_child;

            // Sao chép tùy chỉnh món ăn
            if (other.m_customize) {
                m_customize = new char[strlen(other.m_customize) + 1];
                strcpy(m_customize, other.m_customize);
            } else {
                m_customize = nullptr;
            }
        }
        return *this;
    }
    Billable* Food::clone() const {
        return new Food(*this);
    }
    // Destructor
    Food::~Food() {
        delete[] m_customize;
    }

    // Phương thức tính giá món ăn
    double Food::price() const {
        double adjustedPrice = m_price;

        // Nếu là phần trẻ em, giá sẽ giảm một nửa
        if (m_child) {
            adjustedPrice /= 2;
        }

        return adjustedPrice;
    }

    // Phương thức in thông tin món ăn
    ostream& Food::print(ostream& ostr) const {
        ostr << left << setw(28) << setfill('.') << m_name << " | ";

        // In phần ăn (Child hay Adult)
        if (ordered() && m_child) {
            ostr << "Child";
        } else {
            ostr << ".....";
        }

        ostr << " | " << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price();

        // In tùy chỉnh nếu có
        if (m_customize && &ostr == &cout) {
            ostr << " >> " << m_customize;
        }

        ostr << endl;
        return ostr;
    }

    // Phương thức đặt món ăn
    bool Food::order() {
        cout << "Food Size Selection\n";
        cout << "   1- Adult\n";
        cout << "   2- Child\n";
        cout << "   0- Back\n";
        cout << ">";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: setChild(false); break;
            case 2: setChild(true); break;
            case 0: return false;
            default: cout << "Invalid choice, try again!" << endl; return false;
        }

        m_ordered = true;

        // Nhập các tùy chỉnh món ăn
        cout << "Special instructions\n";
        cin.ignore();
        char buffer[256];
        cin.getline(buffer, 256);
        if (strlen(buffer) > 0) {
            setCustomization(buffer);
        } else {
            delete[] m_customize;
            m_customize = nullptr;
        }

        return true;
    }

    // Phương thức kiểm tra món ăn đã được đặt chưa
    bool Food::ordered() const {
        return m_ordered;
    }

    // Phương thức đọc thông tin món ăn từ file
    ifstream& Food::read(ifstream& file) {
        if (file) {
            char temp[100];
            file.getline(temp, 100, ',');  // Đọc tên món ăn
            name(temp);

            file >> m_price;  // Đọc giá món ăn
            file.ignore();  // Bỏ qua dấu '\n' còn lại

            m_child = false;  // Đặt lại phần ăn trẻ em mặc định
            m_ordered = false;  // Món ăn chưa được đặt
            delete[] m_customize;
            m_customize = nullptr;

            return file;
        }
        
        return file;
    }

    // Phương thức thiết lập món ăn là phần trẻ em hay không
    void Food::setChild(bool child) {
        m_child = child;
    }

    // Phương thức thiết lập tùy chỉnh món ăn
    void Food::setCustomization(const char* customization) {
        if (customization) {
            m_customize = new char[strlen(customization) + 1];
            strcpy(m_customize, customization);
        } else {
            m_customize = nullptr;
        }
    }

} // namespace seneca
