//
// Created by Josep on 27/08/2018.
//

#ifndef ZEPTOLABTEST_EVENTPOOL_H
#define ZEPTOLABTEST_EVENTPOOL_H

#include <string>
#include <memory>
#include "../../scene/components/Collider.h"

namespace events
{
    class Event
    {
    public:
        Event() = default;
        virtual ~Event() = default;
        using DescriptorType = const char*;
        virtual DescriptorType Type() const = 0;
    };

    class EnterCollisionEvent final: public Event
    {
    public:
        EnterCollisionEvent() = default;
        virtual ~EnterCollisionEvent() = default;
        static const DescriptorType Descriptor;

        void SetNodes(scene::SceneNode* aFirst, scene::SceneNode* aSecond);
        void GetNodes(scene::SceneNode*& aFirst, scene::SceneNode*& aSecond) const;

        virtual DescriptorType Type() const override
        {
            return Descriptor;
        }
    private:
        scene::SceneNode* mFirstNode;
        scene::SceneNode* mSecondNode;
    };

    class ExitCollisionEvent final: public Event
    {
    public:
        ExitCollisionEvent() = default;
        virtual ~ExitCollisionEvent() = default;
        static const DescriptorType Descriptor;

        void SetNodes(scene::SceneNode* aFirst, scene::SceneNode* aSecond);
        void GetNodes(scene::SceneNode*& aFirst, scene::SceneNode*& aSecond) const;

        virtual DescriptorType Type() const override
        {
            return Descriptor;
        }

    private:
        scene::SceneNode* mFirstNode;
        scene::SceneNode* mSecondNode;
    };
}

#endif //ZEPTOLABTEST_EVENTPOOL_H
