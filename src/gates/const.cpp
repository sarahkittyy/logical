#include "gates/const.hpp"

namespace lg::gates {

CONST::CONST(bool value)
	: node(0, 1),
	  m_value(value) {
}

bool CONST::compute(int gate) const {
	return m_value;
}

void CONST::toggle() {
	m_value = !m_value;
}

}
