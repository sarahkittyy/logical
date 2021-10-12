#include "gates/nor.hpp"

namespace lg::gates {

NOR::NOR()
	: node(2, 1) {
}

bool NOR::compute(int gate) const {
	return !(input(0) || input(1));
}

}
