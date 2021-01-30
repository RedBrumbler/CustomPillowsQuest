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
    if (!fileexists(imagePath)) return;
    Sprite* sprite = FileUtils::FileToSprite(imagePath, 474, 1012);
    //Sprite* sprite = Sprite::Create(tex, UnityEngine::Rect(0.0f, 0.0f, (float)474, (float)1012), UnityEngine::Vector2(0.5f,0.5f), 1024.0f, 1u, SpriteMeshType::FullRect, UnityEngine::Vector4(0.0f, 0.0f, 0.0f, 0.0f), false);
    if (!sprite) return;

    //VerticalLayoutGroup* doubleLayout 
    Button* button = BeatSaberUI::CreateUIButton(layout, "", "SettingsButton", nullptr);
    /*il2cpp_utils::MakeDelegate<UnityEngine::Events::UnityAction*>(classof(UnityEngine::Events::UnityAction*), (Il2CppObject*)nullptr, +[](void* irrelevant, Button* button){
                
            }));*/
    ButtonSpriteSwap* swap = button->GetComponent<HMUI::ButtonSpriteSwap*>();

    swap->normalStateSprite = sprite;
    swap->highlightStateSprite = sprite;
    swap->pressedStateSprite = sprite;
    swap->disabledStateSprite = sprite;

    button->set_interactable(false);
    button->get_transform()->set_localScale(UnityEngine::Vector3::get_one() * 0.22f);
    return;
}

void AddToggleToLayout(Transform* layout, std::string name)
{
    Il2CppString* csName = il2cpp_utils::createcsstr(name, il2cpp_utils::StringType::Manual);

    BeatSaberUI::CreateToggle(layout, FileUtils::RemoveExtension(name), MenuPillow::TexturePool::GetIsActive(name), il2cpp_utils::MakeDelegate<UnityAction_1<bool>*>(classof(UnityAction_1<bool>*), csName, 
        +[](Il2CppString* texName, bool value) {
            if (!texName) return;
            std::string name = to_utf8(csstrtostr(texName));
            if (value) MenuPillow::TexturePool::AddTexture(name);
            else MenuPillow::TexturePool::RemoveTexture(name);  
            MenuPillow::PillowManager::RandomizeTextures();
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
        //this->texVector = texVector;
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
        GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
        VerticalLayoutGroup* layout = BeatSaberUI::CreateVerticalLayoutGroup(container->get_transform());
        ExternalComponents* externalComponents = container->GetComponent<ExternalComponents*>();
        RectTransform* scrollTransform = externalComponents->Get<RectTransform*>();
        scrollTransform->set_sizeDelta(UnityEngine::Vector2(0.0f, 0.0f));

        
        layout->set_childForceExpandWidth(false);
        layout->set_childControlWidth(false);
        //scrollTransform->set_childAlignment(UnityEngine::TextAnchor::MiddleLeft);
        //scrollTransform->get_rectTransform()->set_sizeDelta(UnityEngine::Vector2(0.0f, -20.0f));
        //scrollTransform->set_spacing(3.0f);
        
        //const std::vector<std::string>& texVector = TexturePool::GetTextureVector();
        QuestUI::CustomDataType* wrapper = CRASH_UNLESS(il2cpp_utils::New<QuestUI::CustomDataType*, il2cpp_utils::CreationType::Manual>(classof(QuestUI::CustomDataType*)));
        TextureInfo* info = new TextureInfo(TexturePool::GetTextureVector(), container->get_transform());
        wrapper->data = info;
        
        auto coroutine = UnityEngine::WaitUntil::New_ctor(il2cpp_utils::MakeDelegate<System::Func_1<bool>*>(classof(System::Func_1<bool>*), wrapper,
            +[](QuestUI::CustomDataType* wrapper){
                TextureInfo* info = (TextureInfo*)wrapper->data;
                if (info->index >= info->size)
                {
                    free(info);
                    free(wrapper);
                    return true;
                }

                switch(info->counter)
                {
                    case 0:
                        info->layout = BeatSaberUI::CreateHorizontalLayoutGroup(info->container);
                        info->layout->set_spacing(3.0f);
                        info->layoutTransform = info->layout->get_transform();
                        info->layout->GetComponent<Backgroundable*>()->ApplyBackgroundWithAlpha(il2cpp_utils::createcsstr("round-rect-panel"), 0.5f);
                        break;
                    case 1:
                        AddImageToLayout(info->layoutTransform, info->texVector[info->index]);
                        break;
                    case 2:
                        AddToggleToLayout(info->layoutTransform, info->texVector[info->index]);
                        break;
                    default:
                        info->counter = 0;
                        info->index++;
                        return false;
                }
                info->counter++;
                return false;
            }));

        UnityEngine::MonoBehaviour::StartCoroutine(reinterpret_cast<System::Collections::IEnumerator*>(coroutine));
        /*
        for (auto& name : texVector)
        {
            getLogger().info("Adding texture %s to the UI", name.c_str());
            QuestUI::CustomDataType* wrapper = CRASH_UNLESS(il2cpp_utils::New<QuestUI::CustomDataType*, il2cpp_utils::CreationType::Manual>(classof(QuestUI::CustomDataType*)));
            TextureInfo* info = new TextureInfo(name, container->get_transform());
            wrapper->data = info;
            
            
            auto coroutine = UnityEngine::WaitUntil::New_ctor(il2cpp_utils::MakeDelegate<System::Func_1<bool>*>(classof(System::Func_1<bool>*), wrapper,
            +[](QuestUI::CustomDataType* wrapper){
                TextureInfo* info = (TextureInfo*)wrapper->data;
                switch(info->counter)
                {
                    case 0:
                        info->layout = BeatSaberUI::CreateHorizontalLayoutGroup(info->container);
                        info->layout->set_spacing(3.0f);
                        info->layoutTransform = info->layout->get_transform();
                        info->layout->GetComponent<Backgroundable*>()->ApplyBackgroundWithAlpha(il2cpp_utils::createcsstr("round-rect-panel"), 0.5f);
                        break;
                    case 1:
                        AddImageToLayout(info->layoutTransform, info->name);
                        break;
                    case 2:
                        AddToggleToLayout(info->layoutTransform, info->name);
                        break;
                    default:
                        free(info);
                        return true;
                }
                info->counter++;
                return false;
            }));

            UnityEngine::MonoBehaviour::StartCoroutine(reinterpret_cast<System::Collections::IEnumerator*>(coroutine));
            
        }
        */
    }
}

void MenuPillow::TextureSelectorViewController::DidDeactivate(bool removedFromHierarchy, bool screenSystemDisabling)
{

}