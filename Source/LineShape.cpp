#include "LineShape.hpp"

namespace VisualEditor {
    namespace Graphics {

        void LineShape::Render() {
            GraphicUtility::LineEdge(mPointBegin, mPointEnd);
        }

    }
}