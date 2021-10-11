#pragma once

#include <node.hpp>

namespace gates {

class XNOR : public node {
public:
	XNOR();

	bool compute(int gate) const;
};

}
