#pragma once
#include <vector>
#include <memory>
#include <Components/BaseComponent.h>

struct Entity 
{
	int EntityIndex = 0;
	std::vector<std::unique_ptr<Component>> EntityComponents;
};