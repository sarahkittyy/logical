#pragma once

#include <node.hpp>

namespace gates {

class XOR : public node {
public:
	XOR();

	bool compute(int gate) const;
};

}
