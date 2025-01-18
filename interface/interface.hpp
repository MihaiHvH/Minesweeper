#pragma once

#include "../structs.hpp"
#include "../graphics/graphics.hpp"

#include <vector>

class pInterface {
    private:
        bool bInit = false;
        void init(bool ow = false);
        void destroy();
    public:
    pInterface();
    ~pInterface();

    void(*pRender)(void);

    void drawPieces();
    void drawPiece(pPiece piece);

    std::vector<pPiece> pieces;

    void calcValuesAndPieces();
    void spawnMines(int mines, std::pair<double, double> noPos);
    pPiece &getPieceRel(std::pair<double, double> relPos);
    pPiece &getPiece(std::pair<double, double> pos);
    bool shouldSpawnMine();
    void spawnPiece(std::pair<double, double> pos, std::string value);

    bool isFlagPlaced(std::pair<double, double> pos);

    void handleWin();
    void handleFlagPlacementClick();
    void handleMineClick();
    void handleDigitClick();
    void handleBulkClick();
    void handleClick(bool rClick = false);

    pScreen screen;
    pGraphics graphics;
    pGameInfo gameInfo;
};