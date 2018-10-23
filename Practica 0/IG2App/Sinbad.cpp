#include "Sinbad.h"

//Constructora
Sinbad::Sinbad(Ogre::SceneNode* oSN) {
	nSinbad = oSN;
	mSM = nSinbad->getCreator();
	createSinbad();

	//ANIMACIONES

	//Baile
	Dance = eSinbad->getAnimationState("Dance");
	Dance->setLoop(true);
	Dance->setEnabled(false);

	//Correr
	//Piernas
	RunBase = eSinbad->getAnimationState("RunBase");
	RunBase->setLoop(true);
	RunBase->setEnabled(true);
	//Torso
	RunTop = eSinbad->getAnimationState("RunTop");
	RunTop->setLoop(true);
	RunTop->setEnabled(true);
	
	//Mostrar esqueleto
	//auto skeleton = eSinbad->getMesh()->getSkeleton();

	//Espadas
	//eSinbad->attachObjectToBone("Hueso", "Objeto");
}

void Sinbad::createSinbad() {
	// ENTIDAD
	eSinbad = mSM->createEntity("Sinbad.mesh");

	//Nodo
	nSinbad = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	nSinbad->attachObject(eSinbad);

	nSinbad->setPosition(200, 2, -150);
	nSinbad->setScale(20, 20, 20);
	//mSinbadNode->yaw(Ogre::Degree(-45));
	//mSinbadNode->showBoundingBox(true);
	//mSinbadNode->setVisible(false);
}


void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	Dance->addTime(evt.timeSinceLastFrame);
	RunBase->addTime(evt.timeSinceLastFrame);
	RunTop->addTime(evt.timeSinceLastFrame);
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	switch (evt.keysym.sym) {

	case SDLK_r:
		switchAnimation();
		break;
	}
	return false;
}
