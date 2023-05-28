#pragma once
#include <stdint.h>
#include "employees.h"

namespace bin_manip {
    template <typename T>
    struct OutputManip {
        const T& val;
    public:
        OutputManip(const T& v) : value(v) {};
    };

    template <typename T>
    struct InputManip {
         T& val;
    public:
        InputManip(T& v) : value(v) {};
    };

    template <typename T>
    OutputManip<T> output(const T&);

    template <typename T>
    InputManip<T> input(T&);
}

template <typename T>
std::ostream& operator<<(std::ostream&, bin_manip::OutputManip<T>);
template <typename T>
std::ostream& operator<<(std::ostream&, bin_manip::OutputManip<std::string>);

template <typename T>
std::istream& operator>>(std::istream&, bin_manip::InputManip<T>);
template <typename T>
std::istream& operator>>(std::istream&, bin_manip::InputManip<std::string>);