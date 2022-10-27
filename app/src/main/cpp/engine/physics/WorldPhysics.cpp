//
// Created by Josep on 30/08/2018.
//

#include "WorldPhysics.h"
#include "../common/events/EventDispatcher.h"

#include "../scene/components/ColliderBox.h"
#include "../scene/components/ColliderCircle.h"

namespace physics
{
    utils::Vector3<float> WorldPhysics::Gravity = utils::Vector3<float>(0.f, -9.8f, 0.f);

    class WorldPhysicsImpl
    {
    private:
        /**
         * Collider data stores a collider to be checked, and a vector of other colliders which can
         * be colliding with the one we are checking.
         */
        struct ColliderData
        {
            scene::Collider* mCheckingCollider;
            std::map<scene::Collider*, bool> mOtherColliders;
        };

        // Vector of collisions data.
        std::vector<ColliderData> mCollisions;

        // Vector of colliders.
        std::vector<scene::Collider*> mColliders;

    public:
        /**
         * Constructor
         */
        WorldPhysicsImpl() = default;

        /**
         * Destructor.
         */
        ~WorldPhysicsImpl()
        {
            mCollisions.clear();
            mColliders.clear();
        }

        /**
         * Copy and move constructors, and copy and move operators are deleted.
         * The worldphysics should not be movable or copyable.
         */
        WorldPhysicsImpl(WorldPhysicsImpl&& aOther) = delete;
        WorldPhysicsImpl(const WorldPhysicsImpl& aOther) = delete;
        WorldPhysicsImpl& operator=(const WorldPhysicsImpl& aOther) = delete;
        WorldPhysicsImpl& operator=(WorldPhysicsImpl&& aOther) = delete;

        /**
        * Removes all collider data that belongs to null scene nodes. This is because the node has
        * been deleted from the scene, but colliders still remains in the physics world.
        */
        void RemoveOldColliderData()
        {
            // TODO: refactor this function, for the sake of mankind.
            if (!mColliders.empty())
            {
                for (auto It = mColliders.begin(); It != mColliders.end();)
                {
                    if ((*It)->GetNodeContainer() == nullptr)
                    {
                        mColliders.erase(It);
                    }
                    else
                    {
                        ++It;
                    }
                }
            }
            if (!mCollisions.empty())
            {
                for (auto ItChecking = mCollisions.begin(); ItChecking != mCollisions.end();)
                {
                    for(auto ItOthers = (*ItChecking).mOtherColliders.begin();
                        ItOthers != (*ItChecking).mOtherColliders.end();)
                    {
                        if ((*ItOthers).first->GetNodeContainer() == nullptr)
                        {
                            (*ItChecking).mOtherColliders.erase(ItOthers++);
                        }
                        else
                        {
                            ++ItOthers;
                        }
                    }
                    if ((*ItChecking).mCheckingCollider->GetNodeContainer() == nullptr)
                    {
                        mCollisions.erase(ItChecking);
                    }
                    else
                    {
                        ++ItChecking;
                    }
                }
            }
        }

        void Update(double aDt)
        {
            RemoveOldColliderData();
            // First version. Check all colliders with all colliders.
            for (auto& Collision : mCollisions)
            {
                for (auto& Other: Collision.mOtherColliders)
                {
                    scene::Collider* CheckingCollider = Collision.mCheckingCollider;
                    scene::Collider* OtherCollider = Other.first;
                    if (OtherCollider->GetNodeContainer() == nullptr)
                        continue;
                    if (CheckingCollider->GetNodeContainer() == nullptr)
                        break;

                    auto WasColliding = Other.second;
                    if (CheckCollision(CheckingCollider, OtherCollider))
                    {
                        if (!WasColliding)
                        {
                            events::EnterCollisionEvent event;
                            event.SetNodes(CheckingCollider->GetNodeContainer(),
                                           OtherCollider->GetNodeContainer());
                            events::EventDispatcher::SendEvent(event);
                            Other.second = true;
                        }
                    }
                    else
                    {
                        if (WasColliding)
                        {
                            events::ExitCollisionEvent event;
                            event.SetNodes(CheckingCollider->GetNodeContainer(),
                                           OtherCollider->GetNodeContainer());
                            events::EventDispatcher::SendEvent(event);
                            Other.second = false;
                        }
                    }
                }
            }
        }

        /**
         * Performs a check collision between two colliders
         * @param aFirst First collider
         * @param aSecond Second Collider
         * @return True if there is a collision between them. False otherwise.
         */
        bool CheckCollision(scene::Collider *aFirst, scene::Collider *aSecond) const
        {
            bool IsCollision = false;

            // Two boxes
            if (aFirst->Type() == scene::ColliderBox::type &&
                aSecond->Type() == scene::ColliderBox::type)
            {
                scene::ColliderBox* FirstBox = static_cast<scene::ColliderBox*>(aFirst);
                scene::ColliderBox* SecondBox = static_cast<scene::ColliderBox*>(aSecond);
                IsCollision = CollisionBoxBox(FirstBox, SecondBox);
            }

            // Two circles
            if (aFirst->Type() == scene::ColliderCircle::type &&
                aSecond->Type() == scene::ColliderCircle::type)
            {
                scene::ColliderCircle* FirstCircle = static_cast<scene::ColliderCircle*>(aFirst);
                scene::ColliderCircle* SecondCircle = static_cast<scene::ColliderCircle*>(aSecond);
                IsCollision = CollisionCircleCircle(FirstCircle, SecondCircle);
            }

            // Circle and box.
            if (aFirst->Type() == scene::ColliderCircle::type &&
                aSecond->Type() == scene::ColliderBox::type)
            {
                scene::ColliderCircle* Circle = static_cast<scene::ColliderCircle*>(aFirst);
                scene::ColliderBox* Box = static_cast<scene::ColliderBox*>(aSecond);
                IsCollision = CollisionCircleBox(Box, Circle);
            }

            // Box and circle.
            if (aFirst->Type() == scene::ColliderBox::type &&
                aSecond->Type() == scene::ColliderCircle::type)
            {
                scene::ColliderBox* Box = static_cast<scene::ColliderBox*>(aFirst);
                scene::ColliderCircle* Circle = static_cast<scene::ColliderCircle*>(aSecond);
                IsCollision = CollisionCircleBox(Box, Circle);
            }

            return IsCollision;
        }

