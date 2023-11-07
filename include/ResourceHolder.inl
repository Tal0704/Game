#include "ResourceHolder.hpp"
#include <cassert>
#include <stdexcept>

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& fileName)
{
	std::unique_ptr<Resource> resource = std::make_unique<Resource>();
	try
	{
		resource->loadFromFile(fileName);
	}
	catch (const std::exception&)
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + fileName);
	}
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
template <typename Paramater>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& fileName, const Paramater& param)
{
	std::unique_ptr<Resource> resource = std::make_unique<Resource>();
	try
	{
		resource->loadFromFile(fileName, param);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("ResourceHHolder::load - Failed to load " + fileName);
	}
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

