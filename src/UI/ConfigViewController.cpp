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

DEFINE_TYPE(MenuPillow, ConfigViewController);

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
            //layout->set_spacing(3.0f);

            // which is the active constellation?
            int active = 0;

            //wether the active constellation was found already
            bool found = false;
            for (auto con : *PillowManager::GetConstellations())
            {
                // make strings of all the names
                constellationNames.push_back(il2cpp_utils::createcsstr(con.get_name(), il2cpp_utils::StringType::Manual));
                // if it's the active one, set found to true
                if (con.get_name().find(config.lastActiveConstellation) != std::string::npos) found = true;
                
                // when the active one has not been found, increase the counter
                if (!found) active++; 
            }
            
            if (!found) active = 0;

            // should pillows show at all?
            BeatSaberUI::CreateToggle(layout->get_transform(), "Pillows Enabled", config.enabled, [](bool value) {
                    config.enabled = value;
                    if (config.enabled) PillowManager::OnModEnable();
                    else PillowManager::OnModDisable();
                    SaveConfig();
            });

            // switch between the constellations with a rollback
            constellationSwitcher = BeatSaberUI::CreateIncrementSetting(layout->get_transform(), "Constellation", 0, 1.0f, active, [&](float value) {
                    // get the current value into an int for indexing
                    int index = (int)value;
                    // max is the constellationNames.size - 1
                    int max = constellationNames.size() - 1;

                    // if under 0, loop back to the top
                    if (index < 0) index = max;
                    // if not under 0, mod so it keeps in bounds
                    index %= (max + 1);

                    // which name to use
                    Il2CppString* name = constellationNames[index];
                    
                    // set the text
                    constellationSwitcher->Text->SetText(name);
                    
                    // set current val again
                    constellationSwitcher->CurrentValue = index;

                    // get the std string of the constellation name
                    std::string constellation = to_utf8(csstrtostr(name));
                    
                    // get manager and set active
                    PillowManager* manager = Object::FindObjectOfType<PillowManager*>();
                    if (!manager) return;
                    manager->SetActiveConstellation(constellation);
                    SaveConfig();
                });

            // set text initially
            constellationSwitcher->Text->SetText(constellationNames[active]);
            
            // Shuffle button 
            QuestUI::BeatSaberUI::CreateUIButton(layout->get_transform(), "Shuffle", []{
                PillowManager::RandomizeTextures();
            });
        }
    }

    void ConfigViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling)
    {

    }
}