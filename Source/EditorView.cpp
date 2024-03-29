#include "EditorView.hpp"

#include <utility>

namespace VisualEditor {

    EditorView::EditorView(SDL_Window* window) {
        SDL_GetWindowSize(window, &mScrWidth, &mScrHeight);
        mFrame = std::make_shared<FrameBuffer>(ImVec2(2000, 2000));
        int tw, th;
        LoadTextureFromFile("../Resources/tr.png", &mTriangleIcon, &tw, &th);
        LoadTextureFromFile("../Resources/cr.png", &mCircleIcon, &tw, &th);
        LoadTextureFromFile("../Resources/ln.png", &mLineIcon, &tw, &th);
        LoadTextureFromFile("../Resources/qu.png", &mQuadIcon, &tw, &th);
    }

    void EditorView::Render(SDL_Window *window) {
        SDL_GetWindowSize(window, &mScrWidth, &mScrHeight);
        RenderSceneEntities(window);
        RenderEntityList(window);
        RenderEntitySettings(window);
        RenderActionList(window);
        RenderScene(window);
    }

    void EditorView::RenderSceneEntities(SDL_Window *window) {

    }

    void EditorView::RenderEntityList(SDL_Window *window) {
        ImGui::SetNextWindowPos(ImVec2(5, mScrHeight * 0.25 + 20));
        ImGui::SetNextWindowSize(ImVec2(mScrWidth * 0.2, mScrHeight * 0.2));
        ImGui::Begin("Object list", 0,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
        if (ImGui::BeginTable("##Objects", 1)) {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_::ImGuiTableBgTarget_CellBg,
                                   IM_COL32(81, 81, 81, 255));
            if (ImGui::ImageButton((ImTextureID)mTriangleIcon, ImVec2(20, 20)))
                mOnAddCallBack(Graphics::ShapeType::TRIANGLE);
            ImGui::SameLine();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
            ImGui::Text("Triangle");
            ImGui::TableNextRow();
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_::ImGuiTableBgTarget_CellBg,
                                   IM_COL32(81, 81, 81, 255));
            if (ImGui::ImageButton((ImTextureID)mCircleIcon, ImVec2(20, 20)))
                mOnAddCallBack(Graphics::ShapeType::CIRCLE);
            ImGui::SameLine();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
            ImGui::Text("Circle");
            ImGui::TableNextRow();
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_::ImGuiTableBgTarget_CellBg,
                                   IM_COL32(81, 81, 81, 255));
            if (ImGui::ImageButton((ImTextureID)mLineIcon, ImVec2(20, 20)))
                ;//mOnAddCallBack(Graphics::ShapeType::LINE);
            ImGui::SameLine();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
            ImGui::Text("Line");
            ImGui::TableNextRow();
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_::ImGuiTableBgTarget_CellBg,
                                   IM_COL32(81, 81, 81, 255));
            if (ImGui::ImageButton((ImTextureID)mQuadIcon, ImVec2(20, 20)))
                mOnAddCallBack(Graphics::ShapeType::QUAD);
            ImGui::SameLine();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
            ImGui::Text("Quad");
            ImGui::TableNextRow();
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_::ImGuiTableBgTarget_CellBg,
                                   IM_COL32(81, 81, 81, 255));
            if (ImGui::Button("Sticky", ImVec2(20, 20)))
                mOnSetSticky();
            ImGui::SameLine();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
            ImGui::Text("Set sticky");
            ImGui::TableNextRow();
            ImGui::TableNextRow();

            ImGui::EndTable();
        }
        ImGui::End();
    }

    void EditorView::RenderEntitySettings(SDL_Window *window) {
        ImGui::SetNextWindowPos(ImVec2(5, mScrHeight * 0.45 + 20));
        ImGui::SetNextWindowSize(ImVec2(mScrWidth * 0.2, mScrHeight * 0.3));
        ImGui::Begin("Settings", 0,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
        if (ImGui::BeginTable("##Settings", 2)) {

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_::ImGuiTableBgTarget_CellBg,
                                   IM_COL32(81, 81, 81, 255));
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 3);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
            ImGui::Text("Color");
            ImGui::TableSetColumnIndex(1);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_::ImGuiTableBgTarget_CellBg,
                                   IM_COL32(81, 81, 81, 255));
            if (ImGui::Button("Change")) mColorEdit = true;
            if (mColorEdit) {
                ImGui::ColorPicker3("##ColorPick", mColor);
                if (ImGui::Button("Submit")) {
                    mOnChangeColorCallBack(mColor[0], mColor[1], mColor[2]);
                }
                if (ImGui::Button("Cancel"))
                    mColorEdit = false;
            }
            ImGui::EndTable();
        }
        ImGui::End();
    }

    void EditorView::RenderActionList(SDL_Window *window) {
        ImGui::SetNextWindowPos(ImVec2(5, mScrHeight * 0.75 + 20));
        ImGui::SetNextWindowSize(ImVec2(mScrWidth * 0.2, mScrHeight * 0.22));
        ImGui::Begin("Actions", 0,
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
        if (ImGui::BeginTable("##Objects", 1)) {
            std::stack<std::shared_ptr<ICommand>> temp;
            while (!mActions.empty()) {
                auto cmd = mActions.top();
                temp.push(cmd);
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TableSetBgColor(ImGuiTableBgTarget_::ImGuiTableBgTarget_CellBg,
                                       IM_COL32(81, 81, 81, 255));
                ImGui::Selectable(cmd->GetName().c_str());
                ImGui::TableNextRow();
                mActions.pop();
            }
            //mActions.swap(temp);
            ImGui::EndTable();
        }
        ImGui::End();
    }

    void EditorView::RenderScene(SDL_Window *window) {
        auto sceneSize = ImVec2(mScrWidth * 0.793, mScrHeight * 0.97);
        auto scenePos = ImVec2(mScrWidth * 0.204, 20);
        ImGui::SetNextWindowPos(scenePos);
        ImGui::SetNextWindowSize(sceneSize);
        ImGui::Begin("Scene", 0,
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
        // Рендер в буффер
        mFrame->Bind(ImVec4(0, 0, 2000, 2000));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (uint32_t i = 0; i < mEntities->Size(); i++)
            (*mEntities)[i]->Render();
        ImVec2 avail_size = ImGui::GetContentRegionAvail();
        mSceneSize = avail_size;
        ImGui::Image((void*)mFrame->GetTexture(), avail_size);
        mScenePos = ImGui::GetItemRectMin();
        mFrame->UnBind(ImVec4(0, 0, 2000, 2000));
        ImGui::PushItemWidth(150);
        if (ImGui::BeginPopupContextItem("##SceneContextMenu")) {
            if (ImGui::MenuItem("Group", "Selected entities")) {
                mOnMakeGroup();
            }
            if (ImGui::MenuItem("UnGroup")) {
                mOnUnGroup();
            }
            if (ImGui::MenuItem("Delete")) {
                mOnDelete();
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Undo", "Last action")) {
                mOnUndo();
            }
            if (ImGui::MenuItem("Redo")) {
                mOnRedo();
            }
            ImGui::EndPopup();
        }
        ImGui::PopItemWidth();
        ImGui::End();
    }

    void EditorView::OnAddShape(const std::function<void(Graphics::ShapeType)> &fn) {
        mOnAddCallBack = fn;
    }

    void EditorView::SetEntities(const std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>>& entities) {
        mEntities = entities;
    }

    void EditorView::SetActions(const std::stack<std::shared_ptr<ICommand>>& actions) {
        mActions = actions;
    }

    void EditorView::OnChangeColor(const std::function<void(float, float, float)> &fn) {
        mOnChangeColorCallBack = fn;
    }

    void EditorView::OnMakeGroup(const std::function<void()> &fn) {
        mOnMakeGroup = fn;
    }

    void EditorView::OnUnGroup(const std::function<void()> &fn) {
        mOnUnGroup = fn;
    }

    void EditorView::OnDelete(const std::function<void()> &fn) {
        mOnDelete = fn;
    }

    void EditorView::OnUndo(const std::function<void()> &fn) {
        mOnUndo = fn;
    }

    void EditorView::OnRedo(const std::function<void()> &fn) {
        mOnRedo = fn;
    }

    void EditorView::OnSetSticky(const std::function<void()> &fn) {
        mOnSetSticky = fn;
    }
}