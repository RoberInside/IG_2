#ifndef __Plano_H__
#define __Plano_H__
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
	void rotateX(float angulo);
	void setPosition(int x, int y, int z);

protected:
	std::string nombre;
	Ogre::SceneManager* mSM;
	Ogre::SceneNode* nPlano;
	Ogre::Entity* ePlano;
};
#endif