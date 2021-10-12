#pragma once

namespace lg {

class node;

/**
 * struct link - represents a unidirectional link towards a node and one of it's i/o gates
 */
struct wire {
	wire();

	node* to;	/// end node
	int gate;	/// the gate at that node
	bool oti;	/// output -> input?

	/**
	 * @return true if the link connects nowhere
	 */
	bool empty() const;
};

}
