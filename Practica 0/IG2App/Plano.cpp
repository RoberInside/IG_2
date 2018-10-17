#include "Plano.h"


//Constructora
Plano::Plano(Ogre::SceneNode* oSN, std::string name){
	nPlano = oSN;
	mSM = nPlano->getCreator();
	nombre = name;
	createPlano();
}

void Plano::createPlano() {
	//ENTIDAD
	ePlano = mSM->createEntity(nombre, "mPlane1080x800", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	//ePlano->setMaterialName("IG2App/plano");

	//Nodo
	nPlano = mSM->getRootSceneNode()->createChildSceneNode("n"+nombre);
	nPlano->attachObject(ePlano);
	nPlano->setPosition(0, -100, 0);


}

void Plano::setPosition(int x, int y, int z) {
	nPlano->setPosition(x, y, z);

}

void Plano::rotateX(float x) {
	nPlano->rotate(Ogre::Vector3(1, 0, 0), Ogre::Radian(x));
}