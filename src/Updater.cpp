#include "Updater.hpp"
#include "PileProvider.hpp"

DEFINE_CLASS(MenuPillow::Updater);

void MenuPillow::Updater::Update()
{
    PileProvider::ManualUpdate();
}