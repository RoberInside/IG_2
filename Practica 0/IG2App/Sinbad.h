#pragma once
#include "EntityClass.h"
#include "Bomb.h"

class Sinbad :
	public EntityClass
{
public:
	//Constructora
	Sinbad(Ogre::SceneNode* oSN, Bomb* bObj, Ogre::SceneNode* nToy);

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
	//void Muere(); //estaria bien separar las animaciones de "muerte" y de movimiento hacia la bomba

protected:
	bool actBum = false;
	bool muerto = false;

	Ogre::SceneManager* mSM; //scene Manager
	Ogre::SceneNode* nSinbad; //nodo Sinbad
	Ogre::SceneNode* snToy;		// nodo
	Ogre::Entity* eSinbad;	  //entidad Sinbad
	Bomb* bomb;				 //esto para activar el sistema de particulas desde la animacion

	Ogre::SceneNode* nBomba; //Nodo bomba

	Ogre::Entity* eSword1;
	Ogre::Entity* eSword2;

	
	Ogre::AnimationState* Dance;
	Ogre::AnimationState* RunBase;
	Ogre::AnimationState* RunTop;
	Ogre::AnimationState* Ruta;
	Ogre::AnimationState* Kabum;
	Ogre::AnimationState* Corriente;

};