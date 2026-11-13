#include "tge.hpp"

void Screen::draw (){
    std::string buffer;
    buffer.reserve (width * height * 20);

    buffer += "\033[H";

    Color lastTopCol = {0, 0, 0, 1};
    Color lastBotCol = {0, 0, 0, 1};

    for (uint16_t i = 0; i < height; i += 2){

        uint16_t topRowOffset = i * width;
        uint16_t bottomRowOffset = (i + 1) * width;
        
        bool rowChange = 0;

        for (uint8_t j = 0; j < width; j++){

            Color& curTopCol = board [j + topRowOffset];
            Color& curBotCol = board [j + bottomRowOffset];
            
            Color& curPrevTopCol = prevBoard [j + topRowOffset];
            Color& curPrevBotCol = prevBoard [j + bottomRowOffset];

            if (curTopCol.r != curPrevTopCol.r || curTopCol.g != curPrevTopCol.g || curTopCol.b != curPrevTopCol.b || curTopCol.transparent != curPrevTopCol.transparent ||
                curBotCol.r != curPrevBotCol.r || curBotCol.g != curPrevBotCol.g || curBotCol.b != curPrevBotCol.b || curBotCol.transparent != curPrevBotCol.transparent){
                rowChange = 1;
                break;            
            }
        
        }
        
        if (!rowChange) continue;

        buffer += "\033[" + std::to_string (i / 2 + 1) + ";1H";
    
        for (uint8_t j = 0; j < width; j++){

            Color& curTopCol = board [j + topRowOffset];
            Color& curBotCol = board [j + bottomRowOffset];

            if (curTopCol.r != lastTopCol.r || curTopCol.g != lastTopCol.g || curTopCol.b != lastTopCol.b || curTopCol.transparent != lastTopCol.transparent ||
                curBotCol.r != lastBotCol.r || curBotCol.g != lastBotCol.g || curBotCol.b != lastBotCol.b || curBotCol.transparent != lastBotCol.transparent){
                buffer += "\033[48;2;" + std::to_string (curTopCol.r) + ";" + std::to_string (curTopCol.g) + ";" + std::to_string (curTopCol.b) + ";" + "38;2;" +
                            std::to_string (curBotCol.r) + ";" + std::to_string (curBotCol.g) + ";" + std::to_string (curBotCol.b) + "m";

                lastTopCol = curTopCol;
                lastBotCol = curBotCol;
            }

            buffer += "▄";

            prevBoard [j + topRowOffset] = curTopCol;
            prevBoard [j + bottomRowOffset] = curBotCol;

        }
    }

    buffer += "\033[m";

    std::cout << buffer << std::flush;
}

void Screen::clear (const Color color){
    for (uint8_t i = 0; i < height; i++){
        for (uint8_t j = 0; j < width; j++){

            add (j, i, color);

        }
    }
}

void Screen::add (int16_t x, int16_t y, const Color color){
    if (color.transparent == 1) return;

    if (x < 0 || y < 0 || x >= width || y >= height) return;

    uint16_t boardPos = x + y * width;

    board [boardPos] = color;
}

void Screen::fillColor (const Color color){
    currentFillColor = color;
}

void Screen::strokeColor (const Color color){
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

void Screen::drawSprite (int16_t x, int16_t y, uint8_t width, uint8_t height, const std::vector <std::vector <Color>>& sprite) {
    if (width == 0 || height == 0) return;

    for (uint8_t i = 0; i < height; i++){
        for (uint8_t j = 0; j < width; j++){

            Color color = sprite [i][j];

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
    prevBoard.resize (width * height, {0, 0, 0, 1});
}
