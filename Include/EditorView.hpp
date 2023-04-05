#pragma once
#include "pch.hpp"
#include "ShapeFactory.hpp"
#include "Command.hpp"
#include "GroupShape.hpp"
#include <vector>
#include <algorithm>

namespace VisualEditor {

    class EntitiesModel final : public Graphics::Observable {
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

    class TreeView final : public Graphics::IObserver {
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
                    // TODO: Update to SelectedShape
                    auto selected = current->IsSelected();
                    if (ImGui::TreeNodeEx(name.c_str(),
                            selected ? ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_DefaultOpen : 0)) {
                        RecurseGroup(currentEntitiesGroup);
                        ImGui::TreePop();
                    }
                }
                else {
                    auto name = current->GetName() + "##" + std::to_string(i);
                    auto selected = current->GetName() == "SelectedShape";
                    if (ImGui::Selectable(name.c_str(), selected)) {
                        current->Select(!selected);
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
                        sh[i]->Select(!sh[i]->IsSelected());
                    }
                }
            }
        }
    private:
        EntitiesModel* mModel;
    };

    class StickyShape final : virtual public Graphics::Shape, public Graphics::IObserver {
    public:
        StickyShape(EntitiesModel* model, Shape* stickyShape) : mModel(model), mShape(stickyShape) {
            mModel->AddObserver(this);
            mPosition = mShape->GetPosition();
        }
        void Render() override { mShape->Render(); }
        void Update() override {
            auto entities = mModel->GetEntities()->get();
            for (int i = 0; i < entities->Size(); ++i) {
                auto it = find (mStickyIndices.begin(), mStickyIndices.end(), i);
                if (it != mStickyIndices.end())
                    continue;
                auto entity = entities->At(i);
                auto stickyPos = mShape->GetPosition();
                auto entityPos = entity->GetPosition();
                auto stickySize = mShape->GetSize();
                auto dist = sqrt( ((stickyPos.x - entityPos.x) * (stickyPos.x - entityPos.x))
                                  + ((stickyPos.y - entityPos.y) * (stickyPos.y - entityPos.y)) );
                if (dist < stickySize.x * 1.24) {
                    if (entity->GetName() != "SelectedShape") {
                        mStickyIndices.push_back(i);
                    }

                }
            }
        }
        void Load(nlohmann::json* data) override { mShape->Load(data); }
        void Save(nlohmann::json* data) override { mShape->Save(data); }
        void Move(ImVec2 delta) override {
            mShape->Move(delta);
            Graphics::Shape::Move(delta);
            for (const auto& index : mStickyIndices) {
                mModel->GetEntities()->get()->At(index)->Move(delta);
            }
        }
        ImVec2 GetSize() override { return mShape->GetSize(); };
        bool IsMouseHover(ImVec2 mousePos) override { return mShape->IsMouseHover(mousePos); }
        bool IsInFlexBorder(ImVec2 mouse) override { return mShape->IsInFlexBorder(mouse); }
        void Amplify(ImVec2 mouse) override { return mShape->Amplify(mouse); }
        void Flex(double dist) override { return mShape->Flex(dist); }
        std::string GetName() const override { return "StickyShape"; }
        Graphics::ShapeType GetShapeType() const override { return mShape->GetShapeType(); }
        void SetColor(ImVec4 color) override { mShape->SetColor(color); }
        Shape* Copy() override { return mShape->Copy(); }
        Graphics::Quad GetBounds(ImVec2 pos) override { return mShape->GetBounds(pos); }
    private:
        Shape* mShape = nullptr;
        EntitiesModel* mModel;
        std::vector<int> mStickyIndices;
        ImVec2 lastMoveDeltas;
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
        void OnSetSticky(const std::function<void()>& fn);
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
        std::function<void()> mOnSetSticky;
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