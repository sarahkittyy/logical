#include "gates/out.hpp"

#include <stdexcept>

namespace lg::gates {

OUT::OUT()
	: node(1, 1) {
}

bool OUT::is_circuit_out() const {
	return true;
}

bool OUT::compute(int gate) const {
	return input(0);
}

}
