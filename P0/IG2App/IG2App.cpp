#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include "Toy.h"
#include "Sinbad.h"
#include "Plano.h"

#include "OgrePlane.h"
#include "OgreMovablePlane.h"


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

  //CAMARA REFLEJO
  Camera* reflexCam = mSM->createCamera("reflexCamera");
  reflexCam->setNearClipDistance(1);
  reflexCam->setFarClipDistance(10000);
  reflexCam->setAutoAspectRatio(true);

  mCamNode->attachObject(reflexCam);
 


  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  //vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  //mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz"); //Luz fija al escenario
  mLightNode = mCamNode->createChildSceneNode("nLuz"); //Luz se mueve con la c�mara
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // SINBAD

  Ogre::SceneNode* snSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("Sinbad");
  Sinbad* sinbadObj = new Sinbad(snSinbadNode);

 // Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");

  //mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
  //mSinbadNode->attachObject(ent);

  //mSinbadNode->setPosition(400, 100, -300);
  //mSinbadNode->setScale(20, 20, 20);
  //mSinbadNode->yaw(Ogre::Degree(-45));
  //mSinbadNode->showBoundingBox(true);
  //mSinbadNode->setVisible(false);

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
  planeObj->getEntity()->setMaterialName("IG2App/plano");


  //PLANO DEL REFLEJO
  MeshManager::getSingleton().createPlane("mReflex1080x800", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  MovablePlane(Vector3::UNIT_Y, 0), 1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::NEGATIVE_UNIT_Z);


  /*Ogre::Entity* eReflex = mSM->createEntity("Reflejo", "mReflex1080x800", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  Ogre::SceneNode* snReflex = mSM->getRootSceneNode()->createChildSceneNode("Reflejo");
  snReflex->attachObject(eReflex);*/

  //reflexCam->enableReflection(eReflex);

  //Ogre::MovablePlane* reflexPlane = new MovablePlane(Vector3::UNIT_Y, 0);

  //reflexPlane->

  /*
  Ogre::SceneNode* snReflex = mSM->getRootSceneNode()->createChildSceneNode("Reflejo");
  Plano* reflexObj = new Plano(snReflex, "reflejo");
  reflexObj->getEntity()->setMaterialName("Reflex");
  reflexObj->rotateX(1.55f);
  reflexObj->setPosition(0, 0, -100);
  //snReflex->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(90));
  
  */

  /*reflexCam->enableReflection(reflexPlane);
  reflexCam->enableCustomNearClipPlane(reflexPlane);*/


  // Creamos una entidad donde almacenaremos el plano con la malla dada
  //Ogre::Entity* entPlane = mSM->createEntity("Plano", "mPlane1080x800", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  //entPlane->setMaterialName("IG2APP/plano");

  //El nodo del Plano
  //mPlanoNode = mSM->getRootSceneNode()->createChildSceneNode("nPlano");
  //mSM->getRootSceneNode()->addChild(mPlanoNode);
  //mPlanoNode->attachObject(entPlane);

  //mPlanoNode->setPosition(0, -100, 0);
  //mPlanoNode->setVisible(true);

  //------------------------------------------------------------------------

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
