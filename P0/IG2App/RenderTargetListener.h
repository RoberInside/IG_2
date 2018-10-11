#ifndef __RenderTargetListener_H__
#define __RenderTargetListener_H__
#include "Ogre.h"
#include "OgreRenderTargetListener.h" // esto falla porque no esta el bloque de memoria activo y no lo reconoce, no se porque.

class RenderTargetListener : public Ogre::RenderTargetListener
{
public:
	RenderTargetListener(Ogre::SceneNode* sceneNode);
	virtual ~RenderTargetListener();

	virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);	virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);

};
#endif
