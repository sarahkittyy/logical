#pragma once

#include <node.hpp>

namespace gates {

/**
 * @brief abstract gate used only in schematics to denote a circuit output
 */
class OUT : public node {
public:
	OUT();

	bool is_circuit_out() const;

	bool compute(int gate) const;

	using node::set_output_wires;
};

}
