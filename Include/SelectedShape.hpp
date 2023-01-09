#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class SelectedShape final : public Shape {
        public:
            SelectedShape() = default;
            explicit SelectedShape(std::shared_ptr<Shape> shape);
            void Render() override;
            void Load(nlohmann::json* data, uint32_t* index) override;
            void Save(nlohmann::json* data, uint32_t* index) override;
            ImVec2 GetSize() override { return mShape->GetSize(); };
            bool IsMouseHover(ImVec2 mousePos) override;
            bool IsInFlexBorder(ImVec2 mouse) override;
            void Amplify(ImVec2 mouse) override;
            void Flex(double dist) override;
            std::string GetName() const override { return "SelectedShape"; }
            Quad GetBounds(ImVec2 pos) override;
            void Move(ImVec2 delta) override;
            Shape* Copy() override;
        private:
            ImVec2 mSize = ImVec2(0.4, 0.4);
            std::shared_ptr<Shape> mShape;
        };

    }
}