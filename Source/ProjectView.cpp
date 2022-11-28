#include "ProjectView.hpp"

namespace VisualEditor {

    ProjectView::ProjectView() {
        mProjectAddName.resize(15);
        int tw, th;
        LoadTextureFromFile("../Resources/project.png", &mProjectIcon, &tw, &th);
        LoadTextureFromFile("../Resources/Add.png", &mProjectAddIcon, &tw, &th);
        LoadTextureFromFile("../Resources/cancel.png", &mCancelProjectAddIcon, &tw, &th);
        LoadTextureFromFile("../Resources/save.png", &mSuccesProjectAddIcon, &tw, &th);
    }

    void ProjectView::Render(SDL_Window *window) {
        SDL_GetWindowSize(window, &mScrWidth, &mScrHeight);
        ImGui::SetNextWindowSize(ImVec2(mScrWidth * 0.28, mScrHeight * 0.35));
        if (mOpened) {
            ImGui::Begin("Project", &mOpened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
            ImGui::BeginChild("##List", ImVec2(mScrWidth * 0.27, mScrHeight * 0.23));
            if (ImGui::BeginTable("##ProjectList", 1, ImGuiTableFlags_Borders)) {
                int Count = (*mData)["Count"];
                for (int i = 0; i < Count; ++i) {
                    ImGui::TableNextRow();
                    std::string projName = (*mData)[std::to_string(i)]["Name"];
                    std::string projNum = "##" + projName + std::to_string(i);
                    RenderProjectTable(projName, projNum);
                    ImGui::TableNextRow();
                }
                ImGui::EndTable();
            }
            ImGui::EndChild();
            if (!mProjectAddProcess) {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ((mScrWidth * 0.268) / 2) - 25);
                if (ImGui::ImageButton((ImTextureID)mProjectAddIcon,
                                       ImVec2(50, 50), ImVec2(0, 0), ImVec2(1, 1), 0,
                                       mBtnColor)) {
                    mProjectAddProcess = true;
                }
                mBtnColor = ImVec4(0.129, 0.141, 0.149, 1.0);
                if (ImGui::IsItemHovered())
                    mBtnColor = ImVec4(0.129, 0.141, 0.149, 0.7);
            }
            else {
                RenderProjectAdd();
            }
            ImGui::End();
        }
    }

    void ProjectView::RenderProjectTable(std::string projName, std::string projNum) {
        ImGui::TableSetColumnIndex(0);
        ImGui::TableSetBgColor(ImGuiTableBgTarget_::ImGuiTableBgTarget_CellBg,
                               IM_COL32(81, 81, 81, 255));
        ImGui::Image((ImTextureID)mProjectIcon, ImVec2(60, 50));
        ImGui::SameLine();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 17);
        ImGui::Text("%s", projName.c_str());
        ImGui::SameLine();
        ImGui::Selectable(projNum.c_str(), false,
                          ImGuiSelectableFlags_SpanAllColumns, ImVec2(mScrWidth * 0.2685, 50));
    }

    void ProjectView::RenderProjectAdd() {
        if (ImGui::BeginTable("##ProjectAdd", 1)) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_::ImGuiTableBgTarget_CellBg,
                                   IM_COL32(81, 81, 81, 255));
            ImGui::Image((ImTextureID)mProjectIcon, ImVec2(60, 50));
            ImGui::SameLine();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 17);
            ImGui::InputText("##ProjectNameText", &mProjectAddName[0], 15);
            ImGui::SameLine();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 16);
            if (ImGui::ImageButton((ImTextureID)mCancelProjectAddIcon,
                    ImVec2(14, 15))) {
                ClearName();
                mProjectAddProcess = false;
            }
            ImGui::SameLine();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 16);
            if (ImGui::ImageButton((ImTextureID)mSuccesProjectAddIcon,
                                   ImVec2(14, 15))) {
                mAddProjectCallBack(mProjectAddName);
                ClearName();
                mProjectAddProcess = false;
            }
            ImGui::EndTable();
        }
    }

    void ProjectView::OnAddProjectCallBack(const std::function<void(std::string)> &fn) {
        mAddProjectCallBack = fn;
    }

    void ProjectView::SetData(std::shared_ptr<nlohmann::json> data) {
        mData = data;
    }

    void ProjectView::ClearName() {
        mProjectAddName.clear();
        mProjectAddName.resize(15);
    }

}