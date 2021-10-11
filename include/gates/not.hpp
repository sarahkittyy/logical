#pragma once

#include <node.hpp>

namespace gates {

/**
 * @brief a standard NOT gate
 */
class NOT : public node {
public:
	NOT();

	bool compute(int gate) const;
};

}
