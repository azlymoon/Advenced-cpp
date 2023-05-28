#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <string>
#include <vector>
namespace employees {
    class Employee {
    public:
        Employee(std::string, int32_t);
        Employee();
        virtual int salary() const = 0;
        void set_name(std::string);
        void set_base_salary(int);
        virtual void input(std::istream&) = 0;
        virtual void output(std::ostream&) const = 0;
        friend std::istream& operator>>(std::istream&, Employee&);
        friend std::ostream& operator<<(std::ostream&, const Employee&);
    protected:
        std::string _name;
        int32_t _base_salary;
    };

    class Developer : public Employee {
    public:
        Developer(
            std::string,
            int32_t, 
            bool
        );
        Developer();
        int salary() const;
        void set_has_bonus(bool);
        void input(std::istream&);
        void output(std::ostream&) const;
    private:
        bool _has_bonus;
    };

    class SalesManager : public Employee {
    public:
        SalesManager(
            std::string,
            int32_t, 
            int32_t, 
            int32_t
        );
        SalesManager();
        void set_sold_nm(int);
        void set_price(int);
        int salary() const;
        void input(std::istream&);
        void output(std::ostream&) const;
    private:
        int32_t _sold_nm, _price;
    };

    class EmployeesArray {
    public:
        void add(const Employee*);
        int total_salary() const;
        friend std::ostream& operator<<(std::ostream&, const EmployeesArray&);
    private:
        std::vector<const Employee*> _employees;
    };

    std::istream& operator>>(std::istream&, Employee&);
    std::ostream& operator<<(std::ostream&, const Employee&);
    std::ostream& operator<<(std::ostream&, const EmployeesArray&);
}

#endif
