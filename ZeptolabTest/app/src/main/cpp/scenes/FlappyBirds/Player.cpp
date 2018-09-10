//
// Created by Josep on 03/09/2018.
//

#include "Player.h"

#include "../../engine/scene/components/RendererCircle.h"

float Player::JUMP_FORCE = 1600.f;

const utils::Color DEAD_COLOR = utils::Color(1.0f, 0.f, 0.f);

Player::Player()
    : mPlayerNode(nullptr)
    , mIsAwake(false)
    , mIsDead(false)

{
}

void Player::Jump()
{
    if (mPlayerNode)
    {
        scene::PhysicsBody* PhysicsComponent = mPlayerNode->GetComponent<scene::PhysicsBody>();
        if (PhysicsComponent)
        {
            PhysicsComponent->SetApplyGravity(true);
            PhysicsComponent->AddForce(utils::Vector3<>(0.f, JUMP_FORCE, 0.f));
        }
    }
}

void Player::Kill()
{
    if (mPlayerNode)
    {
        auto PhysicsComponent = mPlayerNode->GetComponent<scene::PhysicsBody>();
        auto RendererComponent = mPlayerNode->GetComponent<scene::RendererCircle>();
        if (PhysicsComponent)
        {
            PhysicsComponent->Stop();
        }

        if (RendererComponent)
        {
            RendererComponent->SetColor(DEAD_COLOR);
        }
    }

    mIsDead = true;
}

void Player::Awake()
{
    mIsAwake = true;
}

bool Player::IsAwake() const
{
    return mIsAwake;
}

bool Player::IsDead() const
{
    return mIsDead;
}

void Player::SetPlayerNode(scene::SceneNode *aPlayerNode)
{
    mPlayerNode = aPlayerNode;
}