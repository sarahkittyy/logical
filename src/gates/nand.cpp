#include "gates/nand.hpp"

namespace lg::gates {

NAND::NAND()
	: node(2, 1) {
}

bool NAND::compute(int gate) const {
	return !(input(0) && input(1));
}

}
