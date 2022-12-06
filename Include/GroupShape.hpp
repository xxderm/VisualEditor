#pragma once
#include "Shape.hpp"

namespace VisualEditor::Graphics {

    class GroupShape final : public Shape {
    public:
        GroupShape() = default;
        GroupShape(const GroupShape& other);
        void Add(Shape* shape);
        void Render() override;
        bool IsMouseHover(ImVec2 mousePos) override;
        bool IsInFlexBorder(ImVec2 mouse) override;
        void Amplify(ImVec2 mouse) override;
        void Flex(double dist) override;
        void Move(ImVec2 delta) override;
        std::string GetName() const override { return "GroupShape"; }
        Storage<Shape*> GetEntities() { return mEntities; }
        Shape* Copy() override;
        Quad GetBounds(ImVec2 pos) override;
        ~GroupShape();
    private:
        ImVec4 GetQuadSize();
    private:
        Storage<Shape*> mEntities;
        ImVec2 mSize{};
    };

}