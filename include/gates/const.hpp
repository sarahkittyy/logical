#pragma once

#include <node.hpp>

namespace lg::gates {

/**
 * @brief gate that is always resolved, has no inputs, and returns a constant signal
 */
class CONST : public node {
public:
	/**
	 * @brief constructor
	 *
	 * @param value the signal to constantly emit (on or off)
	 */
	CONST(bool value);

	bool compute(int gate) const;

	/**
	 * @brief toggle the signal between on and off
	 */
	void toggle();

private:
	bool m_value;	/// the constant signal's value
};

}
