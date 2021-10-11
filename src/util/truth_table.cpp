#include "util/truth_table.hpp"

#include <algorithm>
#include <cmath>
#include <iomanip>

namespace util {

truth_table gen_truth_table(const node& n) {
	truth_table table;

	// amount of inputs possible
	const int input_states = std::pow(2, n.inputs());

	for (int i = 0; i < input_states; ++i) {
		// simple trick: i can be turned into a vector of boolean just by converting it
		// to binary.
		// eg. if n.inputs() = 3, input_states = 8,
		// so we'd have 000, 001, 010, 011, 100, 101, 110, 111 (0-7, which is i)

		std::vector<bool> input;
		input.resize(n.inputs());
		int bit = 0;
		std::generate_n(input.begin(), n.inputs(), [i, &bit]() {
			bool res = static_cast<bool>((i >> bit) & 1);
			bit++;
			return res;
		});
		table[input] = n.test(input);
	}

	return table;
}

truth_table gen_truth_table(const node& n, std::vector<bool> input) {
	truth_table table;
	table[input] = n.test(input);
	return table;
}

truth_table gen_truth_table(const node& n, std::string in) {
	std::vector<bool> input;
	for (auto& ch : in) {
		if (ch == '0')
			input.push_back(false);
		else if (ch == '1')
			input.push_back(true);
		else
			throw std::runtime_error("unexpected character in input string");
	}
	return gen_truth_table(n, input);
}

}

static std::ostream& operator<<(std::ostream& os, const std::vector<bool>& b) {
	for (const auto& val : b) os << (val ? "1" : "0");
	return os;
}

std::ostream& operator<<(std::ostream& os, const util::truth_table& table) {
	const int input_size  = table.begin()->first.size();
	const int output_size = table.begin()->second.size();
	const int table_width = 1 + input_size + 1 + output_size + 1;

	std::ios_base::fmtflags saved_flags(os.flags());

	// top bar
	os << "+";
	for (int i = 0; i < table_width - 2; ++i) {
		os << "-";
	}
	os << "+" << std::endl;

	// header
	os << "|i";
	for (int i = 0; i < input_size - 1; ++i) {
		os << " ";
	}
	os << "|o";
	for (int i = 0; i < output_size - 1; ++i) {
		os << " ";
	}
	os << "|" << std::endl;

	// sep bar
	os << "+";
	for (int i = 0; i < input_size; ++i) {
		os << "-";
	}
	os << "+";
	for (int i = 0; i < output_size; ++i) {
		os << "-";
	}
	os << "+" << std::endl;

	// table
	for (auto& [input, output] : table) {
		os << "|" << input << "|" << output << "|" << std::endl;
	}

	// bottom bar
	os << "+";
	for (int i = 0; i < table_width - 2; ++i) {
		os << "-";
	}
	os << "+" << std::endl;

	os.flags(saved_flags);

	return os;
}
