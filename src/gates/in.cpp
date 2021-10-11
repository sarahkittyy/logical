#include "gates/in.hpp"

#include <stdexcept>

namespace gates {

IN::IN()
	: node(1, 1) {
}

bool IN::is_circuit_in() const {
	return true;
}

bool IN::compute(int gate) const {
	return input(0);
}

}
