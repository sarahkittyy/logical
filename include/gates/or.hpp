#pragma once

#include <node.hpp>

namespace lg::gates {

class OR : public node {
public:
	OR();

	bool compute(int gate) const;
};

}
