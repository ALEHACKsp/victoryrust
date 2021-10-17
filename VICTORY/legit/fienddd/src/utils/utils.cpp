#include "common.hpp"

namespace Utils {
	void Error(const std::string& s) {
		printf("[ERROR] %s\n", s.c_str());
		throw std::runtime_error(s);
	}
}