#include "gates/xor.hpp"

namespace lg::gates {

XOR::XOR()
	: node(2, 1) {
}

bool XOR::compute(int gate) const {
	return input(0) != input(1);
}

}
