#include "EditorController.hpp"

namespace VisualEditor {

    EditorController::EditorController(SDL_Window* window) {
        mEntities = std::make_shared<Storage<std::shared_ptr<Graphics::Shape>>>(100);
        mEditorView = std::make_shared<EditorView>(window);
        mEditorView->OnAddShape([this](Graphics::ShapeType type) {
            mActions.push_back(std::make_shared<AddShapeCommand>(mEntities, type));
            mActions.back()->Execute();
        });
        mEditorView->OnChangeColor([this](float r, float g, float b) {
            for (auto beg = mEntities->Begin(); beg != mEntities->End(); ++beg) {
                if ((*beg)->IsSelected()) {
                    mActions.push_back(std::make_shared<ShapeChangeColorCommand>((*beg), ImVec4(r, g, b, 1.)));
                    mActions.back()->Execute();
                }
            }
        });
    }

    void EditorController::Render(SDL_Window* window) {
        int ww, wh;
        SDL_GetWindowSize(window, &ww, &wh);
        mScrSize.x = ww;
        mScrSize.y = wh;
        mEditorView->SetEntities(mEntities);
        mEditorView->SetActions(mActions);
        mEditorView->Render(window);
    }

    void EditorController::OnEvent(SDL_Event *event) {
        auto scenePos = mEditorView->GetScenePos();
        auto sceneSize = mEditorView->GetSceneSize();
        auto pos = ImVec2(event->motion.x - scenePos.x, event->motion.y - scenePos.y);
        auto nx = (float)((float)pos.x / sceneSize.x) * 2.f - 1.f;
        auto ny = (float)((float)-pos.y / sceneSize.y) * 2.f + 1.f;
        for (auto beg = mEntities->Begin(); beg != mEntities->End(); ++beg) {
            (*beg)->OnEvent(event, ImVec2(nx, -ny));
        }
    }

    void EditorController::Save(std::string project) {
        nlohmann::json data;
        data["EntityCount"] = mEntities->GetSize();
        std::ofstream f(project);
        auto dump = data.dump(4);
        f.write(dump.data(), dump.size());
        f.close();
    }

}
