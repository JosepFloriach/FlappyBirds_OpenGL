//
// Created by Josep on 29/08/2018.
//

#include "PhysicsBody.h"
#include "../SceneNode.h"
#include "../../physics/WorldPhysics.h"

namespace scene
{
    const Component::ComponentDescriptor PhysicsBody::type= "PhysicsBody";
    Component::ComponentDescriptor PhysicsBody::Type() const
    {
        return type;
    }

    PhysicsBody::PhysicsBody()
        : mApplyGravity(false)
        , mVelocity(utils::Vector3<float>(0.f, 0.f, 0.f))
    {
    }

    std::unique_ptr<Component> PhysicsBody::Clone() const
    {
        return std::make_unique<PhysicsBody>(*this);
    }

    void PhysicsBody::SetApplyGravity(bool aApplyGravity)
    {
        mApplyGravity = aApplyGravity;
    }

    void PhysicsBody::Update(double aDt)
    {
        if (mApplyGravity)
        {
            mForce += physics::WorldPhysics::Gravity;
        }
        mVelocity = (mVelocity + mForce) * (aDt / 1000.f);
        mNode->Move(mVelocity);
    }

    bool PhysicsBody::IsGravityApplied() const
    {
        return mApplyGravity;
    }

    void PhysicsBody::AddForce(utils::Vector3<float> aForce)
    {
        mForce = aForce;
    }

    void PhysicsBody::Stop()
    {
        mForce = utils::Vector3<float>(0.f, 0.f, 0.f);
        mApplyGravity = false;
    }
}