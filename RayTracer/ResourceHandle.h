#pragma once
#include <functional>


class ResourceHandle {
public:
	ResourceHandle(std::function<void()> constructor, std::function<void()> destructor);
	ResourceHandle(const ResourceHandle&) = delete;
    ResourceHandle& operator=(const ResourceHandle&) = delete;
	virtual ~ResourceHandle();
	
private:
	std::function<void()> destructor;
};
