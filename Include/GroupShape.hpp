#pragma once
#include "Shape.hpp"

namespace VisualEditor::Graphics {

    class GroupShape final : public Shape {
    public:
        GroupShape() {  }
        void Add(Shape* shape);
        void Render() override;
        bool IsMouseHover(ImVec2 mousePos) override;
        std::string GetName() const override { return "GroupShape"; }
        Shape* Copy() override {}
        Quad GetBounds(ImVec2 pos) override;
    private:
        ImVec4 GetQuadSize();
    private:
        Storage<Shape*> mEntities;
        ImVec2 mSize{};
    };

}