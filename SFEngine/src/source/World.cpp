#include "../headers/World.h"

World::World(sf::RenderTarget& outputTarget, FontHolder& fonts, SoundPlayer& sounds) : 
mTarget(outputTarget),
mFonts(fonts),
mSounds(sounds),
mWorldView(outputTarget.getDefaultView()),
mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 5000.f),
mSpawnPosition(mWorldView.getSize().x/2.f, mWorldBounds.height - mWorldView.getSize().y /2.f),
mScrollSpeed(-50.f),
mPlayerAircraft(nullptr),
mActiveEnemies(),
gameOver(false)
{
	mSceneTexture.create(outputTarget.getSize().x, outputTarget.getSize().y);

	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);

}

void World::loadTextures(){

	mTextures.load(Resources::Textures::Grass, "Resources/img/Grass.jpg");
	mTextures.load(Resources::Textures::Particle, "Resources/img/Particle.png");
	mTextures.load(Resources::Textures::Explosion, "Resources/img/Explosion.png");

}

void World::buildScene(){

	//Initialize each layer
	for (std::size_t i = 0; i < LayerCount; ++i){

		Category::Type category = (i == LowerAir) ? Category::SceneAirLayer : Category::None;

		SceneNode::Ptr layer(new SceneNode(category));
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}


	//printf("%i\n", mSceneGraph.nbChildren());
	//Initialize desert sprite node
	sf::Texture& texture = mTextures.get(Resources::Textures::Grass);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

}

void World::draw(){

	if (PostEffect::isSupported()){

		mSceneTexture.clear();
		mSceneTexture.setView(mWorldView);
		mSceneTexture.draw(mSceneGraph);
		mSceneTexture.display();
		mBloomEffect.apply(mSceneTexture, mTarget);

	}

	else{
		mTarget.setView(mWorldView);
		mTarget.draw(mSceneGraph);
	}
}

void World::update(sf::Time dt){
	//printf("%i\n", mSceneGraph.getNodes().size());

	/*for (int i = 0; i < mSceneGraph.getNodes().size(); i++){
		SceneNode* n = mSceneGraph.getNode(i);
		if (n->getCategory() & Category::PlayerAircraft){
			auto p = static_cast<Aircraft*>(n);
			p->move(0.2f,0.f);
		}
			
	}
	*/


	//forward commands to the scene graph
	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	handleCollisions();	
	mSceneGraph.removeWrecks();
	//mSceneGraph.clearNodes();

	mSceneGraph.update(dt, mCommandQueue);
}

CommandQueue& World::getCommandQueue(){
	return mCommandQueue;
}

sf::FloatRect World::getViewBounds() const {
	return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}





void World::handleCollisions(){
	std::set < SceneNode::Pair > collisionPairs;
	mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);
	//printf("%i\n", collisionPairs.size());

	FOREACH(SceneNode::Pair pair, collisionPairs){
		
	}

}

bool World::gameStatus() const{
	return gameOver;
}

