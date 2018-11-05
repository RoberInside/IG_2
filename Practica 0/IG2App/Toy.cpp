#include "Toy.h"

//Constructora
Toy::Toy(Ogre::SceneNode* oSN): 
	desplazamiento(0)
{
	ToyNode = oSN;
	mSM = ToyNode->getCreator();
	createToy();
	


}


//Generado
void Toy::createToy() {
	//Entidades y sus mallas
	eCabeza = mSM->createEntity("sphere.mesh");
	eNariz = mSM->createEntity("sphere.mesh");
	eCuerpo = mSM->createEntity("sphere.mesh");
	eOmbligo = mSM->createEntity("sphere.mesh");

	//Jerarquia de nodos //No hacer nodos nietos
	nCuerpo = ToyNode->createChildSceneNode("cuerpo");
	nCuello = ToyNode->createChildSceneNode("cuello"); //Ver si queremos que cabeza se hijo de cuello
	nCabeza = ToyNode->createChildSceneNode("cabeza");
	nNariz = nCabeza->createChildSceneNode("nariz");
	nOmbligo = nCuerpo->createChildSceneNode("ombligo");

	//Acoplar las entidades a sus nodos correspondientes
	nCabeza->attachObject(eCabeza);
	nNariz->attachObject(eNariz);
	nCuerpo->attachObject(eCuerpo);
	nOmbligo->attachObject(eOmbligo);

	//Posicion y escala de cada nodo
	// OJO ESCALA AFECTA A TODO NO SOLO AL TAMAÑO, TAMBIEN A POSICION ETC
	nCuerpo->setScale(0.4, 0.4, 0.4);
	nCabeza->setScale(0.2, 0.2, 0.2); //0.5 respecto al 1 del cuerpo, que ya esta en 0.4
	nNariz->setScale(0.1, 0.1, 0.1); //0.4 de la escala de la cabeza
	nOmbligo->setScale(0.1, 0.1, 0.1);

	nCuerpo->setPosition(0, 0, 0);
	nCabeza->setPosition(0, 55, 0);		//Coordenadas relativas al cuerpo
	nNariz->setPosition(0, 0, 100);		//Desplazar el radio de la cabeza para que resalte
	nOmbligo->setPosition(0, 0, 100);	//Desplazar el radio de cuerpo para que resalte
}

bool Toy::keyPressed(const OgreBites::KeyboardEvent& evt) 
{

	switch (evt.keysym.sym){
		case SDLK_y:
			ToyNode->translate(Ogre::Vector3(0, 0, desplazamiento), Ogre::Node::TS_LOCAL);
			nCuerpo->rotate(Ogre::Vector3(1, 0, 0), Ogre::Radian(0.05));
			break;
		case SDLK_v:
			ToyNode->rotate(Ogre::Vector3(0,1,0), Ogre::Radian(45));
			break;
		case SDLK_t:
			ToyNode->translate(Ogre::Vector3(0, 0, -desplazamiento), Ogre::Node::TS_LOCAL);
			nCuerpo->rotate(Ogre::Vector3(1, 0, 0), Ogre::Radian(-0.05));
			break;
	}
	return true;
}

void Toy::frameRendered(const Ogre::FrameEvent& evt)
{
	desplazamiento = 50.0 * evt.timeSinceLastFrame;
}
