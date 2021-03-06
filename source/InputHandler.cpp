#include "InputHandler.h"
#include "GridHelper.h"

InputHandler* handler;

//bunch of functions which handle console commands
void setNumCells(Ogre::StringVector& vec)
{
	if (vec.size() >= 2)
	{
		unsigned int count = atoi(vec[1].c_str());
		OgreConsole::getSingleton().print("Cell number changed");
		handler->setCellNumber(count);
	}
	else
	{
		OgreConsole::getSingleton().print("Invalid arguments: too few");
	}
}

void gotoPoint(Ogre::StringVector& vec)
{
	if (vec.size() >= 4)
	{
		int x = atoi(vec[1].c_str());
		int y = atoi(vec[2].c_str());
		int z = atoi(vec[3].c_str());
		handler->setCameraPosition(Ogre::Vector3(x,y,z));
	}
	else
	{
		OgreConsole::getSingleton().print("Invalid arguments: too few");
	}
}

InputHandler::InputHandler(void) :
	mPointerDown(false),
	mPickingMeshes(true),
	mCenterObject(false),
	mTracking(false),
	mHorizonLocked(false),
	mReverseMovementTarget(false),
	mRaySceneQuery(NULL),
	mSceneMgr(NULL),
	mObjectMgr(NULL),
	mCamera(NULL),
	mSelectedObject(NULL),
	mGridLineFactory(NULL),
	mGui(NULL)
{
	resetState();
	handler = this;
}

InputHandler::~InputHandler(void)
{
	mSceneMgr->destroyQuery(mRaySceneQuery);
	delete mGridLineFactory;
}

void InputHandler::setCamera(Ogre::Camera* camera)
{
	if (mGridLineFactory)
	{
		delete mGridLineFactory;
	}
	
	mCamera = camera;
	
	//we assume that we ALWAYS have a scene manager, if we also have a ray scene query
	if (mRaySceneQuery != NULL && mSceneMgr != NULL)
	{
		mSceneMgr->destroyQuery(mRaySceneQuery);
	}
	
	mSceneMgr = mCamera->getParentSceneNode()->getCreator();
	mRaySceneQuery = mSceneMgr->createRayQuery(Ogre::Ray());
	
	mGridLineFactory = new GridLineFactory(mSceneMgr);
}

void InputHandler::translate(InputHandler::Direction dir)
{
	switch (dir)
	{
		case DIR_LEFT:
			mTransVector.x -= 1; break;
		case DIR_RIGHT:
			mTransVector.x += 1; break;
		case DIR_FORWARD:
			mTransVector.z -= 1; break;
		case DIR_BACKWARD:
			mTransVector.z += 1; break;
		case DIR_DOWN:
			mTransVector.y -= 1; break;
		case DIR_UP:
			mTransVector.y += 1; break;
		default:
			std::cerr << "Warning: rotation used in InputHandler::translate" << std::endl;
	}
}

void InputHandler::rotate(InputHandler::Direction rot, bool isMouse, float mult)
{
	Ogre::Real speed = isMouse ? 1.0f / mMouseRotateSpeedDivisor : mKeyRotateSpeed;
	speed *= mult;
	
	switch (rot)
	{
		case ROT_UP:
			mRotVector.x += speed; break;
		case ROT_DOWN:
			mRotVector.x -= speed; break;
		case ROT_LEFT:
			mRotVector.y += speed; break;
		case ROT_RIGHT:
			mRotVector.y -= speed; break;
		case ROT_CCW:
			mRotVector.z += speed; break;
		case ROT_CW:
			mRotVector.z -= speed; break;
		default:
			std::cerr << "Warning: direction used in InputHandler::rotate" << std::endl;
	}
}

void InputHandler::changeSpeed(float numSteps)
{
	if (numSteps > 0)
	{
		mSpeedMult *= SPEED_PER_STEP * numSteps;
	}
	else if (numSteps < 0)
	{
		mSpeedMult /= SPEED_PER_STEP * -numSteps; //remember to get it back to positive values
	}
}

