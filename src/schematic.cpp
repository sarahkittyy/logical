#include "schematic.hpp"

#include <algorithm>
#include <functional>

schematic::schematic() {
}

schematic::~schematic() {
}

void schematic::tick() {
	std::for_each(m_nodes.begin(), m_nodes.end(), std::mem_fn(&node::mark_unresolved));
	std::for_each(m_nodes.begin(), m_nodes.end(), std::mem_fn(&node::resolve));
}

bool schematic::is_complete() const {
	return std::all_of(m_nodes.cbegin(), m_nodes.cend(), std::mem_fn(&node::is_complete));
}

void schematic::add(node* n) {
	m_nodes.push_back(n);
}

void schematic::remove(node* n) {
	auto pos = std::find(m_nodes.begin(), m_nodes.end(), n);
	if (pos != m_nodes.end()) {
		m_nodes.erase(pos);
	}
}

void schematic::clear() {
	m_nodes.clear();
}

int schematic::circuit_in_count() const {
	return std::count_if(m_nodes.cbegin(), m_nodes.cend(), std::mem_fn(&node::is_circuit_in));
}

int schematic::circuit_out_count() const {
	return std::count_if(m_nodes.cbegin(), m_nodes.cend(), std::mem_fn(&node::is_circuit_out));
}

gates::IN* schematic::get_circuit_in(int gate) {
	int ct	  = gate;
	auto item = std::find_if(m_nodes.begin(), m_nodes.end(), [&ct](node*& n) {
		if (n->is_circuit_in()) {
			if (ct == 0) {
				return true;
			} else {
				ct--;
			}
		}
		return false;
	});
	if (item == m_nodes.end()) {
		throw std::out_of_range("IN gate number out of bounds.");
	}
	return dynamic_cast<gates::IN*>(*item);
}

gates::OUT* schematic::get_circuit_out(int gate) {
	int ct	  = gate;
	auto item = std::find_if(m_nodes.begin(), m_nodes.end(), [&ct](node*& n) {
		if (n->is_circuit_out()) {
			if (ct == 0) {
				return true;
			} else {
				ct--;
			}
		}
		return false;
	});
	if (item == m_nodes.end()) {
		throw std::out_of_range("IN gate number out of bounds.");
	}
	return dynamic_cast<gates::OUT*>(*item);
}
