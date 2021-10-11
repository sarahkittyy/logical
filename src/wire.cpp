#include "wire.hpp"

wire::wire()
	: to(nullptr),
	  gate(0),
	  oti(true) {
}

bool wire::empty() const {
	return to == nullptr;
}
