#ifndef __Sinbad_H__
#define __Sinbad_H__
#include "EntityClass.h"

class Sinbad :
	public EntityClass
{
public:
	//Constructora
	Sinbad(Ogre::SceneNode* oSN);

	//Destructora
	~Sinbad() {};

	void createSinbad();

protected:
	Ogre::SceneManager* mSM;
	Ogre::SceneNode* nSinbad;
	Ogre::Entity* eSinbad;
};
#endif