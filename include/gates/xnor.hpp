#pragma once

#include <node.hpp>

namespace lg::gates {

class XNOR : public node {
public:
	XNOR();

	bool compute(int gate) const;
};

}
