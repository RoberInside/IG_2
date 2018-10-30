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

	//Animaciones
	andar();
	kabumAnim();

	Ruta->setEnabled(true);
}

void Sinbad::createSinbad() {
	// ENTIDADES
	eSinbad = mSM->createEntity("Sinbad.mesh");
	eSword1 = mSM->createEntity("Sword.mesh");
	eSword2 = mSM->createEntity("Sword.mesh");

	//Nodo
	nSinbad = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	nSinbad->attachObject(eSinbad);

	//Propiedades Sinbad
	nSinbad->setPosition(200, 2, -150);
	nSinbad->setScale(20, 20, 20);
	//mSinbadNode->yaw(Ogre::Degree(-45));
	//mSinbadNode->showBoundingBox(true);
	//mSinbadNode->setVisible(false);

	//Propiedades Espadas
	eSinbad->attachObjectToBone("Handle.R", eSword1);
	eSinbad->attachObjectToBone("Sheath.L", eSword2);
}


bool Sinbad::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	switch (evt.keysym.sym) {

		case SDLK_r:
			switchAnimation();
			break;

		case SDLK_b:
			activarBomba();
			break;
		
	}
	return false;
}

void Sinbad::kabumAnim() {
	//RunTop->setEnabled(true);
	//RunTop->setEnabled(true);

	//KABUUM!!!
	Ogre::Real duracionBum = 20;
	Ogre::Animation* animationBum = mSM->createAnimation("animKabum", duracionBum);
	Ogre::NodeAnimationTrack* trackBum = animationBum->createNodeTrack(0); //incluir modulo animaciones
	trackBum->setAssociatedNode(nSinbad);
	Ogre::Vector3 keyframePosBum = nSinbad->getPosition();
	Ogre::Real longitudPasoBum = duracionBum / 4.2;
	Ogre::Real tiempoGiroBum = 4 / 4.2;
	Ogre::TransformKeyFrame* kfBum;
	int tamDesplazamientoZBum = 600;
	int tamDesplazamientoYBum = 50;
	int tamDesplazamientoXBum = 400;

	Ogre::Vector3 srcBum(0, 0, 1);
	//1 hacia la bomba
	Ogre::Vector3 destBum(-1, 0, 0);
	//2 plantado en el suelo
	Ogre::Vector3 dest2Bum(0, 1, 0);

	Ogre::Quaternion quatBum = srcBum.getRotationTo(destBum);
	Ogre::Quaternion quat2Bum = srcBum.getRotationTo(dest2Bum);

	//nSinbad->setInitialState();

	//Keyframe 0 Se detiene
	kfBum = trackBum->createNodeKeyFrame(longitudPasoBum * 0);
	kfBum->setTranslate(keyframePosBum);

	//Keyframe 1: Se gira hacia la bomba
	kfBum = trackBum->createNodeKeyFrame(longitudPasoBum * 0.2);
	kfBum->setRotation(quatBum);
	kfBum->setTranslate(keyframePosBum);

	//Keyframe 3: Anda hacia la bomba
	kfBum = trackBum->createNodeKeyFrame(longitudPasoBum * 1);
	keyframePosBum += Ogre::Vector3::NEGATIVE_UNIT_X * tamDesplazamientoXBum;
	kfBum->setRotation(quatBum);
	kfBum->setTranslate(keyframePosBum);

	//Keyframe 4: Se tumba hacia arriba
	kfBum = trackBum->createNodeKeyFrame(longitudPasoBum * 1.2);
	kfBum->setRotation(quat2Bum);
	keyframePosBum += Ogre::Vector3::NEGATIVE_UNIT_Y * tamDesplazamientoXBum;
	kfBum->setTranslate(keyframePosBum);
	//RunTop->setEnabled(false);
	//RunBase->setEnabled(false);

	//Keyframe 5: Arrastrado por la corriente
	kfBum = trackBum->createNodeKeyFrame(longitudPasoBum * 3);
	keyframePosBum += Ogre::Vector3::UNIT_X * tamDesplazamientoXBum;
	kfBum->setRotation(quat2Bum);
	kfBum->setTranslate(keyframePosBum);

	Kabum = mSM->createAnimationState("animKabum");
	Kabum->setLoop(false);
	Kabum->setEnabled(false);
	//animationBum->setInterpolationMode();
}

void Sinbad::activarBomba() {
	Ruta->setEnabled(false);
	//RunBase->setEnabled(false);
	//RunTop->setEnabled(false);
	Kabum->setEnabled(true);
}

