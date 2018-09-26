#pragma once
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreFrameListener.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

class Toy : 
	public OgreBites::InputListener 
{ 

public:
	//Constructora
	Toy(Ogre::SceneNode* oSN);

	//Destructora
	~Toy() {}

	//Generado
	void createToy();

	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void frameRendered(const Ogre::FrameEvent& evt);

protected:
	Ogre::SceneManager* mSM;
	Ogre::SceneNode* ToyNode;
	Ogre::Entity* eCabeza;
	Ogre::Entity* eNariz;
	Ogre::Entity* eCuerpo;
	Ogre::Entity* eOmbligo;
	Ogre::SceneNode* nCuerpo;
	Ogre::SceneNode* nCuello; // para determinar la dirección de desplazamiento (eje Z) y traslación (Z)
	Ogre::SceneNode* nCabeza;
	Ogre::SceneNode* nNariz;
	Ogre::SceneNode* nOmbligo;

	Ogre::Real desplazamiento;

};