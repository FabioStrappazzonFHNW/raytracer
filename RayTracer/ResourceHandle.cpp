#include "ResourceHandle.h"

ResourceHandle::ResourceHandle(std::function<void()> constructor, std::function<void()> destructor):
	destructor(destructor) {
	constructor();
}

ResourceHandle::~ResourceHandle() {
	if(destructor) {
		destructor();
	}
}
