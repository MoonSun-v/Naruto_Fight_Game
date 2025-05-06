#include "framework.h"
#include "Player.h"
#include "Weapon.h"
#include "Scene.h"

#include "Idle_Player.h"
#include "Run_Player.h"
#include "Attack_Action_Player.h"
#include "AttackCombo_Action_Player.h"
#include "Throw_Action_Player.h"
#include "Hurt_Action_Player.h"

#include "Idle_Action_Player.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SceneManager.h"

#include <fstream>
#include <sstream>

Player::Player(const std::wstring& imagePath, const std::wstring& animPath)
    : Character(imagePath, animPath)
{
    // transparentColor = Gdiplus::Color(0, 128, 0); // 이미지 배경 투명 처리
    ChangeMoveState(new Idle_Player());
    ChangeActionState(new Idle_Action_Player());
}

Player::~Player() = default;

void Player::Update()
{
    __super::Update();

    m_AttackStartedThisFrame = false; // 매 프레임 초기화

    float currentTime = TimeManager::Get().GetTotalTime();
    float deltaTime = TimeManager::Get().GetDeltaTime();

    // [ Attack_Action_Player ]
    PlayAttack();

    // [ Move_Action_Player ]
    PlayMove(currentTime);

    // [ FSM ] 
    if (moveState) moveState->Update(this, deltaTime);
    if (actionState) actionState->Update(this, deltaTime);
    
    // [ 화면 경계 제한 주기 ]

    // [MP 회복]
    UpdateMP(); // ← MP 회복 체크
}

void Player::Render()
{
    __super::Render();
    /*
    RenderManager::Get().DrawText_w(
        L"Player Pos: " + std::to_wstring(position.x) + L", " + std::to_wstring(position.y),
        150, 10, 20, Gdiplus::Color::Blue);

    RenderManager::Get().DrawText_w(
        L"Collider Center: " + std::to_wstring(collider.m_Center.x) + L", " + std::to_wstring(collider.m_Center.y),
        150, 40, 20, Gdiplus::Color::Red);
    */
    // RenderManager::Get().DrawText_w(
    //    L"moveSpeed: " + std::to_wstring(moveSpeed), 150, 80, 20, Gdiplus::Color::Green);

   
}

void Player::PlayAttack()
{
    // [ Attack ] 
    if (InputManager::Get().IsKeyPressed(keySet.keyAttack)) {
        ChangeActionState(new Attack_Action_Player());
        return;
    }

    // [ AttackCombo ] : Attack에서 관리 

    // [ Throw ]
    if (InputManager::Get().IsKeyPressed(keySet.keyThrow)) {
        ChangeActionState(new Throw_Action_Player());
        return;
    }
}

void Player::PlayMove(float currentTime)
{
    // [ Walk ] : Idle에서 관리 
    
    // [ Run ] : 방향키 더블탭 감지 
    if (InputManager::Get().IsKeyPressed(keySet.keyLeft)) {
        if (lastKeyPressed == keySet.keyLeft && (currentTime - lastKeyTime) < doubleTapThreshold) {
            ChangeMoveState(new Run_Player());
            return;
        }
        lastKeyPressed = keySet.keyLeft;
        lastKeyTime = currentTime;
    }
    if (InputManager::Get().IsKeyPressed(keySet.keyRight)) {
        if (lastKeyPressed == keySet.keyRight && (currentTime - lastKeyTime) < doubleTapThreshold) {
            ChangeMoveState(new Run_Player());
            return;
        }
        lastKeyPressed = keySet.keyRight;
        lastKeyTime = currentTime;
    }
}

void Player::ChangeMoveState(PlayerState* newState) 
{
    if (moveState) moveState->Exit(this);
    delete moveState;
    moveState = newState;
    if (moveState) moveState->Enter(this);
}

void Player::ChangeActionState(PlayerActionState* newState) 
{
    if (actionState) actionState->Exit(this);
    delete actionState;
    actionState = newState;
    if (actionState) actionState->Enter(this);
}


void Player::PlayAnimation(const std::wstring& name, bool force)
{
    animator.Play(name, force);
}

void Player::ResetRunInput()
{
    lastKeyPressed = 0;
    lastKeyTime = 0.0f;
}

void Player::SetKeySet(const KeySet& keys)
{
    keySet = keys;
}

void Player::TakeDamage(float damage)
{
    hp -= damage;
    if (hp < 0) hp = 0;

    // 예: 체력 감소, 피격 애니메이션, 디버그 출력
    OutputDebugString(L"Player Hit!");
}

float Player::SetHP(float value) 
{ 
    if (value < 0) return 0.0f;
    if (value > maxHp) return maxHp;
    return value;
}
float Player::SetMP(float value)
{
    if (value < 0) return 0.0f;
    if (value > maxHp) return maxHp;
    return value;
}

bool Player::IsAttacking() const
{
    // 여기서 예외처리 발생! 수정 필요 
    return dynamic_cast<Attack_Action_Player*>(actionState) != nullptr ||
        dynamic_cast<AttackCombo_Action_Player*>(actionState) != nullptr;
}

bool Player::IsHurt() const
{
    return dynamic_cast<Hurt_Action_Player*>(actionState) != nullptr;
}

// ------- MP 관련 ----------

void Player::UpdateMP()
{
   MPRecoveryTimer += TimeManager::Get().GetDeltaTime();

   if (MPRecoveryTimer >= 5.0f)
   {
       mp = std::min(mp + 5.0f, maxMp); 
       MPRecoveryTimer = 0.0f;
   }
}

void Player::OnHitEnemy(bool isCombo)
{
    float recoverAmount = isCombo ? 10.0f : 5.0f;
    mp = std::min(mp + recoverAmount, maxMp);
}

bool Player::CanThrowWeapon() const
{
    return mp >= 5.0f;
}

bool Player::CanUseSkill() const
{
    return mp >= 100.0f;
}

void Player::ConsumeMPForWeapon()
{
    mp = std::max(0.0f, mp - 5.0f);
}

void Player::ConsumeMPForSkill()
{
    mp = std::max(0.0f, mp - 100.0f);
}