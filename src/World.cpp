#include <World.hpp>
#include <iostream>
#include <SpriteNode.hpp>
#include <Helpers.hpp>

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mCommandQueue()
{
	loadTextures();
	buildScene();
}

void World::draw()
{
	mWindow.setView(mView);
	mWindow.draw(mSceneGraph);
}

void World::update(const sf::Time& dt)
{
	while (!mCommandQueue.isEmpty())
	{
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	}

	mSceneGraph.update(dt);
	auto characterPosition = mCharacter->getPosition();
	auto textureSize = mTextures.get(Textures::Background).getSize();
	mView.setCenter(characterPosition.x, textureSize.y / 2);

	sf::Vector2f position = mCharacter->getPosition();
	sf::FloatRect borderDistance = mCharacter->getGlobalBounds();
	sf::FloatRect viewBorders = mView.getViewport();

	position.y = std::max(position.y, viewBorders.top);
	position.y = std::min(position.y, viewBorders.top + mView.getSize().y - borderDistance.height);

	mCharacter->setPosition(position);
}

void World::loadTextures()
{
	mTextures.load(Textures::MainCharacter, "Media/Textures/main character.png");
	mTextures.load(Textures::Background, "Media/Textures/background.png");
}

void World::buildScene()
{
	for (auto& layer : mLayers)
	{
		SceneNode::Pointer l = std::make_unique<SceneNode>();
		layer = l.get();

		mSceneGraph.attachChild(std::move(l));
	}
	sf::IntRect rect = sf::IntRect(0, 0, 2000, mWindow.getSize().y);
	sf::Texture& txt = mTextures.get(Textures::Background);
	txt.setRepeated(true);
	std::unique_ptr<SpriteNode> background = std::make_unique<SpriteNode>(txt, rect);
	background->setPosition(0.f, 0.f);
	mLayers[Layer::Background]->attachChild(std::move(background));


	sf::Texture& charTxt = mTextures.get(Textures::MainCharacter);
	std::unique_ptr<Character> character = std::make_unique<Character>(charTxt);

	const auto& pos = character->getOrigin();
	const auto& bounds = character->getGlobalBounds();

	character->setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

	character->setPosition(100.f, 100.f);
	mCharacter = character.get();
	mLayers[Layer::ForeGround]->attachChild(std::move(character));

	mView.setSize(sf::Vector2f(mWindow.getSize()));
	auto p = mCharacter->getPosition();
	mView.setCenter(p.x, 0);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}
