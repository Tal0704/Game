#pragma once
#include <CommandQueue.hpp>
#include <Character.hpp>
#include <SpriteNode.hpp>
#include <SceneNode.hpp>
#include <ResourceHolder.hpp>
#include <array>
#include <Textures.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class World
	: public sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);

	void draw();
	void update(const sf::Time& dt);

	CommandQueue& getCommandQueue();
private:
	enum Layer
	{
		Background,
		ForeGround,
		LayerCount
	};

	ResourceHolder<sf::Texture, Textures::ID> mTextures;
	void loadTextures();
	void buildScene();

	Character* mCharacter;

	sf::RenderWindow& mWindow;
	sf::View mView;

	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mLayers;
	CommandQueue mCommandQueue;
};
