#include "gates/or.hpp"

namespace gates {

OR::OR()
	: node(2, 1) {
}

bool OR::compute(int gate) const {
	return input(0) || input(1);
}

}
