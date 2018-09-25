#pragma once
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

class Toy : public OgreBites::InputListener { 

public:
	//Constructora
	Toy(Ogre::SceneNode* oSN) {
		ToyNode = oSN;
		mSM = ToyNode->getCreator();
		createToy();
	}

	//Destructora
	~Toy() {}

	//Generado
	void createToy() {
		//Entidades y sus mallas
		eCabeza = mSM->createEntity("sphere.mesh");
		eNariz = mSM->createEntity("sphere.mesh");
		eCuerpo = mSM->createEntity("sphere.mesh");
		eOmbligo = mSM->createEntity("sphere.mesh");

		//Jerarquia de nodos
		nCuerpo = ToyNode->createChildSceneNode("cuerpo");
		nCuello = nCuerpo->createChildSceneNode("cuello"); //Ver si queremos que cabeza se hijo de cuello
		nCabeza = nCuerpo->createChildSceneNode("cabeza");
		nNariz = nCabeza->createChildSceneNode("nariz");
		nOmbligo = nCuerpo->createChildSceneNode("ombligo");

		//Acoplar las entidades a sus nodos correspondientes
		nCabeza->attachObject(eCabeza);
		nNariz->attachObject(eNariz);
		nCuerpo->attachObject(eCuerpo);
		nOmbligo->attachObject(eOmbligo);

		//Posicion y escala de cada nodo
		nCuerpo->setScale(40, 40, 40);
		nCabeza->setScale(20, 20, 20);
		nNariz->setScale(10, 10, 10);
		nOmbligo->setScale(10, 10, 10);

		nCuerpo->setPosition(0, 0, 0);
		nCabeza->setPosition(0, 30, 0);		//Coordenadas relativas al cuerpo
		nNariz->setPosition(20, 0, 0);		//Desplazar el radio de la cabeza para que resalte
		nOmbligo->setPosition(40, 0, 0);	//Desplazar el radio de cuerpo para que resalte
	}

	//virtual bool keyPressed(const Ogrebites::KeyboardEvent& evt){}

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


};