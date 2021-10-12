#pragma once

#include <iostream>
#include <vector>

#include <wire.hpp>

namespace lg {

/**
 * @brief base node for all gates / circuits
 */
class node {
public:
	/**
	 * @brief construct the node
	 *
	 * @param i the amount of inputs
	 * @param o the amount of outputs
	 */
	node(int i, int o);
	virtual ~node();

	/**
	 * @return the amount of inputs
	 */
	int inputs() const;

	/**
	 * @return the amount of outputs
	 */
	int outputs() const;

	/**
	 * @return true if all inputs are linked
	 */
	bool is_complete() const;

	/**
	 * @brief link a node's output into this node's input
	 *
	 * @param n the node's output to link
	 * @param o the given node's output gate number
	 * @param i this node's input gate number
	 */
	void link_in(node* n, int o, int i);

	/**
	 * @brief link this node's output into another node's input
	 *
	 * @param n the node's input to link
	 * @param o this node's output gate number
	 * @param i the given node's input gate number
	 */
	void link_out(node* n, int o, int i);

	/**
	 * @brief detach a specific input gate
	 *
	 * @param gate the gate to clear
	 */
	void clear_in(int gate);

	/**
	 * @brief detach a specific output gate
	 *
	 * @param gate the gate to clear
	 * @param n (optional) if not null, removes only the output link containing this node
	 */
	void clear_out(int gate, node* n = nullptr);

	/**
	 * @brief tests what the result of this node would be given an input
	 *
	 * @param in the input
	 * @returns the result of that input
	 */
	virtual std::vector<bool> test(std::vector<bool> in) const;

	/**
	 * @brief tests what the result of this node would be given an input
	 *
	 * @param in an input, with each character of the string being 0 or 1
	 * @returns the result of that input
	 */
	std::vector<bool> test(std::string in) const;

	/**
	 * @brief used in gates::IN to mark this node as an abstract input
	 */
	virtual bool is_circuit_in() const;

	/**
	 * @brief used in gates::OUT to mark this node as an abstract output
	 */
	virtual bool is_circuit_out() const;

	//// -- UPDATE / RESOLUTION METHODS -- ////

	/**
	 * @brief marks this node as unresolved. only resolvable once all input nodes have resolved
	 */
	virtual void mark_unresolved();

	/**
	 * @return true if this node is resolved
	 */
	virtual bool is_resolved() const;

	/**
	 * @brief tries to resolve this node by recursively trying to resolve all inputs
	 * @remarks if the node is already marked as resolved, this does nothing
	 */
	virtual void resolve();

	/**
	 * @brief retrieve the value at the given input gate
	 *
	 * @param gate the input gate
	 * @return on or off
	 *
	 * @remarks throws if node not resolved
	 */
	bool input(int gate) const;

	/**
	 * @brief retrieve the result at the given output gate
	 *
	 * @param gate the output gate to retrieve
	 * @return on or off
	 *
	 * @remarks throws if node not resolved
	 */
	bool result(int gate) const;

protected:
	/**
	 * @brief compute the result at the given output gate
	 *
	 * @remarks at this stage, all inputs are guaranteed resolved
	 */
	virtual bool compute(int gate) const = 0;

	//// -- SPECIALTY CIRCUIT METHODS -- ////

	/**
	 * @brief directly copy the given wire into the gate
	 *
	 * @param gate the gate to override
	 * @param w the overriding wire
	 */
	void set_input_wire(int gate, wire w);

	/**
	 * @brief retrieve a copy of the wire at the specified input gate
	 *
	 * @param gate the input gate
	 * @return the wire at that gate
	 */
	wire get_input_wire(int gate) const;

	/**
	 * @brief directly copy the given set of output wires into the gate
	 *
	 * @param gate the gate to override
	 * @param ws the overriding wires
	 */
	void set_output_wires(int gate, std::vector<wire> ws);

	/**
	 * @brief retrieve a copy of the wires at the specified output gate
	 *
	 * @param gate the output gate
	 * @return the wires at that gate
	 */
	std::vector<wire> get_output_wires(int gate) const;

	/**
	 * @brief mark this node as resolved manually
	 */
	void mark_resolved();

	/**
	 * @brief copy all compute() results into m_result
	 */
	void copy_results();

	mutable bool m_testing;					  /// true during the test() method
	mutable std::vector<bool> m_test_input;	  /// set to the test input during

private:
	const int m_input_ct;	 /// the amount of inputs
	const int m_output_ct;	 /// the amount of outputs

	bool m_resolved;			  /// is this node resolved?
	std::vector<bool> m_result;	  /// the result of this node

	std::vector<wire> m_inputs;					/// pointers to all node inputs
	std::vector<std::vector<wire>> m_outputs;	/// pointers to all node outputs
};

}

std::ostream& operator<<(std::ostream& os, const lg::node& n);

