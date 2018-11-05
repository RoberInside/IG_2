#pragma once
#include "EntityClass.h"


class Plano :
	public EntityClass
{
public:
	//Constructora
	Plano(Ogre::SceneNode* oSN, std::string name);

	//Destructora
	~Plano() {};

	void createPlano();
	Ogre::Entity* getEntity() { return ePlano; }
	Ogre::SceneNode* getNode() { return nPlano; }

	
	void setPosition(int x, int y, int z);

	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void frameRendered(const Ogre::FrameEvent& evt);

protected:
	std::string nombre;
	Ogre::SceneManager* mSM;
	Ogre::SceneNode* nPlano;
	Ogre::Entity* ePlano;
	float rotacion;
};