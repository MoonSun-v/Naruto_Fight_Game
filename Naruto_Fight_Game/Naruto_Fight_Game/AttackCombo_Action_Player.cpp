#include "framework.h"
#include "Player.h"
#include "AttackCombo_Action_Player.h"
#include "Hurt_Action_Player.h"
#include "Idle_Action_Player.h"
#include "ComboHurt_Action_Player.h" 

#include "SceneManager.h"
#include "Scene.h"

void AttackCombo_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"ComboAttack", false);
}

void AttackCombo_Action_Player::Update(Player* player, float deltaTime)
{
    // 콤보 공격 중 적에게 충돌 판정
    for (Object* obj : SceneManager::Get().GetCurrentScene()->GetObjects())
    {
        Player* enemy = dynamic_cast<Player*>(obj);
        if (enemy && enemy != player)
        {
            if (player->GetAABB().CheckIntersect(enemy->GetAABB()))
            {
                if (!enemy->IsHurt())
                {
                    enemy->ChangeActionState(new ComboHurt_Action_Player());
                }
            }
        }
    }

    if (player->GetAnimator().IsAnimationFinished())
    {
        player->ChangeActionState(new Idle_Action_Player());
    }
}

void AttackCombo_Action_Player::Exit(Player* player) {
    // 아무 작업 없음
}
