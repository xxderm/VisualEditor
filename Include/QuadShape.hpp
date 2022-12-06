#include "Shape.hpp"

namespace VisualEditor {
    namespace Graphics {

        class QuadShape final : public Shape {
        public:
            QuadShape() = default;
            QuadShape(const QuadShape& other);
            void Render() override;
            void Load(nlohmann::json* data, uint32_t* index) override;
            void Save(nlohmann::json* data, uint32_t* index) override;
            bool IsMouseHover(ImVec2 mousePos) override;
            bool IsInFlexBorder(ImVec2 mouse) override;
            void Amplify(ImVec2 mouse) override;
            void Flex(double dist) override;
            std::string GetName() const override { return "QuadShape"; }
            Quad GetBounds(ImVec2 pos) override;
            void Move(ImVec2 delta) override;
            Shape* Copy() override;
        private:
            ImVec2 mSize = ImVec2(0.4, 0.4);
        };

    }
}