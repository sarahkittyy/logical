#include "node.hpp"

#include <algorithm>
#include <functional>
#include <stdexcept>

node::node(int i, int o)
	: m_testing(false),
	  m_input_ct(i),
	  m_output_ct(o),
	  m_resolved(false),
	  m_result(false) {
	m_inputs.resize(inputs());
	m_outputs.resize(outputs());
	m_result.resize(outputs());
}

node::~node() {
}

int node::inputs() const {
	return m_input_ct;
}

int node::outputs() const {
	return m_output_ct;
}

bool node::is_complete() const {
	return std::none_of(m_inputs.cbegin(), m_inputs.cend(), std::mem_fn(&wire::empty));
}

void node::link_in(node* n, int o, int i) {
	// remove any existing link
	clear_in(i);
	// create the oti link
	n->m_outputs[o].emplace_back();
	wire& oti = n->m_outputs[o].back();
	oti.gate  = i;
	oti.to	  = this;
	oti.oti	  = true;

	// create the ito link
	wire& ito = m_inputs[i];
	ito.gate  = o;
	ito.to	  = n;
	ito.oti	  = false;
}

void node::link_out(node* n, int o, int i) {
	// remove any existing link
	n->clear_in(i);
	// create the oti link
	m_outputs[o].emplace_back();
	wire& oti = m_outputs[o].back();
	oti.gate  = i;
	oti.to	  = n;
	oti.oti	  = true;

	// create the ito link
	wire& ito = n->m_inputs[i];
	ito.gate  = o;
	ito.to	  = this;
	ito.oti	  = false;
}

void node::clear_in(int gate) {
	if (gate >= inputs() || gate < 0) throw std::runtime_error("gate is out of bounds");
	wire& l = m_inputs[gate];
	if (l.empty()) return;
	node* n = l.to;
	l.to	= nullptr;
	n->clear_out(l.gate, this);
}

void node::clear_out(int gate, node* n) {
	if (gate >= outputs() || gate < 0) throw std::runtime_error("gate is out of bounds");
	std::vector<wire>& ls = m_outputs[gate];
	if (n == nullptr) {
		// clear the input gate of each linked node
		std::for_each(ls.begin(), ls.end(), [](wire& l) {
			if (l.empty()) return;
			l.to->clear_in(l.gate);
		});
		// clear the vector
		ls.clear();
	} else {
		auto l = std::find_if(ls.begin(), ls.end(), [n](wire& l) {
			return !l.empty() && l.to == n;
		});
		if (l == ls.end()) return;
		l->to->clear_in(l->gate);
		ls.erase(l);
	}
}

std::vector<bool> node::test(std::vector<bool> in) const {
	if (in.size() != inputs())
		throw std::runtime_error("test input size does not equal node input size");
	std::vector<bool> out;
	out.resize(outputs());

	m_testing	 = true;
	m_test_input = in;

	for (int i = 0; i < outputs(); ++i) {
		out[i] = compute(i);
	}

	m_testing = false;

	return out;
}

std::vector<bool> node::test(std::string in) const {
	if (in.size() != inputs())
		throw std::runtime_error("test input size does not equal node input size");
	std::vector<bool> input;
	for (auto& ch : in) {
		if (ch == '0')
			input.push_back(false);
		else if (ch == '1')
			input.push_back(true);
		else
			throw std::runtime_error("unexpected character in input string");
	}
	return test(input);
}

bool node::is_circuit_in() const {
	return false;
}

bool node::is_circuit_out() const {
	return false;
}

void node::mark_unresolved() {
	m_resolved = false;
}

bool node::is_resolved() const {
	return m_resolved;
}

void node::resolve() {
	if (is_resolved()) return;
	m_resolved = true;
	// for each input link
	for (wire& link : m_inputs) {
		// checks
		if (link.empty()) continue;
		if (link.oti) throw std::runtime_error("input link should be in to out, not out to in");
		// resolve it if not resolved
		node& n = *link.to;
		if (!n.is_resolved()) n.resolve();
	}
	copy_results();
}

void node::copy_results() {
	// compute each output node and store
	for (int i = 0; i < outputs(); ++i) {
		m_result[i] = compute(i);
	}
}

bool node::result(int gate) const {
	if (!is_resolved()) throw std::runtime_error("attempt to query result of unresolved node");
	if (gate >= outputs() || gate < 0) throw std::runtime_error("gate is out of bounds");
	return m_result.at(gate);
}

void node::set_input_wire(int gate, wire w) {
	m_inputs[gate] = w;
}

wire node::get_input_wire(int gate) const {
	return m_inputs.at(gate);
}

void node::set_output_wires(int gate, std::vector<wire> ws) {
	m_outputs[gate] = ws;
}

std::vector<wire> node::get_output_wires(int gate) const {
	return m_outputs.at(gate);
}

void node::mark_resolved() {
	m_resolved = true;
}

bool node::input(int gate) const {
	if (gate >= inputs() || gate < 0) throw std::runtime_error("gate is out of bounds");

	/// for the test() method
	if (m_testing) {
		return m_test_input[gate];
	}

	const wire& l = m_inputs.at(gate);
	if (l.empty()) return false;
	if (l.oti) throw std::runtime_error("input link should be in to out, not out to in");
	const node& n = *l.to;
	if (!n.is_resolved()) throw std::runtime_error("input link is not resolved");
	return n.result(l.gate);
}

std::ostream& operator<<(std::ostream& os, const node& n) {
	os << n.inputs() << "i" << n.outputs() << "o";
	if (!n.is_resolved()) {
		os << "{unresolved}";
		return os;
	}
	os << "{";
	for (int i = 0; i < n.inputs(); ++i) {
		os << n.input(i);
	}
	os << ",";
	for (int i = 0; i < n.outputs(); ++i) {
		os << n.result(i);
	}
	os << "}";
	return os;
}
