#ifndef WORLD_H
#define WORLD_H

#include "SFML\Graphics.hpp"
#include "util\ResourceHolder.hpp"
#include "util\ResourceIdentifier.hpp"
#include "scene\SceneNode.hpp"
#include "scene\SpriteNode.hpp"
#include "commands\CommandQueue.hpp"
#include "util\Foreach.hpp"
#include "entities\Pickup.hpp"
#include "scene\ParticleNode.hpp"
#include "graphics\BloomEffect.hpp"
#include "sound\SoundPlayer.hpp"
#include "scene\SoundNode.hpp"
#include <array>


class World : private sf::NonCopyable{

public:
	

public:
	explicit World(sf::RenderTarget& outputTarget, FontHolder& fonts, SoundPlayer& sounds);
	void update(sf::Time dt);
	void draw();

	CommandQueue& getCommandQueue();
	bool gameStatus() const;

private:
	void loadTextures();
	void buildScene();

	sf::FloatRect getViewBounds() const;

	void handleCollisions();

private:
	enum Layer{
		Background,
		LowerAir,
		UpperAir,
		LayerCount
	};

private:
	sf::View mWorldView;
	TextureHolder mTextures;
	FontHolder& mFonts;
	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;
	sf::RenderTarget& mTarget;
	sf::RenderTexture mSceneTexture;
	BloomEffect mBloomEffect;
	SoundPlayer& mSounds;

	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;

	CommandQueue mCommandQueue;
	
	std::vector<Aircraft*> mActiveEnemies;

	bool gameOver;
	
};


#endif