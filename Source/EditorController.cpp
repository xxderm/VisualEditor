#include "EditorController.hpp"

namespace VisualEditor {

    EditorController::EditorController(SDL_Window* window) {
        mEntities = std::make_shared<Storage<std::shared_ptr<Graphics::Shape>>>();
        mEditorView = std::make_shared<EditorView>(window);
        mEditorView->OnAddShape([this](Graphics::ShapeType type) {
            mActions.push_back(std::make_shared<AddShapeCommand>(mEntities, type));
            mActions.back()->Execute();
        });
        mEditorView->OnChangeColor([this](float r, float g, float b) {
            for (uint32_t i = 0; i < mEntities->Size(); i++) {
                if ((*mEntities)[i]->IsSelected()) {
                    mActions.push_back(std::make_shared<ShapeChangeColorCommand>((*mEntities)[i], ImVec4(r, g, b, 1.)));
                    mActions.back()->Execute();
                }
            }
        });
        mEditorView->OnMakeGroup([this]() {
            std::vector<uint32_t> indicesToErase;
            auto gs = Graphics::ShapeFactory::CreateShape(Graphics::ShapeType::GROUP);
            for (uint32_t i = 0; i < mEntities->Size(); i++) {
                if ((*mEntities)[i]->IsSelected()) {
                    ((Graphics::GroupShape*)gs.get())->Add((*mEntities)[i]->Copy());
                    indicesToErase.push_back(i);
                }
            }
            for (auto ind : indicesToErase)
                mEntities->Remove(ind);
            mEntities->Push(gs);
        });
        mEditorView->OnDelete([this]() {
            std::vector<uint32_t> indicesToErase;
            for (uint32_t i = 0; i < mEntities->Size(); i++) {
                if ((*mEntities)[i]->IsSelected())
                    indicesToErase.push_back(i);
            }
            for (auto ind : indicesToErase)
                mEntities->Remove(ind);
        });
        mEditorView->OnUnGroup([this]() {
            std::vector<uint32_t> indicesToErase;
            for (uint32_t i = 0; i < mEntities->Size(); i++) {
                if ((*mEntities)[i]->IsSelected()) {
                    indicesToErase.push_back(i);
                    auto entities = ((Graphics::GroupShape*)(*mEntities)[i].get())->GetEntities();
                    for (uint32_t j = 0; j < entities.Size(); ++j) {
                        mEntities->Push(std::shared_ptr<Graphics::Shape>(entities[j]));
                    }
                }
            }
            for (auto ind : indicesToErase)
                mEntities->Remove(ind);
        });
        mTreeView = std::make_shared<TreeView>(&mEntityModel);
    }

    void EditorController::Render(SDL_Window* window) {
        SDL_SetCursor(SDL_CreateSystemCursor(mCursor));
        int ww, wh;
        SDL_GetWindowSize(window, &ww, &wh);
        mScrSize.x = ww;
        mScrSize.y = wh;
        mEditorView->SetEntities(mEntities);
        mEditorView->SetActions(mActions);
        mEditorView->Render(window);
        mEntityModel.SetEntities(&mEntities);
        mEntityModel.SetScrSize(ImVec2(ww, wh));

    }

    void EditorController::OnEvent(SDL_Event *event) {
        mCursor = SDL_SYSTEM_CURSOR_ARROW;
        auto scenePos = mEditorView->GetScenePos();
        auto sceneSize = mEditorView->GetSceneSize();
        auto pos = ImVec2(event->motion.x - scenePos.x, event->motion.y - scenePos.y);
        auto nx = (float)((float)pos.x / sceneSize.x) * 2.f - 1.f;
        auto ny = (float)((float)-pos.y / sceneSize.y) * 2.f + 1.f;
        for (uint32_t i = 0; i < mEntities->Size(); i++) {
            (*mEntities)[i]->OnEvent(event, ImVec2(nx, -ny));
            if ((*mEntities)[i]->IsInFlexBorder(ImVec2(nx, -ny)))
                mCursor = SDL_SYSTEM_CURSOR_SIZEWE;
        }

    }

    void EditorController::Save(std::string project) {
        nlohmann::json data;
        data["EntityCount"] = mEntities->Size();
        std::ofstream f(project);
        auto dump = data.dump(4);
        f.write(dump.data(), dump.size());
        f.close();
    }

}
