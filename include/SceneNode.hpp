#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include <SFML/Graphics.hpp>
#include <Command.hpp>
#include <Category.hpp>

struct Command;

class SceneNode
	: public sf::Drawable,
	public sf::Transformable,
	private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Pointer;

	SceneNode();

	void attachChild(Pointer child);
	Pointer detachChild(const SceneNode& node);

	void update(sf::Time deltaTime);

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;

	void onCommand(const Command& command, const sf::Time& dt);
	virtual unsigned int getCategory() const;

private:
	std::vector<Pointer> mChildren;
	SceneNode* mParent;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	void updateChildren(sf::Time deltaTime);
	virtual void updateCurrent(sf::Time deltaTime);
};
