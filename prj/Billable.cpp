#include "Billable.h"
using namespace std;
#include <cstring>

namespace seneca {

    Billable::Billable() : m_name(nullptr), m_price(0.0) {}

    // Copy constructor
    Billable::Billable(const Billable& other) : m_price(other.m_price) {
        if (other.m_name) {
            m_name = new char[strlen(other.m_name) + 1];
            strcpy(m_name, other.m_name);
        } else {
            m_name = nullptr;
        }
    }

    // Assignment operator
    Billable& Billable::operator=(const Billable& other) {
        if (this != &other) {
            delete[] m_name;  // Xóa tên cũ
            m_price = other.m_price;
            if (other.m_name) {
                m_name = new char[strlen(other.m_name) + 1];
                strcpy(m_name, other.m_name);
            } else {
                m_name = nullptr;
            }
        }
        return *this;
    }

    // Destructor
    Billable::~Billable() {
        delete[] m_name;  // Giải phóng bộ nhớ của m_name
    }

    // Phương thức trả về giá của món
    double Billable::price() const {
        return m_price;
    }
    std::string Billable::name() const {
        return m_name;
    }

    Billable::operator const char*() const {
        return m_name ? m_name : "Unnamed";
    }

    // Operator overloads
    double operator+(double money, const Billable& B) {
        return money + B.price();
    }

    double& operator+=(double& money, const Billable& B) {
        money += B.price();
        return money;
    }

    // Phương thức cập nhật tên món
    void Billable::name(const char* name) {
        delete[] m_name;  // Giải phóng bộ nhớ cũ nếu có
        if (name) {
            m_name = new char[strlen(name) + 1];
            strcpy(m_name, name);
        } else {
            m_name = nullptr;
        }
    }

}
