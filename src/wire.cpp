#include "wire.hpp"

namespace lg {

wire::wire()
	: to(nullptr),
	  gate(0),
	  oti(true) {
}

bool wire::empty() const {
	return to == nullptr;
}

}
