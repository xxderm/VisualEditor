#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class SelectedShape final : public Shape {
        public:
            SelectedShape() = default;
            explicit SelectedShape(const std::shared_ptr<Shape>& shape);
            void Render() override;
            void Load(nlohmann::json* data) override;
            void Save(nlohmann::json* data) override;
            void SetColor(ImVec4 color) override { mShape->SetColor(color); }
            void Move(ImVec2 delta) override { mShape->Move(delta); Shape::Move(delta); }
            ShapeType GetShapeType() const override { return mShape->GetShapeType(); }
            ImVec2 GetSize() override { return mShape->GetSize(); };
            bool IsMouseHover(ImVec2 mousePos) override;
            bool IsInFlexBorder(ImVec2 mouse) override;
            void Amplify(ImVec2 mouse) override;
            void Flex(double dist) override;
            std::string GetName() const override { return "SelectedShape"; }
            Quad GetBounds(ImVec2 pos) override;
            Shape* Copy() override;
            std::shared_ptr<Shape> Extract() { return mShape; }
        private:
            std::shared_ptr<Shape> mShape;
        };

    }
}