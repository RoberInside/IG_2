#pragma once
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreFrameListener.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreVector2.h>
#include <OgrePrerequisites.h>

class EntityClass :
	public OgreBites::InputListener
{
public:
	EntityClass() {}
	~EntityClass() {}

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) { return true; };
	virtual void frameRendered(const Ogre::FrameEvent& evt) {};

protected:

};