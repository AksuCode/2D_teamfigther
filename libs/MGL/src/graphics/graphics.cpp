#include "../../include/grahics.hpp"

Graphics::Graphics() {
    mgl_window_ = new Window();
}

Graphics::~Graphics() {
    delete mgl_window_;
}

Graphics::initializeOrUpdateGraphics() {
    mgl_window_->createOrUpdateWindow(false, 1000, 1000);
    mgl_renderer_ = mgl_window_->getRenderer();
}