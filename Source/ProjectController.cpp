#include "ProjectController.hpp"

#include <utility>

namespace VisualEditor {

    ProjectController::ProjectController() {
        mProjectView = std::make_shared<ProjectView>();
        mProjectView->OnAddProjectCallBack([this](const std::string& name){
            AddProjectToList(name);
        });
        ReadProjectListFile();
    }

    void ProjectController::Render(SDL_Window *window) {
        mProjectView->Render(window);
    }

    void ProjectController::OnEvent(SDL_Event *event) {

    }

    void ProjectController::ReadProjectListFile() {
        std::fstream f("list.json");
        mJsonData = std::make_shared<nlohmann::json>(nlohmann::json::parse(f));
        mProjectView->SetData(mJsonData);
        f.close();
    }

    void ProjectController::Update() {
        ReadProjectListFile();
    }

    void ProjectController::AddProjectToList(const std::string& name) {
        int count = (*mJsonData)["Count"];
        (*mJsonData)[std::to_string(count)]["Name"] = name;
        (*mJsonData)["Count"] = 1 + count;
        std::ofstream f("list.json");
        auto dump = mJsonData->dump(4);
        f.write(dump.data(), dump.size());
        f.close();
        Update();
    }

}