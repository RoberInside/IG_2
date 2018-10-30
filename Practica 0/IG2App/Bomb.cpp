#include "Bomb.h"

Bomb::Bomb(Ogre::SceneNode* oSN)
{
	nBomb = oSN;
	mSM = nBomb->getCreator();
	createBomb();
}


Bomb::~Bomb()
{
}

void Bomb::createBomb() {
	//ENTIDAD
	eBomb = mSM->createEntity("uv_sphere.mesh");
	
	//Material
	eBomb->setMaterialName("IG2App/Bomb");

	//Nodo
	nBomb = mSM->getRootSceneNode()->createChildSceneNode("nBomb");
	nBomb->attachObject(eBomb);
	nBomb->setPosition(0, -50, 0);

	//Animacion
	Ogre::Real duracion = 4;
	Ogre::Animation* animation = mSM->createAnimation("animVV", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0); //incluir modulo animaciones
	track->setAssociatedNode(nBomb);
	Ogre::Vector3 keyframePos = nBomb->getPosition();
	Ogre::Real longitudPaso = duracion / 4.0;
	Ogre::TransformKeyFrame* kf;
	int tamDesplazamiento = 20;

	nBomb->setInitialState();

	//Keyframe 0
	kf = track->createNodeKeyFrame(longitudPaso * 0);
	kf->setTranslate(keyframePos);

	//Keyframe 1: ARRIBA
	kf = track->createNodeKeyFrame(longitudPaso * 1);
	keyframePos += Ogre::Vector3::UNIT_Y * tamDesplazamiento;
	kf->setTranslate(keyframePos);

	//Keyframe 2: ORIGEN
	kf = track->createNodeKeyFrame(longitudPaso * 2);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * tamDesplazamiento;
	kf->setTranslate(keyframePos);

	//Keyframe 3: ABAJO
	kf = track->createNodeKeyFrame(longitudPaso * 3);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * tamDesplazamiento;
	kf->setTranslate(keyframePos);

	//Keyframe 4: ORIGEN
	kf = track->createNodeKeyFrame(longitudPaso * 4);
	keyframePos += Ogre::Vector3::UNIT_Y * tamDesplazamiento;
	kf->setTranslate(keyframePos);


	animationState = mSM->createAnimationState("animVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	
}

void Bomb::frameRendered(const Ogre::FrameEvent& evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
}