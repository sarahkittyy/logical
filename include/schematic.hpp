#pragma once

#include <vector>

#include <gates/in.hpp>
#include <gates/out.hpp>
#include <node.hpp>

namespace lg {

/**
 * @brief a collection of nodes
 */
class schematic {
public:
	schematic();
	~schematic();

	/**
	 * @brief tick forward the simulation
	 *
	 */
	void tick();

	/**
	 * @brief is the schematic complete?
	 *
	 * @return true if all nodes have all their inputs linked
	 */
	bool is_complete() const;

	/**
	 * @brief add a node
	 *
	 * @param n the node to add
	 */
	void add(node* n);

	/**
	 * @brief remove a node
	 *
	 * @param n the node to remove
	 */
	void remove(node* n);

	/**
	 * @brief clear all nodes from the schematic
	 */
	void clear();

	/**
	 * @return the amount of nodes in the schematic
	 */
	int count() const;

	//// -- CIRCUIT METHODS -- ////

	/**
	 * @brief count how many abstract circuit INPUTS are in this schematic
	 */
	int circuit_in_count() const;

	/**
	 * @brief count how many abstract circuit OUTPUTS are in this schematic
	 */
	int circuit_out_count() const;

	/**
	 * @brief get the specific in circuit at given gate
	 *
	 * @param gate
	 */
	gates::IN* get_circuit_in(int gate);

	/**
	 * @brief get the specific out circuit at given gate
	 *
	 * @param gate
	 */
	gates::OUT* get_circuit_out(int gate);

private:
	std::vector<node*> m_nodes;	  /// all nodes in the schematic
};

}
