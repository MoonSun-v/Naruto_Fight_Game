#include "framework.h"
#include "Player.h"
#include "Skill_Action_Player.h"
#include "Idle_Action_Player.h"
#include "SkillHurt_Action_Player.h"
#include "SceneManager.h"
#include "Scene.h"

void Skill_Action_Player::Enter(Player* player)
{ 
    if (player->CanUseSkill())
    {
        player->PlayAnimation(L"Skill", false);
        player->ConsumeMP(80.0f);
        SetInputLockForAllPlayers(true); // 입력 잠금
    }
    else player->ChangeActionState(new Idle_Action_Player());
}

void Skill_Action_Player::Update(Player* player, float deltaTime)
{
    elapsed += deltaTime;

    if (elapsed >= 5.0f && movedDistance < totalDistance)
    {
        float moveStep = moveSpeed * deltaTime;
        movedDistance += moveStep;

        Vector2 dir = player->IsFlipX() ? Vector2(-1, 0) : Vector2(1, 0);
        player->SetPosition(player->GetPosition() + dir * moveStep);

        if (!damageApplied)
        {
            for (auto other : SceneManager::Get().GetCurrentScene()->GetObjects())
            {
                Player* enemy = dynamic_cast<Player*>(other);
                if (enemy && enemy != player)
                {
                    if (player->GetAABB().CheckIntersect(enemy->GetAABB()))
                    {
                        enemy->ChangeActionState(new SkillHurt_Action_Player());
                        damageApplied = true;
                        break;
                    }
                }
            }
        }
    }

    if (player->GetAnimator().IsAnimationFinished())
    {
        player->ChangeActionState(new Idle_Action_Player());
    }
}

void Skill_Action_Player::Exit(Player* player) 
{
    SetInputLockForAllPlayers(false); 
}


// [ 입력 잠금/해제 ]
void Skill_Action_Player::SetInputLockForAllPlayers(bool lock)
{
    for (Object* obj : SceneManager::Get().GetCurrentScene()->GetObjects())
    {
        Player* p = dynamic_cast<Player*>(obj);
        if (p)
        {
            p->isInputLocked = lock;
        }
    }
}
