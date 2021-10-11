#include "gates/xnor.hpp"

namespace gates {

XNOR::XNOR()
	: node(2, 1) {
}

bool XNOR::compute(int gate) const {
	return input(0) == input(1);
}

}