bool InputHandler::onPrimaryPointerDown(void)
{
	mPointerDown = true;
	
	clickOnObjects();
	
	return true;
}

bool InputHandler::onPrimaryPointerUp(void)
{
	mPointerDown = false;
	
	return true;
}

void InputHandler::resetCamera(void)
{
	mCameraNeedsReset = true;
}

void InputHandler::toggleObjectMode(void)
{
	mPickingMeshes = !mPickingMeshes;
}

void InputHandler::clickOnObjects(void)
{
	RocEyeObject* oldObject = mSelectedObject;
	
	deselectObject();
	
	tryPickObjects();
	
	if (mSelectedObject == oldObject)
	{
		deselectObject();
	}
}

void InputHandler::tryPickObjects(void)
{
	//we need to perform a scene query, first of all
	Ogre::Ray mouseRay(mCamera->getParentSceneNode()->getPosition(), mCamera->getDerivedDirection());
	mRaySceneQuery->setRay(mouseRay);
	mRaySceneQuery->setSortByDistance(true);
	mRaySceneQuery->setQueryTypeMask(mPickingMeshes ? Ogre::SceneManager::FX_TYPE_MASK : Ogre::SceneManager::ENTITY_TYPE_MASK);
	
	//execute the query
	Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();
	Ogre::RaySceneQueryResult::iterator iter = result.begin();
	
	//iterate through the results, and select the closest object
	for (; iter != result.end(); iter++)
	{
		if (iter->movable && iter->movable->getName().substr(0,5) != "tile[")
		{
			selectObject(iter->movable->getParentSceneNode());
			break; //return early if we've found what we want
		}
	}
}

void InputHandler::selectObject(Ogre::SceneNode* object)
{
	mSelectedObject = mObjectMgr->getObjectByName(object->getName());
	if (mSelectedObject)
	{
		mSelectedObject->getSceneNode()->showBoundingBox(true);
	}
}

void InputHandler::deselectObject(void)
{
	if (mSelectedObject)
	{
		mSelectedObject->getSceneNode()->showBoundingBox(false);
	}
	
	mSelectedObject = NULL;
}

void InputHandler::centerObject(void)
{
	mCenterObject = true;
}

void InputHandler::toggleObjectLock(void)
{
	mTracking = !mTracking;
	Ogre::SceneNode* target = mTracking && mSelectedObject ? mSelectedObject->getSceneNode() : NULL;
	mCamera->getParentSceneNode()->setAutoTracking(mTracking, target);
}

void InputHandler::toggleGridLines(bool centerOnTarget)
{
	
	if (!mGridLineFactory->isGridEmpty())
	{
		mGridLineFactory->removeGrid();
		return;
	}
	
	if (centerOnTarget && !mSelectedObject)
	{
		return;
	}
	
	Ogre::SceneNode* node = centerOnTarget ? mSelectedObject->getSceneNode() : mCamera->getParentSceneNode();
	Ogre::Vector3 centerPosition = GridHelper::roundToGrid(node->getPosition());
	mGridLineFactory->addGrid(centerPosition, 50);
}

void InputHandler::levelHorizon(void)
{
	//WHY could I not make this a one-line function? Gah, I'll have to do some thinking about rotations, see if there's a shorter way to do this.
	//I think there are also floating point errors that get amplified somewhere...
	
	int count = 0;
	do
	{
		const Ogre::Quaternion orient = mCamera->getParentSceneNode()->getOrientation();
		const Ogre::Radian roll = orient.getRoll();
		const Ogre::Degree yaw = orient.getYaw();
	
		Ogre::Degree finalRoll;
		if (yaw < Ogre::Degree(-90) || yaw > Ogre::Degree(90))
		{
			if ( (roll - Ogre::Radian(Ogre::Math::PI)) < Ogre::Radian(0.0001) && (roll - Ogre::Radian(Ogre::Math::PI)) > Ogre::Radian(-0.0001) )
			{
				break;
			}
			const Ogre::Degree targetRoll(180);
			if (roll < Ogre::Degree(0))
			{
				finalRoll = (targetRoll - roll);
			}
			else
			{
				finalRoll = -(targetRoll - roll);
			}
			if (finalRoll > Ogre::Degree(359.9)) //we DO NOT want to oscillate!
			{
				finalRoll = Ogre::Degree(0);
			}
		}
		else
		{
			if (roll < Ogre::Radian(0.0001)  && roll > Ogre::Radian(-0.0001))
			{
				break;
			}
			finalRoll = -roll;
		}
	
		const int dampFactor = 8; //this is important, otherwise we get oscillation
		mCamera->getParentSceneNode()->roll((finalRoll)/dampFactor);
	} while (++count < 10000); //make sure that we don't freeze
}

