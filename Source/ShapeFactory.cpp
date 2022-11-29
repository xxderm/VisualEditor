#include "ShapeFactory.hpp"

namespace VisualEditor {
    namespace Graphics {

        std::shared_ptr<Shape> ShapeFactory::CreateShape(ShapeType shapeType) {
            switch (shapeType) {
                case CIRCLE:
                    return std::make_shared<CircleShape>();
                case TRIANGLE:
                    return std::make_shared<TriangleShape>();
                case QUAD:
                    return std::make_shared<QuadShape>();
                case LINE:
                    return std::make_shared<LineShape>();
                case GROUP:
                    return std::make_shared<GroupShape>();
            }
        }

    }
}