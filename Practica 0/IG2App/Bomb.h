#pragma once
#include "EntityClass.h"


class Bomb :
	public EntityClass
{
public:
	Bomb(Ogre::SceneNode* oSN);
	~Bomb();

	void createBomb();
	Ogre::Entity* getEntity() { return eBomb; }
	Ogre::SceneNode* getNode() { return nBomb; }
	void frameRendered(const Ogre::FrameEvent& evt);
	//void rotateX(float angulo);
	//void setPosition(int x, int y, int z);

protected:
	Ogre::SceneManager* mSM; //Scene Manager
	Ogre::SceneNode* nBomb;
	Ogre::Entity* eBomb;

	//Animacion
	Ogre::AnimationState* animationState;
};

