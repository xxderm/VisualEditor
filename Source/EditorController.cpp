#include "EditorController.hpp"

namespace VisualEditor {

    EditorController::EditorController(SDL_Window* window) {
        mEntities = std::make_shared<Storage<std::shared_ptr<Graphics::Shape>>>();
        mEditorView = std::make_shared<EditorView>(window);
        mEditorView->OnAddShape([this](Graphics::ShapeType type) {
            mCmdDispatcher.ExecuteCommand(std::make_shared<AddShapeCommand>(mEntities, type));
        });
        mEditorView->OnChangeColor([this](float r, float g, float b) {
            for (uint32_t i = 0; i < mEntities->Size(); i++) {
                if ((*mEntities)[i]->IsSelected()) {
                    mCmdDispatcher.ExecuteCommand(
                            std::make_shared<ShapeChangeColorCommand>(
                                    (*mEntities)[i],
                                    ImVec4(r, g, b, 1.))
                                    );
                }
            }
        });
        mEditorView->OnMakeGroup([this]() {
            std::vector<uint32_t> indicesToErase;
            auto gs = Graphics::ShapeFactory::CreateShape(Graphics::ShapeType::GROUP);
            for (uint32_t i = 0; i < mEntities->Size(); i++) {
                if ( mEntities->At(i)->GetName() == "SelectedShape" ) {
                    auto wrapped = dynamic_cast<Graphics::SelectedShape*>(mEntities->At(i).get());
                    ((Graphics::GroupShape*)gs.get())->Add(wrapped->Copy());
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
                if (mEntities->At(i)->GetName() == "SelectedShape")
                    indicesToErase.push_back(i);
            }
            for (auto ind : indicesToErase)
                mEntities->Remove(ind);
        });
        mEditorView->OnUnGroup([this]() {
            std::vector<uint32_t> indicesToErase;
            for (uint32_t i = 0; i < mEntities->Size(); i++) {
                if (mEntities->At(i)->GetName() == "SelectedShape") {
                    indicesToErase.push_back(i);
                    auto wrapped = dynamic_cast<Graphics::SelectedShape*>(mEntities->At(i).get());
                    auto extracted = dynamic_cast<Graphics::GroupShape*>(wrapped->Extract()->Copy());
                    auto entities = extracted->GetEntities();
                    for (uint32_t j = 0; j < entities.Size(); ++j) {
                        mEntities->Push(std::shared_ptr<Graphics::Shape>(entities[j]));
                    }
                }
            }
            for (auto ind : indicesToErase)
                mEntities->Remove(ind);
        });
        mEditorView->OnUndo([this]() {
            mCmdDispatcher.Undo();
        });
        mEditorView->OnRedo([this]() {
            mCmdDispatcher.Redo();
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
        mEditorView->SetActions(mCmdDispatcher.GetStack());
        mEditorView->Render(window);
        mEntityModel.SetEntities(&mEntities);
        mEntityModel.SetScrSize(ImVec2(ww, wh));

    }

    void EditorController::OnEvent(SDL_Event *event) {
        mCursor = SDL_SYSTEM_CURSOR_ARROW;
        auto scenePos = mEditorView->GetScenePos();
        auto sceneSize = mEditorView->GetSceneSize();
        auto pos = ImVec2(event->motion.x - scenePos.x, event->motion.y - scenePos.y);
        // Координаты [-1;1]
        auto nx = (float)((float)pos.x / sceneSize.x) * 2.f - 1.f;
        auto ny = (float)((float)-pos.y / sceneSize.y) * 2.f + 1.f;
        // TODO: -ny
        auto inScene = ((nx > -1 && nx < 1) && (-ny > -1 && -ny < 1));

        if (event->type == SDL_MOUSEBUTTONUP && inScene) {
            // TODO: Команда на перемещение фигуры
            mMousePressed = false;
        }

        // Keys Down
        if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_LSHIFT)
                mShift = true;
            if (event->key.keysym.sym == SDLK_ESCAPE) {
                // TODO: Escape
                for (size_t i = 0; i < mEntities->Size(); ++i) {
                    if (mEntities->At(i)->GetName() == "SelectedShape") {
                        auto wrapped = dynamic_cast<Graphics::SelectedShape*>(mEntities->At(i).get());
                        mEntities->Replace(i, wrapped->Extract());
                    }
                }
            }
        }
        // Keys Up
        if (event->type == SDL_KEYUP) {
            if (event->key.keysym.sym == SDLK_LSHIFT) {
                mShift = false;
            }
        }

        if (event->type == SDL_MOUSEBUTTONDOWN && inScene) {
            mMousePressed = true;
            mBeginMousePos = ImVec2(nx, -ny);
            mMotionPrev = { -1, -1 };
            for (size_t i = 0; i < mEntities->Size(); ++i) {
                if (mEntities->At(i)->GetName() == "SelectedShape") continue;
                if (mEntities->At(i)->IsMouseHover(ImVec2(nx, -ny)) && mMousePressed && mShift) {
                    const auto& shape = mEntities->At(i);
                    const auto& selected = std::make_shared<Graphics::SelectedShape>(shape);
                    mEntities->Replace(i, selected);
                }
            }
        }

        if (event->type == SDL_MOUSEMOTION && inScene && mMousePressed) {
            ImVec2 delta = { 0,  0};
            if (mMotionPrev.x != -1) {
                delta = {-(mMotionPrev.x - nx), -ny - mMotionPrev.y};
                mMotionPrev = {nx, -ny};
            }
            else {
                mMotionPrev = mBeginMousePos;
                delta = { nx - mBeginMousePos.x, -ny - mBeginMousePos.y };
                if (nx == mMotionPrev.x && -ny == mMotionPrev.y) delta = { 0, 0 };
            }
            bool block = false;
            ImVec2 nextPos{};
            for (int i = 0; i < mEntities->Size(); ++i) {
                auto shapePos = mEntities->At(i)->GetPosition();
                nextPos = { shapePos.x + delta.x, shapePos.y + delta.y };
                if (mEntities->At(i)->CheckBounds(nextPos)) block = true;
            }
            for (int i = 0; i < mEntities->Size(); ++i) {
                if (mEntities->At(i)->GetName() == "SelectedShape" && !block) {
                    mEntities->At(i)->Move(delta);
                }
            }
        }

        /*
for (uint32_t i = 0; i < mEntities->Size(); i++) {
    (*mEntities)[i]->OnEvent(event, ImVec2(nx, -ny));
    if ((*mEntities)[i]->IsInFlexBorder(ImVec2(nx, -ny)))
        mCursor = SDL_SYSTEM_CURSOR_SIZEWE;
}
*/
    }

    void EditorController::Save(std::string project) {
        std::string name = project;
        nlohmann::json data;
        std::ofstream f;
        f.open(name.c_str(), std::ios_base::trunc);
        f.clear();
        uint32_t index = 0;
        for (uint32_t i = 0; i < mEntities->Size(); i++) {
            mEntities->At(i)->Save(&data, &index);
            ++index;
        }
        data["EntityCount"] = index;
        auto dump = data.dump(4);
        f.write(dump.data(), dump.size());
        f.close();
    }

    void EditorController::Load(std::string project) {
        mEntities = std::make_shared<Storage<std::shared_ptr<Graphics::Shape>>>();
        std::string name = project;
        std::ifstream f(name.c_str());
        nlohmann::json data = nlohmann::json::parse(f);
        uint32_t count = data["EntityCount"];
        for (uint32_t i = 0; i < count; ++i) {
            std::string shapeTitle = data[std::to_string(i)]["Name"];
            if (shapeTitle == "TriangleShape")
                mEntities->Push(Graphics::ShapeFactory::CreateShape(Graphics::ShapeType::TRIANGLE));
            if (shapeTitle == "CircleShape")
                mEntities->Push(Graphics::ShapeFactory::CreateShape(Graphics::ShapeType::CIRCLE));
            if (shapeTitle == "QuadShape")
                mEntities->Push(Graphics::ShapeFactory::CreateShape(Graphics::ShapeType::QUAD));
            mEntities->Back()->Load(&data, &i);
        }
    }

}
