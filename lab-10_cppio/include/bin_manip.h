#pragma once
#include <stdint.h>
#include "employees.h"

namespace bin_manip {
    template <typename T>
    struct OutputManip {
        const T& val;
    public:
        OutputManip(const T& v) : val(v) {};
    };

    template <typename T>
    struct InputManip {
         T& val;
    public:
        InputManip(T& v) : val(v) {};
    };

    template <typename T>
    OutputManip<T> output(const T&);

    template <typename T>
    InputManip<T> input(T&);
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, bin_manip::OutputManip<T> out) {
    stream.write((char*)&out.val, sizeof(T));
    return stream;
}
template <>
std::ostream& operator<<(std::ostream& stream, bin_manip::OutputManip<std::string> out) {
    stream.write(out.val.c_str(), (std::streamsize) out.val.length() + 1);
    return stream;
}

template <typename T>
std::istream& operator>>(std::istream& stream, bin_manip::InputManip<T> in) {
    stream.read((char*)&in.val, sizeof(T));
    return stream;
}
template <>
std::istream& operator>>(std::istream& stream, bin_manip::InputManip<std::string> in) {
    std::string buffer;
    char c;
    stream.get(c);
    while (c != '\0') {
        buffer += c;
        stream.get(c);
    }
    in.val = buffer;
    return stream;
}