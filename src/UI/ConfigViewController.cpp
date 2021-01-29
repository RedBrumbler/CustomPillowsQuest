#include "UI/ConfigViewController.hpp"
#include "config.hpp"

extern config_t config;

#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/SpriteMeshType.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/UI/Toggle_ToggleEvent.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"
#include "UnityEngine/Events/UnityAction.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"
#include "HMUI/ScrollView.hpp"
#include "HMUI/ModalView.hpp"
#include "HMUI/Touchable.hpp"
#include "HMUI/InputFieldView.hpp"
#include "UnityEngine/Coroutine.hpp"
#include "UnityEngine/WaitUntil.hpp"
#include "System/Func_1.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Data/CustomDataType.hpp"
#include "questui/shared/CustomTypes/Components/ExternalComponents.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

#include <cstdlib>
#include <vector>
#include <string>

#include "TexturePool.hpp"
#include "CustomTypes/PillowManager.hpp"

using namespace QuestUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace UnityEngine::Events;
using namespace HMUI;

DEFINE_CLASS(MenuPillow::ConfigViewController);

static std::vector<Il2CppString*> constellationNames = {};



namespace MenuPillow
{
    void ConfigViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
        {
            get_gameObject()->AddComponent<Touchable*>();
            VerticalLayoutGroup* layout = BeatSaberUI::CreateVerticalLayoutGroup(get_transform());
            layout->get_gameObject()->GetComponent<Backgroundable*>()->ApplyBackgroundWithAlpha(il2cpp_utils::createcsstr("round-rect-panel"), 0.5f);
            layout->set_childForceExpandHeight(true);
            layout->set_childControlHeight(false);
            layout->set_childAlignment(UnityEngine::TextAnchor::MiddleCenter);
            layout->get_rectTransform()->set_sizeDelta(UnityEngine::Vector2(0.0f, -20.0f));
            layout->set_spacing(3.0f);
            int active = 0;
            bool found = false;
            for (auto con : *PillowManager::GetConstellations())
            {
                constellationNames.push_back(il2cpp_utils::createcsstr(con.get_name(), il2cpp_utils::StringType::Manual));
                if (con.get_name().find(config.lastActiveConstellation) != std::string::npos) found = true;
                if (!found) active++; 
            }

            BeatSaberUI::CreateToggle(layout->get_transform(), "Pillows Enabled", config.enabled, il2cpp_utils::MakeDelegate<UnityAction_1<bool>*>(classof(UnityAction_1<bool>*), this,
                +[](ConfigViewController* view, bool value) {
                    config.enabled = value;
                    if (config.enabled) PillowManager::OnModEnable();
                    else PillowManager::OnModDisable();
                    SaveConfig();
            }));
            int maxSize = constellationNames.size() - 1;
            IncrementSetting* constellationSwitcher = BeatSaberUI::CreateIncrementSetting(layout->get_transform(), "Constellation", 0, 1.0f, active, 0, maxSize, nullptr);
            constellationSwitcher->OnValueChange = il2cpp_utils::MakeDelegate<UnityAction_1<float>*>(classof(UnityAction_1<float>*), constellationSwitcher, 
                +[](IncrementSetting* switcher, float value) {
                    int index = (int)value;
                    Il2CppString* name = constellationNames[index];
                    switcher->Text->SetText(name);
                    std::string constellation = to_utf8(csstrtostr(name));
                    PillowManager* manager = Object::FindObjectOfType<PillowManager*>();
                    if (!manager) return;
                    manager->SetActiveConstellation(constellation);
                    SaveConfig();
                });
            constellationSwitcher->Text->SetText(constellationNames[active]);
            
            Button* saberButton = QuestUI::BeatSaberUI::CreateUIButton(layout->get_transform(), "Shuffle", il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(classof(UnityEngine::Events::UnityAction*), (Il2CppObject*)nullptr, +[]{
                PillowManager::RandomizeTextures();
            }));            


        }
    }

    void ConfigViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling)
    {

    }
}