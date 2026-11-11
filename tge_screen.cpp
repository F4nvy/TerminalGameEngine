#include "tge.hpp"

void Screen::draw (){
    std::string buffer;
    buffer.reserve (width * height * 20);

    buffer += "\033[H";

    std::string lastTopColor = "";
    std::string lastBottomColor = "";

    for (uint16_t i = 0; i < height; i += 2){

        uint16_t topRowOffset = i * width;
        uint16_t bottomRowOffset = (i + 1) * width;

        for (uint8_t j = 0; j < width; j++){

            std::string& currentTopColor = board [j + topRowOffset];
            std::string& currentBottomColor = board [j + bottomRowOffset];

            if (currentTopColor != lastTopColor || currentBottomColor != lastBottomColor){
                buffer += "\033[48;" + board [j + topRowOffset] + ";" + "38;" + board [j + bottomRowOffset] + "m";

                lastTopColor = currentTopColor;
                lastBottomColor = currentBottomColor;
            }

            buffer += "▄";

        }
    }

    buffer += "\033[m";

    std::cout << buffer << std::flush;
}

void Screen::clear (const std::string& color){
    for (uint8_t i = 0; i < height; i++){
        for (uint8_t j = 0; j < width; j++){

            add (j, i, color);

        }
    }
}

void Screen::add (int16_t x, int16_t y, const std::string& color){
    if (color == "") return;

    if (x < 0 || y < 0 || x >= width || y >= height) return;

    uint16_t boardPos = x + y * width;

    board [boardPos] = color;
}

void Screen::fillColor (const std::string& color){
    currentFillColor = color;
}

void Screen::strokeColor (const std::string& color){
    currentStrokeColor = color;
}

void Screen::fillRect (int16_t x, int16_t y, uint8_t width, uint8_t height){
    if (width == 0 || height == 0) return;

    for (int16_t i = y; i < y + height; i++){
        for (int16_t j = x; j < x + width; j++){

            add (j, i, currentFillColor);

        }
    }
}

void Screen::strokeRect (int16_t x, int16_t y, uint8_t width, uint8_t height){
    if (width == 0 || height == 0) return;

    uint8_t skip;

    for (int16_t i = y; i < y + height; i++){

        if (i == y || i == y + height - 1) skip = 1;
        else skip = width - 1;

        if (width > 1){
            for (int16_t j = x; j < x + width; j += skip){

                add (j, i, currentStrokeColor);

            }
        }
        else add (x, i, currentStrokeColor);

    }
}

void Screen::drawSprite (int16_t x, int16_t y, uint8_t width, uint8_t height, const std::vector <std::vector <std::string>>& sprite) {
    if (width == 0 || height == 0) return;

    for (uint8_t i = 0; i < height; i++){
        for (uint8_t j = 0; j < width; j++){

            std::string color = sprite [i][j];

            add (x + j, y + i, color);

        }
    }
}

void Screen::line (int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
    int16_t xDiff = std::abs (x2 - x1);
    int16_t yDiff = std::abs (y2 - y1);
    int16_t xStep = (x1 < x2) ? 1 : -1;
    int16_t yStep = (y1 < y2) ? 1 : -1;
    int16_t error = xDiff - yDiff;

    while (true){
        add (x1, y1, currentStrokeColor);

        if (x1 == x2 && y1 == y2) break;

        int16_t error2 = error * 2;

        if (error2 > -yDiff){
            error -= yDiff;
            x1 += xStep;
        }
        if (error2 < xDiff){
            error += xDiff;
            y1 += yStep;
        }
    }
}

Screen::Screen (const Game* GameAdress, const uint8_t width, const uint8_t height) : GameAdress (GameAdress), width (width), height (height) {
    board.resize (width * height, emptyColor);
}