void Sinbad::switchAnimation() {
	Dance->setEnabled(!Dance->getEnabled());
	RunBase->setEnabled(!RunBase->getEnabled());
	RunTop->setEnabled(!RunTop->getEnabled());

	eSinbad->detachObjectFromBone(eSword1);

	if (Dance->getEnabled()) {
		//Dejar de correr
		Ruta->setEnabled(false);
		//Guardar la espada
		eSinbad->attachObjectToBone("Sheath.R", eSword1);
	}
	else {
		//Seguir corriendo
		Ruta->setEnabled(true);
	}

	if (RunTop->getEnabled()) eSinbad->attachObjectToBone("Handle.R", eSword1);
}


void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if (Dance->getEnabled()) Dance->addTime(evt.timeSinceLastFrame);
	if (RunBase->getEnabled()) RunBase->addTime(evt.timeSinceLastFrame);
	if (RunTop->getEnabled()) RunTop->addTime(evt.timeSinceLastFrame);
	if (Ruta->getEnabled()) Ruta->addTime(evt.timeSinceLastFrame);
	if (Kabum->getEnabled()) Kabum->addTime(evt.timeSinceLastFrame);
}

void Sinbad::andar() {
	//Animacion andar dando vueltas
	//Animacion
	Ogre::Real duracion = 8;
	Ogre::Animation* animation = mSM->createAnimation("animRuta", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0); //incluir modulo animaciones
	track->setAssociatedNode(nSinbad);
	Ogre::Vector3 keyframePos = nSinbad->getPosition();
	Ogre::Real longitudPaso = duracion / 4.2;
	Ogre::Real tiempoGiro = 4 / 4.2;
	Ogre::TransformKeyFrame* kf;
	int tamDesplazamientoZ = 600;
	int tamDesplazamientoX = 800;

	Ogre::Vector3 src(0, 0, 1);
	//1
	Ogre::Vector3 dest(-1, 0, 0);
	//2
	Ogre::Vector3 dest2(0, 0, -1); //(1,0,0) = 180º //(0,-1,0) plancha //(0,0,-1)
	//3
	Ogre::Vector3 dest3(1, 0, 0);
	//4
	Ogre::Vector3 dest4(0, 0, 1);

	Ogre::Quaternion quat = src.getRotationTo(dest);
	Ogre::Quaternion quat2 = src.getRotationTo(dest2);
	Ogre::Quaternion quat3 = src.getRotationTo(dest3);
	Ogre::Quaternion quat4 = src.getRotationTo(dest4);

	nSinbad->setInitialState();

	//Keyframe 0
	kf = track->createNodeKeyFrame(longitudPaso * 0);
	kf->setRotation(quat4);
	kf->setTranslate(keyframePos);

	//Keyframe 1: Adelante
	kf = track->createNodeKeyFrame(longitudPaso * 1);
	keyframePos += Ogre::Vector3::UNIT_Z * tamDesplazamientoZ;
	kf->setTranslate(keyframePos);

	//Keyframe 2: Girar
	kf = track->createNodeKeyFrame(longitudPaso * 1.2);
	kf->setRotation(quat);
	kf->setTranslate(keyframePos);
	//keyframeRot += (std::sqrt(0.5), 0, std::sqrt(0.5), 0);

	//Keyframe 3: Izquierda
	kf = track->createNodeKeyFrame(longitudPaso * 2);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * tamDesplazamientoX;
	kf->setRotation(quat);
	kf->setTranslate(keyframePos);

	//Keyframe 4: Girar
	kf = track->createNodeKeyFrame(longitudPaso * 2.2);
	kf->setRotation(quat2);
	kf->setTranslate(keyframePos);

	//Keyframe 5: Atras
	kf = track->createNodeKeyFrame(longitudPaso * 3);
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Z * tamDesplazamientoZ;
	kf->setRotation(quat2);
	kf->setTranslate(keyframePos);

	//Keyframe 6: Girar
	kf = track->createNodeKeyFrame(longitudPaso * 3.2);
	kf->setRotation(quat3);
	kf->setTranslate(keyframePos);

	//Keyframe 7: Derecha
	kf = track->createNodeKeyFrame(longitudPaso * 4);
	keyframePos += Ogre::Vector3::UNIT_X * tamDesplazamientoX;
	kf->setTranslate(keyframePos);
	kf->setRotation(quat3);

	//Keyframe 8: Girar
	kf = track->createNodeKeyFrame(longitudPaso * 4.2);
	kf->setRotation(quat4);
	kf->setTranslate(keyframePos);

	Ruta = mSM->createAnimationState("animRuta");
	Ruta->setLoop(true);
	Ruta->setEnabled(true);
	//animation->setInterpolationMode();
}