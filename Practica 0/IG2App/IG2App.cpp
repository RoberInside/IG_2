#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgrePrerequisites.h>
#include <OgreMeshManager.h>
#include "Toy.h"
#include "Sinbad.h"
#include "Plano.h"
#include "Bomb.h"
//Includes para evitar error "pointer to incomplete class type not allowed"
#include <OgrePlane.h>
#include <OgreMovablePlane.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreTextureManager.h>
#include <OgreTexture.h>
#include <OgreTextureUnitState.h>
#include <OgreRenderTexture.h>
#include <OgreRenderWindow.h>
#include <OgreRenderTarget.h>
#include <OgreRenderTargetListener.h>

#include <Ogre.h>
#include <OgreRoot.h>

#include <iostream>
/*
#include <OgreFrameListener>
#include <OgreWindowEventUtilities>
#include <OgreInput>
#include <OgreOverlaySystem>
#include <OgreFileSystemLayer>
#include <OgreSGTechniqueResolverListerner.h>
*/

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch(evt.keysym.sym) {
		case SDLK_ESCAPE:
			getRoot()->queueEndRendering();
			break;
		case SDLK_p:
			mPlanoNode->rotate(Ogre::Vector3(1, 0, 0), Ogre::Radian(0.05), Ogre::Node::TS_LOCAL);
			//ToyNode->rotate(Ogre::Quaternion(Ogre::Vector3(0,0,0), Ogre::Vector3(0,0,0), Ogre::Vector3(0, 0, 0)), Ogre::Node::TS_LOCAL);
			//direccion
			break;

		case SDLK_r:
			//sinbadObj
			break;
	}
  /*
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  //else if (evt.keysym.sym == SDLK_???)
  */
  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);
  
  addInputListener(this);   
  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  


 


  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  //vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  //mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz"); //Luz fija al escenario
  mLightNode = mCamNode->createChildSceneNode("nLuz"); //Luz se mueve con la cámara
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------
   //Bomba
  Ogre::SceneNode* snBomb = mSM->getRootSceneNode()->createChildSceneNode("bomb");
  Bomb* bombObj = new Bomb(snBomb);
  addInputListener(bombObj); //NECESARIO PARA QUE SE VEA LA ANIMACION

  //------------------------------------------------------------------------
  // SINBAD

  Ogre::SceneNode* snSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("Sinbad");
  Sinbad* sinbadObj = new Sinbad(snSinbadNode, snBomb);
  addInputListener(sinbadObj);

  //Mostrar animaciones
  std::cout << "\n==LISTA DE ANIMACIONES DE SINBAD==" << std::endl;
  AnimationStateSet* aux = sinbadObj->getEntity()->getAllAnimationStates();
  auto it = aux->getAnimationStateIterator().begin();
  while (it != aux->getAnimationStateIterator().end()) {
	  auto s = it->first; //El iterador en su primera posicion almacena el nombre
	  ++it;
	  std::cout << s << std::endl;
  }

  //Mostrar esqueleto
  std::cout << "\n==LISTA DE HUESOS DE SINBAD==" << std::endl;
  auto skeleton = sinbadObj->getEntity()->getMesh()->getSkeleton();
  auto numBones = skeleton->getNumBones();
  for (int i = 0; i < numBones; i++) {
	  std::cout << skeleton->getBone(i)->getName() << std::endl;
  }
  std::cout << std::endl;


  //------------------------------------------------------------------------

  //PLANO

  //Usar metodo generar plano desde el MeshManager y luego pasar a la entidad
  //malla generada procedimentalmente, no desde un archivo como Sinbad
  //El metodo no devuelve el grid sino que lo almacena como un recurso
  //Debemos llamar al nombre de la malla creada al asignarlo a la entidad plano.
  //CreatePlane(nombre, zona de recursos a almacenarlo, tipo de plano, anchura, altura, segmentosAnchura, segmentosAltura, normales, numeroTexturas, numUtile, numVtile, UpVectorTextura) 
  MeshManager::getSingleton().createPlane("mPlane1080x800", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
	  Plane(Vector3::UNIT_Y, 0), 1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::NEGATIVE_UNIT_Z);
  Ogre::SceneNode* snPlane = mSM->getRootSceneNode()->createChildSceneNode("Plano");
  Plano* planeObj = new Plano(snPlane, "plano");
  planeObj->getEntity()->setMaterialName("Reflex");
  //planeObj->getEntity()->setMaterialName("IG2App/plano");

  //Camara reflejo
  Camera* reflexCam = mSM->createCamera("reflexCamera");
  reflexCam->setNearClipDistance(1);
  reflexCam->setFarClipDistance(10000);
  reflexCam->setAutoAspectRatio(true);
  mCamNode->attachObject(reflexCam);

  //Plano reflejo: no tiene malla, objeto abstracto matemático
  Ogre::MovablePlane* reflexPlane = new MovablePlane(Vector3::UNIT_Y, 0);
  
  //Pedir nodo del plano para agrerarle el plano de reflejo
  planeObj->getNode()->attachObject(reflexPlane);

  //Camara poner en el mismo nodo del planno
  //planeObj->getNode()->attachObject(reflexCam);
  reflexCam->enableReflection(reflexPlane);
  reflexCam->enableCustomNearClipPlane(reflexPlane);

  //Textura del plano (reflejo)
  Ogre::TexturePtr reflexTexturePtr = TextureManager::getSingleton().createManual(
	  "reflexTexture",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  TEX_TYPE_2D,
	  1080,
	  800,
	  0, PF_R8G8B8, TU_RENDERTARGET);
  
  //Añadimos un puerto de vista al RenderTarget con la nueva cámara
  Ogre::RenderTexture* renderTexture = reflexTexturePtr->getBuffer()->getRenderTarget(); // aqui deberia ser asi segun 
  //las transparencias pero no devuelve bien el puntero creado para usarlo y no se el motivo del error de clase 
  //incompleta cuando esta todo incluido.
  Viewport * vpt = renderTexture->addViewport(reflexCam);
  vpt->setClearEveryFrame(true);
  vpt->setBackgroundColour(ColourValue::Black);

  //Añadimos la nueva unidad de textura al material del panel
  TextureUnitState* tU = planeObj->getEntity()->getSubEntity(0)->getMaterial()->getTechnique(0)->getPass(0)->
	  createTextureUnitState("reflexTexture");
  //tU->setColourOperation(LBO_MODULATE); // backgroundColour -> black
										// LBO_ADD / LBO_ALPHA_BLEND / LBO_REPLACE
  tU->setColourOperation(LBO_ADD); // backgroundColour -> black
									  // LBO_ADD / LBO_ALPHA_BLEND / LBO_REPLACE
  tU->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
  tU->setProjectiveTexturing(true, reflexCam);
  

  //------------------------------------------------------------------------
  //TOY

  Ogre::SceneNode* snToy = mSM->getRootSceneNode()->createChildSceneNode("toy");
  Toy* toyObj = new Toy(snToy);
  snToy->setPosition(-200, -60, -40);
  addInputListener(toyObj);

  //------------------------------------------------------------------------
 
  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

