/*
file: util_tostring.h
*/

#pragma once

#include <string>

namespace UTIL {

	template<typename TYPE> struct ToString;

	template<>
	struct ToString<unsigned int> {
		static std::string Type(unsigned int value) {
			std::string string, reverse;
			unsigned int div = 10;
			do {
				int digit = value % div;
				reverse += '0' + digit;
				value /= div;
			} while(value > div);
			for(std::string::reverse_iterator revIt(reverse.rbegin());
				revIt != reverse.rend(); ++revIt) {
				string += *revIt;
			}
			return string;
		}
	};

	template<>
	struct ToString<int> {
		static std::string Type(int value) {
			std::string sign;
			if(0 > value) {
				sign += '-';
				value *= -1;
			}
			return sign + ToString<unsigned int>::Type(value);
		}
	};

} // namespace UTIL