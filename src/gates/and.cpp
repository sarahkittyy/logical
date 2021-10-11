#include "gates/and.hpp"

namespace gates {

AND::AND()
	: node(2, 1) {
}

bool AND::compute(int gate) const {
	return input(0) && input(1);
}

}
