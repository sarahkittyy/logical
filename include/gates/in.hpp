#pragma once

#include <node.hpp>

class circuit;

namespace gates {

/**
 * @brief abstract gate used only in schematics to denote a circuit input
 */
class IN : public node {
public:
	IN();

	bool is_circuit_in() const;

	bool compute(int gate) const;

	using node::set_input_wire;

	using node::m_test_input;
	using node::m_testing;
};

}