        /**
         * Performs a check collision between two circle colliders.
         * @param aFirst First circle collider.
         * @param aSecond Second circle collider.
         * @return True if there is collision between them. False otherwise.
         */
        bool CollisionCircleCircle(scene::ColliderCircle *aFirst, scene::ColliderCircle *aSecond) const
        {
            auto FirstX = aFirst->GetPosition().X;
            auto FirstY = aFirst->GetPosition().Y;
            auto SecondX = aSecond->GetPosition().X;
            auto SecondY = aSecond->GetPosition().Y;
            auto FirstRadius = aFirst->GetRadius().value;
            auto SecondRadius = aSecond->GetRadius().value;

            return std::pow(SecondX - FirstX, 2) + std::pow(SecondY - FirstY, 2) <=
                   std::pow(FirstRadius + SecondRadius, 2);
        }

        /**
         * Performs a check collision between two box colliders.
         * @param aFirst First box collider
         * @param aSecond Second Box collider.
         * @return True if there is collision between them. False otherwise.
         */
        bool CollisionBoxBox(scene::ColliderBox *aFirst, scene::ColliderBox *aSecond) const
        {
            auto FirstX = aFirst->GetPosition().X;
            auto FirstY = aFirst->GetPosition().Y;
            auto SecondX = aSecond->GetPosition().X;
            auto SecondY = aSecond->GetPosition().Y;
            auto FirstWidth = aFirst->GetWidth().value;
            auto FirstHeight = aFirst->GetHeight().value;
            auto SecondWidth = aSecond->GetWidth().value;
            auto SecondHeight = aSecond->GetHeight().value;

            return (std::abs(FirstX - SecondX) * 2 < FirstWidth + SecondWidth) &&
                   (std::abs(FirstY - SecondY) * 2 < FirstHeight + SecondHeight);
        }

        /**
         * Performs a check collision betwen a box collider and a circle collider.
         * @param aBox Box collider
         * @param aCircle Circle collider
         * @return True if there is a collision between them. False otherwise.
         */
        bool CollisionCircleBox(scene::ColliderBox *aBox, scene::ColliderCircle *aCircle) const
        {
            auto CirclePosition = aCircle->GetPosition();
            auto LeftRectangle = aBox->GetPosition().X - aBox->GetWidth().value / 2.0f;
            auto RightRectangle = aBox->GetPosition().X + aBox->GetWidth().value / 2.0f;
            auto TopRectangle = aBox->GetPosition().Y + aBox->GetHeight().value / 2.0f;
            auto BotRectangle = aBox->GetPosition().Y - aBox->GetHeight().value / 2.0f;

            // First, we find the closest point from the rectangle, to the circle's center.
            float ClosestX = utils::Clamp(CirclePosition.X, LeftRectangle, RightRectangle);
            float ClosestY = utils::Clamp(CirclePosition.Y,  BotRectangle, TopRectangle);

            // Then, we calculate the distance between the circle's center and the closest point.
            float Distance = std::sqrt(std::pow(CirclePosition.X - ClosestX, 2) +
                                       std::pow(CirclePosition.Y - ClosestY, 2));

            // If the distance is less than radius, then we have a collision.
            return Distance < aCircle->GetRadius().value;
        }

        void AddCollider(scene::Collider *aCollider)
        {
            // First, we create a new collision data object.
            // We go through all the colliders in world, and
            // we add them to the list of Other Colliders, so
            // we can check potential collisions with all of them.
            ColliderData collisionData;
            collisionData.mCheckingCollider = aCollider;
            std::map<scene::Collider*, bool> OtherColliders;
            for(auto OldCollider: mColliders)
                OtherColliders[OldCollider] = false;
            collisionData.mOtherColliders = OtherColliders;

            // Now, we add the new collider to the already existing
            // collision data objects. It's just an updating of all
            // collision data objects, so they can check collisions
            // with the new collider too.
            for(auto& CurrentCollision: mCollisions)
                CurrentCollision.mOtherColliders[aCollider] = false;

            // Finally we add the new collider and the new collision
            // to its respectively containers.
            mCollisions.push_back(collisionData);
            mColliders.push_back(aCollider);
        }
    };

    WorldPhysics::WorldPhysics()
        : mImpl(std::make_unique<WorldPhysicsImpl>())
    {
    }

    WorldPhysics::~WorldPhysics() = default;

    void  WorldPhysics::Update(double aDt)
    {
        mImpl->Update(aDt);
    }

    void WorldPhysics::AddCollider(scene::Collider *aCollider)
    {
        mImpl->AddCollider(aCollider);
    }
}