#include "UI/TextureSelectorViewController.hpp"
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
#include "HMUI/ButtonSpriteSwap.hpp"
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
#include "FileUtils.hpp"
#include "CustomTypes/PillowManager.hpp"

#include "static-defines.hpp"

using namespace QuestUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace UnityEngine::Events;
using namespace HMUI;

DEFINE_CLASS(MenuPillow::TextureSelectorViewController);

extern Logger& getLogger();

void AddImageToLayout(Transform* layout, std::string name)
{
    std::string imagePath = IMAGEPATH + name;
    
    // if no file, don't try to add an image
    if (!fileexists(imagePath)) return;
    Sprite* sprite = FileUtils::FileToSprite(imagePath);
    Button* button = BeatSaberUI::CreateUIButton(layout, "", "SettingsButton", nullptr); // no delegate needed, it's not interactable
    button->set_interactable(false);

    // set the button sprites to the pillow image
    ButtonSpriteSwap* swap = button->GetComponent<HMUI::ButtonSpriteSwap*>();
    swap->normalStateSprite = sprite;
    swap->highlightStateSprite = sprite;
    swap->pressedStateSprite = sprite;
    swap->disabledStateSprite = sprite;

    // make button smol
    button->get_transform()->set_localScale(UnityEngine::Vector3::get_one() * 0.22f);
}

void AddToggleToLayout(Transform* layout, std::string name)
{
    Il2CppString* csName = il2cpp_utils::createcsstr(name, il2cpp_utils::StringType::Manual);
    BeatSaberUI::CreateToggle(layout, FileUtils::RemoveExtension(name), MenuPillow::TexturePool::GetIsActive(name), il2cpp_utils::MakeDelegate<UnityAction_1<bool>*>(classof(UnityAction_1<bool>*), csName, 
        +[](Il2CppString* texName, bool value) {
            if (!texName) return;
            std::string name = to_utf8(csstrtostr(texName));
            // if the texture gets set to enabled, that means we need to add the tex to the list
            if (value) MenuPillow::TexturePool::AddTexture(name);
            // else remove it
            else MenuPillow::TexturePool::RemoveTexture(name);  
            // randomize textures after changing the pool
            MenuPillow::PillowManager::RandomizeTextures();
            //save config so the active textures are saved
            SaveConfig();
        }));
}

struct TextureInfo{
    const std::vector<std::string>& texVector;
    int counter;
    int index;
    int size;
    HorizontalLayoutGroup* layout;
    Transform* layoutTransform;
    Transform* container;

    TextureInfo(const std::vector<std::string>& texVector, Transform* container) : texVector(texVector)
    {
        counter = 0;
        index = 0;
        size = this->texVector.size();
        layout = nullptr;
        layoutTransform = nullptr;
        this->container = container;
    }
};

void MenuPillow::TextureSelectorViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    if (firstActivation)
    {
        get_gameObject()->AddComponent<Touchable*>();

        // needs to be scrollable because it is a list
        GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
        
        // set sizedelta to make the textures not cut off on the sides
        ExternalComponents* components = container->GetComponent<ExternalComponents*>();
        RectTransform* rect = components->Get<RectTransform*>();
        rect->set_sizeDelta({0.0f, 0.0f});
        
        // create wrapper to pass into the coroutine
        QuestUI::CustomDataType* wrapper = CRASH_UNLESS(il2cpp_utils::New<QuestUI::CustomDataType*, il2cpp_utils::CreationType::Manual>(classof(QuestUI::CustomDataType*)));
        
        // add some data to the struct that we use to get info into the coroutine
        TextureInfo* info = new TextureInfo(TexturePool::GetTextureVector(), container->get_transform());
        wrapper->data = info;
        
        auto coroutine = UnityEngine::WaitUntil::New_ctor(il2cpp_utils::MakeDelegate<System::Func_1<bool>*>(classof(System::Func_1<bool>*), wrapper,
            +[](QuestUI::CustomDataType* wrapper){
                TextureInfo* info = (TextureInfo*)wrapper->data;
                if (info->index >= info->size)
                {
                    // we are now done, we can free the structs and custom datatype
                    free(info);
                    free(wrapper);
                    return true;
                }

                switch(info->counter)
                {
                    case 0:
                        // create the horizontal layout, set it's spacing and add a background
                        info->layout = BeatSaberUI::CreateHorizontalLayoutGroup(info->container);
                        info->layout->set_spacing(3.0f);
                        info->layoutTransform = info->layout->get_transform();
                        info->layout->GetComponent<Backgroundable*>()->ApplyBackgroundWithAlpha(il2cpp_utils::createcsstr("round-rect-panel"), 0.5f);
                        break;
                    case 1:
                        // add the image to the UI
                        AddImageToLayout(info->layoutTransform, info->texVector[info->index]);
                        break;
                    case 2:
                        // add the toggle to the UI to use an image
                        AddToggleToLayout(info->layoutTransform, info->texVector[info->index]);
                        break;
                    default:
                        // reset counter, up the index by 1
                        info->counter = 0;
                        info->index++;
                        return false;
                }
                info->counter++;
                return false;
            }));

        UnityEngine::MonoBehaviour::StartCoroutine(reinterpret_cast<System::Collections::IEnumerator*>(coroutine));
    }
}

void MenuPillow::TextureSelectorViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling)
{

}