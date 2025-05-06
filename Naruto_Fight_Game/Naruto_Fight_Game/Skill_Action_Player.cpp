#include "framework.h"
#include "Player.h"
#include "Skill_Action_Player.h"
#include "Idle_Action_Player.h"
#include "SceneManager.h"
#include "Scene.h"

void Skill_Action_Player::Enter(Player* player)
{
    player->PlayAnimation(L"Skill", false);
}

void Skill_Action_Player::Update(Player* player, float deltaTime)
{
    elapsed += deltaTime;

    if (m_MoveDistance < m_TotalDistance && elapsed >= 5.0f)
    {
        float moveStep = m_MoveSpeed * deltaTime;
        m_MoveDistance += moveStep;

        Vector2 dir = player->IsFlipX() ? Vector2(-1, 0) : Vector2(1, 0);
        player->SetPosition(player->GetPosition() + dir * moveStep);

        if (!m_DamageApplied)
        {
            for (auto other : SceneManager::Get().GetCurrentScene()->GetObjects())
            {
                Player* enemy = dynamic_cast<Player*>(other);
                if (enemy && enemy != player)
                {
                    if (player->GetAABB().CheckIntersect(enemy->GetAABB()))
                    {
                        enemy->TakeDamage(20.0f);
                        m_DamageApplied = true;
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

void Skill_Action_Player::Exit(Player* player) {
    
}
