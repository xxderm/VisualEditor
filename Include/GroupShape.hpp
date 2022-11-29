#pragma once
#include "Shape.hpp"

namespace VisualEditor::Graphics {

    class GroupShape final : public Shape {
    public:
        void Add(std::shared_ptr<Shape> shape);
        void Render() override;
        void OnEvent(SDL_Event *event, ImVec2 mousePos) override {}
        std::string GetName() const override { return "GroupShape"; }
    protected:
        bool CheckBounds(ImVec2 pos) override{}
    private:
        Storage<std::shared_ptr<Shape>> mEntities;
    };

}