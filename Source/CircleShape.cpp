#include "CircleShape.hpp"

namespace VisualEditor::Graphics {

    void CircleShape::Render() {
        GraphicUtility::CircleEdge(mPosition, mRadius, mColor);
        if (mHovered)
            GraphicUtility::CircleEdge(mPosition, mRadius + 0.005, ImVec4(1, 1, 0.6, 1));
        if (mSelected)
            GraphicUtility::Grid(mPosition, mRadius * 2.015);

    }

    Quad CircleShape::GetBounds(ImVec2 pos) {
        Quad quad;
        quad.TopLeft = ImVec2(pos.x - (mRadius + 0.01), pos.y + (mRadius + 0.01));
        quad.TopRight = ImVec2(pos.x + (mRadius + 0.01), pos.y + (mRadius + 0.01));
        quad.BtmLeft = ImVec2(pos.x - (mRadius + 0.01), pos.y - (mRadius + 0.01));
        quad.BtmRight = ImVec2(pos.x + (mRadius + 0.01), pos.y - (mRadius + 0.01));
        return quad;
    }

    bool CircleShape::IsMouseHover(ImVec2 mousePos) {
        auto dist = sqrt( ((mPosition.x - mousePos.x) * (mPosition.x - mousePos.x))
                          + ((mPosition.y - mousePos.y) * (mPosition.y - mousePos.y)) );
        return dist <= mRadius;
    }

    Shape* CircleShape::Copy() {
        CircleShape* copy = new CircleShape();
        copy->mRadius = this->mRadius;
        copy->mPosition = this->mPosition;
        copy->mColor = this->mColor;
        return copy;
    }

    void CircleShape::Move(ImVec2 delta) {
        mPosition = delta;
    }

    bool CircleShape::IsInFlexBorder(ImVec2 mouse) {
        auto dist = sqrt( ((mPosition.x - mouse.x) * (mPosition.x - mouse.x))
                          + ((mPosition.y - mouse.y) * (mPosition.y - mouse.y)) );
        return dist > mRadius && dist < mRadius + 0.05;
    }

    void CircleShape::Amplify(ImVec2 mouse) {
        auto dist = sqrt( ((mPosition.x - mouse.x) * (mPosition.x - mouse.x))
                          + ((mPosition.y - mouse.y) * (mPosition.y - mouse.y)) );
        auto delta = mRadius - dist;
        //mRadius = dist - 0.025;
        Flex(dist - 0.025);
    }

    void CircleShape::Flex(double dist) {
        mRadius = dist;
    }

}