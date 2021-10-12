#pragma once

#include <node.hpp>

namespace lg::gates {

/**
 * @brief and gate
 */
class AND : public node {
public:
	AND();

	bool compute(int gate) const;
};

}
