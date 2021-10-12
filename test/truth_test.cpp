#include "truth_test.hpp"

using namespace lg;

bool truth_test(const util::truth_table& a, util::truth_table expected) {
	if (a.size() != expected.size()) return false;
	for (const auto& [i, o] : a) {
		if (expected[i] != o) return false;
	}
	return true;
}
