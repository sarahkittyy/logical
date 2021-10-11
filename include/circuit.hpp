#pragma once

#include <gates/in.hpp>
#include <gates/out.hpp>
#include <node.hpp>
#include <schematic.hpp>

/**
 * @brief a collection of gates, abstracted into a single node with inputs and outputs
 */
class circuit : public node {
public:
	/**
	 * @brief circuit constructor
	 *
	 * @param schem the internal circuit schematic.
	 *
	 * @remarks use gate type IN and OUT to denote inputs and outputs
	 */
	circuit(schematic* schem);

	~circuit();

	/**
	 * @brief computes the output value at the gate
	 *
	 * @param gate the output gate to compute
	 * @return on or off
	 *
	 * @remarks assumes all inputs are resolved
	 */
	bool compute(int gate) const;

	/**
	 * @brief marks the internal schematic as unresolved
	 */
	void mark_unresolved();

	/**
	 * @return true if the internal schematic is resolved
	 */
	bool is_resolved() const;

	/**
	 * @brief resolves the internal schematic
	 */
	void resolve();

	/**
	 * @brief tests what the result of this node would be given an input
	 *
	 * @param in the input
	 * @returns the result of that input
	 */
	std::vector<bool> test(std::vector<bool> in) const;

private:
	schematic* m_schem;	  /// internal schematic holding the composing circuits
};
