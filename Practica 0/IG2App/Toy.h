#pragma once
#include "EntityClass.h"

class Toy : 
	public EntityClass
{ 

public:
	//Constructora
	Toy(Ogre::SceneNode* oSN);

	//Destructora
	~Toy() {}

	//Generado
	void createToy();
	
	//Otros
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
	Ogre::Quaternion direccion;
};