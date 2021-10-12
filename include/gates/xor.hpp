#pragma once

#include <node.hpp>

namespace lg::gates {

class XOR : public node {
public:
	XOR();

	bool compute(int gate) const;
};

}
