#pragma once

#include <node.hpp>

namespace lg::gates {

/**
 * @brief nand gate
 */
class NAND : public node {
public:
	NAND();

	bool compute(int gate) const;
};

}
