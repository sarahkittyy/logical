#include "util/schematic_factory.hpp"

#include <stdexcept>

namespace util {

std::shared_ptr<circuit> schematic_factory::add(std::string name, const schematic_factory& fac) {
	if (m_factories.contains(name)) {
		throw std::runtime_error("Factory " + name + " already exists.");
	}
	m_factories.emplace(
		std::piecewise_construct,
		std::forward_as_tuple(name),
		std::forward_as_tuple(std::make_shared<schematic_factory>(fac)));
	return add<circuit>(name, &m_factories[name]->schem());
}

void schematic_factory::add_inputs(std::initializer_list<std::string> names) {
	for (auto& name : names) {
		add<gates::IN>(name);
	}
}

void schematic_factory::add_outputs(std::initializer_list<std::string> names) {
	for (auto& name : names) {
		add<gates::OUT>(name);
	}
}

void schematic_factory::del(std::string name) {
	if (!m_nodes.contains(name)) {
		throw std::out_of_range("No node named " + name + " found.");
	}
	m_schem.remove(m_nodes[name].get());
	m_nodes.erase(name);
}

void schematic_factory::connect(std::string a, std::string b, int o, int i) {
	std::shared_ptr<node> na = get(a);
	std::shared_ptr<node> nb = get(b);
	na->link_out(nb.get(), o, i);
}

schematic& schematic_factory::schem() {
	return m_schem;
}

}
