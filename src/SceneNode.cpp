#include <SceneNode.hpp>

SceneNode::SceneNode()
	: mParent(nullptr)
{
}

void SceneNode::attachChild(Pointer child)
{
	child->mParent = this;
	this->mChildren.push_back(std::move(child));
}

SceneNode::Pointer SceneNode::detachChild(const SceneNode& node)
{
	auto foundValue = std::find_if(this->mChildren.begin(), this->mChildren.end(), [&](SceneNode::Pointer& p) -> bool
		{ return p.get() == &node; });
	assert(foundValue != this->mChildren.end());
	SceneNode::Pointer result = std::move(*foundValue);
	result->mParent = nullptr;
	this->mChildren.erase(foundValue);
	return std::move(result);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= this->getTransform();
	this->drawCurrent(target, states);
	for (const auto& child : this->mChildren)
		child->draw(target, states);
}

void SceneNode::update(sf::Time deltaTime)
{
	this->updateCurrent(deltaTime);
	this->updateChildren(deltaTime);
}

void SceneNode::updateChildren(sf::Time deltaTime)
{
	for (const auto& child : this->mChildren)
		child->update(deltaTime);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const auto* node = this; node != nullptr; node = node->mParent)
	{
		transform = node->getTransform() * transform;
	}
	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	// turning this->getWorldTransform() to sf::Vector2f (point) and returning it
	return this->getWorldTransform() * sf::Vector2f();
}

void SceneNode::updateCurrent(sf::Time deltaTime)
{

}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}

void SceneNode::onCommand(const Command& command, const sf::Time& dt)
{
	if (command.category & getCategory())
	{
		command.action(*this, dt);
	}

	for (auto& child : mChildren)
		child->onCommand(command, dt);
}
