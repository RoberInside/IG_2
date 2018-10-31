#ifndef BOMB_H_
#define BOMB_H_

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
	void smokeParticle();

	//void rotateX(float angulo);
	//void setPosition(int x, int y, int z);
	

protected:
	Ogre::SceneManager* mSM; //Scene Manager
	Ogre::SceneNode* nBomb;
	Ogre::Entity* eBomb;

	//Animacion
	Ogre::AnimationState* animationState;

	//Sistema de particulas
	Ogre::Billboard* bb;
	Ogre::ParticleSystem* pSys;
};
#endif // !BOMB_H_

