#ifndef BILLABLE_H
#define BILLABLE_H
#include <iostream>
#include <cstring>
using namespace std;
namespace seneca {
    class Billable {
        protected:
            char* m_name;    // Tên món ăn hoặc đồ uống (C-string)
            double m_price;  // Giá món (kiểu double)

            // Phương thức bảo vệ để cập nhật giá và tên món
            void price(double value) { m_price = value; }
            void name(const char* name);

        public:
            // Constructor, Destructor
            Billable();
            Billable(const Billable& other);  // Copy constructor
            Billable& operator=(const Billable& other);  // Assignment operator
            virtual ~Billable();

            // Phương thức ảo thuần túy (pure virtual methods)
            virtual double price() const;  // Trả về giá của món
            virtual ostream& print(ostream& ostr = cout) const = 0;  // In thông tin món
            virtual bool order() = 0;  // Đặt món
            virtual bool ordered() const = 0;  // Kiểm tra món đã được đặt chưa
            virtual ifstream& read(ifstream& file) = 0;  // Đọc dữ liệu từ file

            // Operator overloads
            friend double operator+(double money, const Billable& B);
            friend double& operator+=(double& money, const Billable& B);
            // Toán tử chuyển đổi sang const char* để lấy tên món
            operator const char*() const;
    };
}

#endif