void InputHandler::toggleHorizonLock(void)
{
	mHorizonLocked = !mHorizonLocked;
	//this is required for rotate-about-target, but for some reason we seem to require TS_WORLD later on anyway for pure yaw
	mCamera->getParentSceneNode()->setFixedYawAxis(mHorizonLocked);
	
	if (mHorizonLocked)
	{
		levelHorizon();
	}
}

void InputHandler::toggleSnapToGrid(void)
{
	if (mSelectedObject)
	{
		mSelectedObject->setSnapToGrid(!mSelectedObject->getSnapToGrid());
	}
}

void InputHandler::execute(void)
{
	Ogre::Vector3 trans = mTransVector * mCameraSpeed * mSpeedMult;
	
	if (mPointerDown)
	{
		//save typing and function calls
		Ogre::SceneNode* node = mCamera->getParentSceneNode();
		
		//track where we move
		Ogre::Vector3 oldPos = node->_getDerivedPosition();
		node->translate(trans, Ogre::SceneNode::TS_LOCAL);
		Ogre::Vector3 newPos = node->_getDerivedPosition();
		
		if (mSelectedObject)
		{
			mSelectedObject->translate(newPos - oldPos);
		}
	}
	else
	{
		bool forceCameraMovement = (mTracking && !mReverseMovementTarget) || (!mTracking && mReverseMovementTarget);
		//Ogre::SceneNode* transObject = mSelectedObject && !forceCameraMovement ? mSelectedObject : mCamera->getParentSceneNode();
		//
		//transObject->translate(trans, Ogre::SceneNode::TS_LOCAL);
		
		if (mSelectedObject && !forceCameraMovement)
		{
			mSelectedObject->translate(trans);
		}
		else
		{
			mCamera->getParentSceneNode()->translate(trans, Ogre::SceneNode::TS_LOCAL);
		}
	}
	
	Ogre::SceneNode::TransformSpace yawSpace = mHorizonLocked ? Ogre::SceneNode::TS_WORLD : Ogre::SceneNode::TS_LOCAL;
	
	mCamera->getParentSceneNode()->pitch(Ogre::Degree(mRotVector.x * mSpeedMult));
	mCamera->getParentSceneNode()->yaw(Ogre::Degree(mRotVector.y * mSpeedMult), yawSpace);
	if (!mHorizonLocked)
	{
		mCamera->getParentSceneNode()->roll(Ogre::Degree(mRotVector.z * mSpeedMult));
	}
	
	if (mCameraNeedsReset)
	{
		Ogre::Quaternion orient(1,-1,0,0); //point straight down
		mCamera->getParentSceneNode()->setOrientation(orient);
	}
	
	if (mCenterObject && mSelectedObject)
	{
		mCamera->getParentSceneNode()->lookAt(mSelectedObject->getPosition(), Ogre::SceneNode::TS_WORLD);
	}
	
	resetState();
}

void InputHandler::resetState(void)
{
	mCameraNeedsReset = false;
	mCenterObject = false;
	mTransVector = Ogre::Vector3(0,0,0);
	mRotVector = Ogre::Vector3(0,0,0);
	mSpeedMult = 1;
}

void InputHandler::addConsoleCommands(void)
{
	mGui->addConsoleCommand("/setnumcells", setNumCells);
	mGui->addConsoleCommand("/goto", gotoPoint);
}
