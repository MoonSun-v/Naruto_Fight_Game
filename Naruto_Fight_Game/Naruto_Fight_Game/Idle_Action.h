#pragma onced
#include "ActionState.h"

class Idle_Action : public ActionState 
{
public:
    void Enter(Player* player) override {}
    void Update(Player* player, float deltaTime) override {}
    void Exit(Player* player) override {}
};
