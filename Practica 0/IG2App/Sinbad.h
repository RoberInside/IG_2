#pragma once
#include "EntityClass.h"

class Sinbad :
	public EntityClass
{
public:
	//Constructora
	Sinbad(Ogre::SceneNode* oSN);

	//Destructora
	~Sinbad() {};

	Ogre::Entity* getEntity() { return eSinbad; }
	void createSinbad();
	void frameRendered(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	void switchAnimation() { 
		Dance->setEnabled(!Dance->getEnabled()); 
		RunBase->setEnabled(!RunBase->getEnabled());
		RunTop->setEnabled(!RunTop->getEnabled());
	}

protected:
	Ogre::SceneManager* mSM;
	Ogre::SceneNode* nSinbad;
	Ogre::Entity* eSinbad;

	Ogre::AnimationState* Dance;
	Ogre::AnimationState* RunBase;
	Ogre::AnimationState* RunTop;

};