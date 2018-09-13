//
// Created by Josep on 03/09/2018.
//

#include "Player.h"

#include "../../engine/scene/components/RendererCircle.h"

float Player::JUMP_FORCE = 1600.f;

const utils::Color DEAD_COLOR = utils::Color(1.0f, 0.f, 0.f);

Player::Player(const std::string aPlayerName)
    : SceneNode(aPlayerName)
    , mIsAwake(false)
    , mIsDead(false)
{
}

void Player::Jump()
{
    scene::PhysicsBody* PhysicsComponent = GetComponent<scene::PhysicsBody>();
    if (PhysicsComponent)
    {
        PhysicsComponent->SetApplyGravity(true);
        PhysicsComponent->AddForce(utils::Vector3<>(0.f, JUMP_FORCE, 0.f));
    }
}

void Player::Kill()
{
    auto PhysicsComponent = GetComponent<scene::PhysicsBody>();
    auto RendererComponent = GetComponent<scene::RendererCircle>();
    if (PhysicsComponent)
    {
        PhysicsComponent->Stop();
    }

    if (RendererComponent)
    {
        RendererComponent->SetColor(DEAD_COLOR);
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