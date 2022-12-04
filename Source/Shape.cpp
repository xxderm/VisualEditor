#pragma once

#include <Shape.hpp>

namespace VisualEditor::Graphics {

    bool Graphics::Shape::CheckBounds(ImVec2 pos) {
        auto quad = this->GetBounds(pos);
        if (quad.TopLeft.x < -1. || quad.TopRight.x > 1.)
            return true;
        if (quad.TopRight.y > 1.)
            return true;
        if (quad.BtmLeft.x < -1. || quad.BtmRight.x > 1.)
            return true;
        if (quad.BtmRight.y < -1.)
            return true;
        return false;
    }

    void Shape::OnEvent(SDL_Event *event, ImVec2 mousePos) {
        if (event->type == SDL_KEYDOWN)
            if (event->key.keysym.sym == SDLK_LSHIFT)
                mShift = true;
        if (event->type == SDL_KEYUP)
            if (event->key.keysym.sym == SDLK_LSHIFT)
                mShift = false;
    }
}