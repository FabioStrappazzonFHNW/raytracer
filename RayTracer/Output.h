#pragma once
#include <memory>


class RendererHandle;
class WindowHandle;
class Surface;

class Output
{
public:
	struct impl;
	~Output();
	static Output& instance();
	Output(const Output&) = delete;
	Output& operator= (const Output&) = delete;
	Output(Output&&) = delete;
	Output& operator=(Output&&) = delete;
	
	void updateScreen();
	const RendererHandle& getRenderer() const;
	const WindowHandle& getWindow() const;
	const Surface* getWall();
	const Surface* getGrace();
	const Surface* getUffizi();

private:
	Output();

	std::unique_ptr<impl> pimpl;
};

