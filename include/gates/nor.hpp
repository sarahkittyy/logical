#pragma once

#include <node.hpp>

namespace lg::gates {

/**
 * @brief nor gate
 */
class NOR : public node {
public:
	NOR();

	bool compute(int gate) const;
};

}
