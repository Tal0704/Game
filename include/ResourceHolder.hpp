#pragma once
#include <string>
#include <map>
#include <memory>

template<typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id, const std::string& fileName);
	template<typename Paramater>
	void load(Identifier id, const std::string& fileName, const Paramater& param);
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"
