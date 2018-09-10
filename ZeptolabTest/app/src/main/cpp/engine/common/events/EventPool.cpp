//
// Created by Josep on 27/08/2018.
//

#include "EventPool.h"
namespace events
{
    const Event::DescriptorType EnterCollisionEvent::Descriptor     = "EVENT_ENTER_COLLISION";
    const Event::DescriptorType ExitCollisionEvent::Descriptor      = "EVENT_EXIT_COLLISION";

    void EnterCollisionEvent::SetNodes(scene::SceneNode *aFirst, scene::SceneNode *aSecond)
    {
        mFirstNode = aFirst;
        mSecondNode = aSecond;
    }

    void EnterCollisionEvent::GetNodes(scene::SceneNode *&aFirst, scene::SceneNode *&aSecond) const
    {
        aFirst = mFirstNode;
        aSecond = mSecondNode;
    }

    void ExitCollisionEvent::SetNodes(scene::SceneNode *aFirst, scene::SceneNode *aSecond)
    {
        mFirstNode = aFirst;
        mSecondNode = aSecond;
    }

    void ExitCollisionEvent::GetNodes(scene::SceneNode *&aFirst, scene::SceneNode *&aSecond) const
    {
        aFirst = mFirstNode;
        aSecond = mSecondNode;
    }
}

