#include "gui_api.hpp"

void createEmbeddedBox(int x, int y, int width, int height, const std::string &color, const std::string &text);


void resizeEmbeddedBox(int newWidth, int newHeight);


void changeEmbeddedBoxColor(const std::string &newColor);


// Moves the embedded box to a new position
void moveEmbeddedBox(int newX, int newY);


// Adds or updates text inside the embedded box
void setEmbeddedBoxText(const std::string &text);
