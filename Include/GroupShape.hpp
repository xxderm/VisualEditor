#pragma once
#include "Shape.hpp"

namespace VisualEditor::Graphics {

    class GroupShape final : public Shape {
    public:
        GroupShape() {mEntities = std::make_shared<Storage<std::shared_ptr<Graphics::Shape>>>(100);}
        void Add(std::shared_ptr<Shape> shape);
        void Render() override;
        bool IsMouseHover(ImVec2 mousePos) override;
        std::string GetName() const override { return "GroupShape"; }
        std::shared_ptr<Shape> Copy() override {}
        Quad GetBounds(ImVec2 pos) override;
    private:
        std::shared_ptr<Storage<std::shared_ptr<Shape>>> mEntities;
    };

}