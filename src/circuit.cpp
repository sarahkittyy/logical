#include "circuit.hpp"

#include <stdexcept>

circuit::circuit(schematic* schem)
	: node(schem->circuit_in_count(), schem->circuit_out_count()),
	  m_schem(schem) {
	if (inputs() < 0 || outputs() <= 0) throw std::runtime_error("not enough inputs / outputs");
}

circuit::~circuit() {
}

bool circuit::compute(int gate) const {
	// return the value computed at the schematic's OUT gate
	return m_schem->get_circuit_out(gate)->compute(0);
}

void circuit::mark_unresolved() {
	node::mark_unresolved();
}

bool circuit::is_resolved() const {
	return node::is_resolved();
}

void circuit::resolve() {
	if (is_resolved()) return;
	mark_resolved();

	// if the input or output count has changed, the circuit is invalid
	if (m_schem->circuit_in_count() != inputs() || m_schem->circuit_out_count() != outputs()) {
		throw std::runtime_error("Input / Output count has changed since circuit construction.");
	}

	// copy all this circuit's input links directly into the IN gates
	for (int i = 0; i < inputs(); ++i) {
		gates::IN* in = m_schem->get_circuit_in(i);
		wire cin	  = get_input_wire(i);
		in->set_input_wire(0, cin);
	}
	// copy all this circuit's output links directly into the OUT gates
	for (int i = 0; i < outputs(); ++i) {
		gates::OUT* out		   = m_schem->get_circuit_out(i);
		std::vector<wire> cout = get_output_wires(i);
		out->set_output_wires(0, cout);
	}

	// tick the schematic
	m_schem->tick();

	// copy compute() values into this entire node's output
	copy_results();
}

std::vector<bool> circuit::test(std::vector<bool> input) const {
	// set all inputs to test mode
	for (int i = 0; i < inputs(); ++i) {
		gates::IN* in = m_schem->get_circuit_in(i);
		in->m_testing = true;
		in->m_test_input.resize(1);
		in->m_test_input[0] = input[i];
	}

	// tick
	m_schem->tick();

	// save all outputs
	std::vector<bool> out;
	out.resize(outputs());
	for (int i = 0; i < outputs(); ++i) {
		out[i] = compute(i);
	}

	// unset all inputs from test mode
	for (int i = 0; i < inputs(); ++i) {
		gates::IN* in = m_schem->get_circuit_in(i);
		in->m_testing = false;
	}

	// if the circuit was already resolved before
	if (is_resolved()) {
		// re-tick the schematic
		m_schem->tick();
	}

	return out;
}
