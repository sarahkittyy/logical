#include "gates/not.hpp"

namespace lg::gates {

NOT::NOT()
	: node(1, 1) {
}

bool NOT::compute(int gate) const {
	return !input(0);
}

}
