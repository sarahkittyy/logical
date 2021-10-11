#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <circuit.hpp>
#include <node.hpp>
#include <schematic.hpp>

namespace util {

/**
 * @brief create schematics without having to manage node memory manually
 */
class schematic_factory {
public:
	/**
	 * @brief adds a node to the schematic
	 *
	 * @tparam T the type of node to add
	 * @param name the name of the node
	 * @param args the arguments to pass to the node's constructor
	 */
	template <typename T, typename... Args>
	std::shared_ptr<T> add(std::string name, Args... args) {
		if (m_nodes.contains(name)) {
			throw std::runtime_error("Node " + name + " already exists.");
		}
		m_nodes.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(name),
			std::forward_as_tuple(std::make_shared<T>(args...)));
		std::shared_ptr<node> n = m_nodes[name];
		m_schem.add(n.get());
		return std::dynamic_pointer_cast<T>(n);
	}

	/**
	 * @brief ports in a schematic factory as a circuit
	 *
	 * @param name circuit name
	 * @param fac factory to use as a circuit
	 */
	std::shared_ptr<circuit> add(std::string name, const schematic_factory& fac);

	/**
	 * @brief shorthand to add multiple circuit IN gates
	 *
	 * @param names a list of names for all the inputs to add
	 */
	void add_inputs(std::initializer_list<std::string> names);

	/**
	 * @brief shorthand to add multiple circuit OUT gates
	 *
	 * @param names a list of names for all the outputs to add
	 */
	void add_outputs(std::initializer_list<std::string> names);

	/**
	 * @brief retrieves a reference to the node given it's name
	 */
	template <typename T = node>
	std::shared_ptr<T> get(std::string name) {
		if (!m_nodes.contains(name)) {
			throw std::out_of_range("No node named " + name + " found.");
		}
		return m_nodes[name];
	}

	/**
	 * @brief delete a node given its name
	 *
	 * @param name the name of the node to delete
	 */
	void del(std::string name);

	/**
	 * @brief connect the output of node a to the input of node b
	 *
	 * @param a node a
	 * @param b node b
	 * @param o the output gate of node a
	 * @param i the input gate of node b
	 */
	void connect(std::string a, std::string b, int o, int i);

	/**
	 * @brief retrieve the internal schematic
	 */
	schematic& schem();

private:
	/// storage of all the nodes in the factory
	std::unordered_map<std::string, std::shared_ptr<node>> m_nodes;
	/// storage of copies of all schematic factories
	std::unordered_map<std::string, std::shared_ptr<schematic_factory>> m_factories;
	schematic m_schem;	 /// the internal schematic
};

};
