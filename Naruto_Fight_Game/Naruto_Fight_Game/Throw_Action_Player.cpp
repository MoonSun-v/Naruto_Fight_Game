#include "framework.h"
#include "Idle_Player.h"
#include "Throw_Action_Player.h"
#include "Player.h"
#include "Weapon.h"

#include "Scene.h"
#include "SceneManager.h"
#include "../Vector2_StaticLib/Vector2.h"

void Throw_Action_Player::Enter(Player* player)
{
    Scene* currentScene = SceneManager::Get().GetCurrentScene();
    Weapon* weapon = (Weapon*)currentScene->CreateObject<Weapon>();
    weapon->SetOwner(player);
    Vector2 dir = player->flipX ? Vector2(-1, 0) : Vector2(1, 0);
    weapon->Init(L"../Resources/Kunai1.png", L"../Resources/Weapon/Kunai1.txt", player->GetPosition(), dir, player->flipX);

    player->PlayAnimation(L"Throw_Action", false);
}

void Throw_Action_Player::Update(Player* player, float deltaTime)
{
    if (player->GetAnimator().IsAnimationFinished()) player->ChangeMoveState(new Idle_Player());
}

void Throw_Action_Player::Exit(Player* player) {
    
}