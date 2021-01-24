#include "PillowManager.hpp"

DEFINE_CLASS(MenuPillow::PillowManager);

namespace MenuPillow
{
    void PillowManager::OnMenuSceneActive()
    {

    }

    void PillowManager::OnMenuSceneInActive()
    {

    }

    void PillowManager::Awake()
    {

    }

    void PillowManager::SpawnPillow(pillowparams param)
    {
        Pile* pile = PileProvider::GetPile(param.type);
    }

    void PillowManager::RemoveLastPillow()
    {
        
    }
}