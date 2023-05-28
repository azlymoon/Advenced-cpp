//#include "bin_manip.h"
//#include <iostream>
//
//bin_manip::OutputManip<int32_t> bin_manip::write_int32(int32_t c) {
//	return bin_manip::OutputManip<int32_t> (bin_manip::write_int32, c);
//}
//
//bin_manip::OutputManip<bool> bin_manip::write_bool(bool c) {
//	return bin_manip::OutputManip<bool>(bin_manip::write_bool, c);
//}
//
//bin_manip::OutputManip<std::string> bin_manip::write_c_str(std::string c) {
//	return bin_manip::OutputManip<std::string>(bin_manip::write_c_str, c);
//}
//
//bin_manip::InputManip<int32_t> bin_manip::read_int32(int32_t& c) {
//	return bin_manip::InputManip<int32_t>(bin_manip::read_int32, c);
//}
//
//bin_manip::InputManip<bool> bin_manip::read_bool(bool c) {
//	return bin_manip::InputManip<bool>(bin_manip::read_bool, c);
//}
//
//bin_manip::InputManip<std::string> bin_manip::read_c_str(std::string c) {
//	return bin_manip::InputManip<std::string>(bin_manip::read_c_str, c);
//}
//
//std::ostream& bin_manip::write_int32(std::ostream& stream, const int32_t& c) {
//	stream << c;
//	return stream;
//}
//
//std::ostream& bin_manip::write_bool(std::ostream& stream, const bool& c) {
//	stream << c;
//	return stream;
//}
//
//std::ostream& bin_manip::write_c_str(std::ostream& stream, const std::string& c) {
//	stream << c;
//	return stream;
//}
//
//std::istream& bin_manip::read_int32(std::istream& stream, int32_t& c) {
//	stream >> c;
//	return stream;
//}
//
//std::istream& bin_manip::read_bool(std::istream& stream, bool& c) {
//	stream >> c;
//	return stream;
//}
//
//std::istream& bin_manip::read_c_str(std::istream& stream, std::string& c) {
//	stream >> c;
//	return stream;
//}

#include "bin_manip.h"
#include <iostream>

template <typename T>
bin_manip::OutputManip<T> bin_manip::output(const T& v) {
	return bin_manip::OutputManip(v);
}

template <typename T>
bin_manip::InputManip<T> bin_manip::input(T& v) {
	return bin_manip::InputManip(v);
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, bin_manip::OutputManip<T> out) {
	stream.write((char*)&out.val, sizeof(T));
	return stream;
}

template <typename T>
std::istream& operator>>(std::istream& stream, bin_manip::InputManip<T> in) {
	stream.read((char*)&in.val, sizeof(T));
	return stream;
}