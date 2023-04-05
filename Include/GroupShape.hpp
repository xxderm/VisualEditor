#pragma once
#include "Shape.hpp"

namespace VisualEditor::Graphics {

    class GroupShape final : public Shape {
    public:
        GroupShape() = default;
        GroupShape(const GroupShape& other);
        void Add(Shape* shape);
        void Render() override;
        void Load(nlohmann::json* data) override;
        void Save(nlohmann::json* data) override;
        void Move(ImVec2 delta) override;
        ImVec2 GetSize() override { return ImVec2(GetQuadSize().z, GetQuadSize().w); };
        bool IsMouseHover(ImVec2 mousePos) override;
        bool IsInFlexBorder(ImVec2 mouse) override;
        void Amplify(ImVec2 mouse) override;
        void Flex(double dist) override;
        std::string GetName() const override { return "GroupShape"; }
        ShapeType GetShapeType() const override { return ShapeType::GROUP; }
        Storage<Shape*> GetEntities() { return mEntities; }
        void SetColor(ImVec4 color) override {
            for (uint32_t i = 0; i < mEntities.Size(); ++i) {
                mEntities[i]->SetColor(color);
            }
        }
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