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

	void switchAnimation();

	//Animaciones
	void andar();
	void kabumAnim();
	void activarBomba();

protected:
	Ogre::SceneManager* mSM; //scene Manager
	Ogre::SceneNode* nSinbad; //nodo Sinbad
	Ogre::Entity* eSinbad;	  //entidad Simbad

	Ogre::Entity* eSword1;
	Ogre::Entity* eSword2;

	
	Ogre::AnimationState* Dance;
	Ogre::AnimationState* RunBase;
	Ogre::AnimationState* RunTop;
	Ogre::AnimationState* Ruta;
	Ogre::AnimationState* Kabum;
};