#pragma once
#include "pch.hpp"
#include "ShapeFactory.hpp"
#include "Command.hpp"

namespace VisualEditor {

    class IObserver {
    public:
        virtual void Update() = 0;
    };

    class Observable {
    public:
        void AddObserver(IObserver* observer) {
            mObservers.push_back(observer);
        }
        void NotifyUpdate() {
            for (auto& obs : mObservers)
                obs->Update();
        }
    private:
        std::vector<IObserver*> mObservers;
    };

    class EntitiesModel final : public Observable {
    public:
        void SetEntities(std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>>* entities) {
            mEntities = entities;
            this->NotifyUpdate();
        }
        void SetScrSize(ImVec2 scr) {
            this->mScrSize = scr;
        }
        std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>>* GetEntities() { return mEntities; }
        ImVec2 GetScrSize() { return mScrSize; }
    private:
        std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>>* mEntities{};
        ImVec2 mScrSize{};
    };

    class TreeView final : public IObserver {
    public:
        TreeView(EntitiesModel* model) {
            mModel = model;
            mModel->AddObserver(this);
        }
        void Update() override {
            std::srand(time(0));
            auto entities = mModel->GetEntities();
            auto scrSize = mModel->GetScrSize();
            ImGui::SetNextWindowPos(ImVec2(5, 20));
            ImGui::SetNextWindowSize(ImVec2(scrSize.x * 0.2, scrSize.y * 0.25));
            ImGui::Begin("Objects", 0,
                         ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);

            for (uint32_t i = 0; i < entities->get()->Size(); i++) {
                auto current = entities->get()->At(i).get();
                if (current->GetName() == "GroupShape") {
                    auto name = "GroupShape##" + std::to_string(i);
                    auto currentEntitiesGroup = ((Graphics::GroupShape*)(*entities->get())[i].get())->GetEntities();
                    auto selected = current->IsSelected();
                    if (ImGui::TreeNodeEx(name.c_str(),
                            selected ? ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen : 0)) {
                        RecurseGroup(currentEntitiesGroup);
                        ImGui::TreePop();
                    }
                }
                else {
                    auto name = current->GetName() + "##" + std::to_string(i);
                    auto selected = current->IsSelected();
                    if (ImGui::Selectable(name.c_str(), selected)) {

                    }
                }
            }

            ImGui::End();
        }
    private:
        void RecurseGroup(Storage<Graphics::Shape*> sh) {
            std::srand(time(0));
            for (uint32_t i = 0; i < sh.Size(); ++i) {
                if (sh[i]->GetName() == "GroupShape") {
                    auto name = "GroupShape##" + std::to_string(i);
                    if (ImGui::TreeNode(name.c_str())) {
                        auto entt = ((Graphics::GroupShape *) (sh)[i])->GetEntities();
                        RecurseGroup(entt);
                        ImGui::TreePop();
                    }
                }
                else {
                    auto name = sh[i]->GetName() + "##" + std::to_string(i);
                    if (ImGui::Selectable(name.c_str())) {

                    }
                }
            }
        }
    private:
        EntitiesModel* mModel;
    };

    class EditorView;
    using EditorViewPtr = std::shared_ptr<EditorView>;

    class EditorView final {
    public:
        EditorView(SDL_Window* window);
        EditorView(const EditorView& other) = delete;
        void Render(SDL_Window* window);
        void OnAddShape(const std::function<void(Graphics::ShapeType)>& fn);
        void OnChangeColor(const std::function<void(float r, float g, float b)>& fn);
        void OnMakeGroup(const std::function<void()>& fn);
        void OnUnGroup(const std::function<void()>& fn);
        void OnDelete(const std::function<void()>& fn);
        void OnUndo(const std::function<void()>& fn);
        void OnRedo(const std::function<void()>& fn);
        void SetEntities(const std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>>& entities);
        void SetActions(const std::stack<std::shared_ptr<ICommand>>& actions);
        ImVec2 GetScenePos() const { return mScenePos; }
        ImVec2 GetSceneSize() const { return mSceneSize; }
    private:
        void RenderSceneEntities(SDL_Window* window);
        void RenderEntityList(SDL_Window* window);
        void RenderEntitySettings(SDL_Window* window);
        void RenderActionList(SDL_Window* window);
        void RenderScene(SDL_Window* window);
    private:
        int mScrWidth{};
        int mScrHeight{};
        std::shared_ptr<FrameBuffer> mFrame;
        float mColor[3];
        std::function<void(Graphics::ShapeType)> mOnAddCallBack;
        std::function<void(float r, float g, float b)> mOnChangeColorCallBack;
        std::function<void()> mOnMakeGroup;
        std::function<void()> mOnUnGroup;
        std::function<void()> mOnDelete;
        std::function<void()> mOnUndo;
        std::function<void()> mOnRedo;
        GLuint mTriangleIcon{};
        GLuint mCircleIcon{};
        GLuint mQuadIcon{};
        GLuint mLineIcon{};
        std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>> mEntities;
        std::stack<std::shared_ptr<ICommand>> mActions;
        ImVec2 mScenePos{};
        ImVec2 mSceneSize{};
        bool mColorEdit = false;
    };

}