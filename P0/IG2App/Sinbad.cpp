#include "Sinbad.h"

//Constructora
Sinbad::Sinbad(Ogre::SceneNode* oSN) {
	nSinbad = oSN;
	mSM = nSinbad->getCreator();
	createSinbad();
}

void Sinbad::createSinbad() {
	// ENTIDAD
	eSinbad = mSM->createEntity("Sinbad.mesh");

	//Nodo
	nSinbad = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	nSinbad->attachObject(eSinbad);

	//mSinbadNode->setPosition(400, 100, -300);
	nSinbad->setScale(20, 20, 20);
	//mSinbadNode->yaw(Ogre::Degree(-45));
	//mSinbadNode->showBoundingBox(true);
	//mSinbadNode->setVisible(false);
}