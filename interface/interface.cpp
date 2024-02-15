#include "../main.hpp"
#include "interface.hpp"
#include <cctype>
#include <cstddef>
#include <random>
#include <string>
#include <queue>

void pInterface::init(bool ow) {
    gameInfo.digitCol[0] = graphics.createNewColor(8, 0, 254);
    gameInfo.digitCol[1] = graphics.createNewColor(8, 135, 15);
    gameInfo.digitCol[2] = graphics.createNewColor(248, 12, 26);
    gameInfo.digitCol[3] = graphics.createNewColor(0, 0, 132);
    gameInfo.digitCol[4] = graphics.createNewColor(132, 0, 0);
    gameInfo.digitCol[5] = graphics.createNewColor(0, 130, 132);
    gameInfo.digitCol[6] = graphics.createNewColor(132, 0, 132);
    gameInfo.digitCol[7] = graphics.createNewColor(117, 117, 117);
    gameInfo.pieceColor = graphics.createNewColor(198, 198, 198);
    gameInfo.downRightColor = graphics.createNewColor(128, 128, 128);
    gameInfo.upLeftColor = graphics.white;

    if (!bInit || ow) {
        std::vector<std::pair<int, int>> flags;

        if (ow) {
            std::pair<int, int> pos = getPieceRel(screen.mousePointer).pos;
            for (int i = 0; i < pieces.size(); ++i)
                if (pieces.at(i).flag)
                    flags.push_back(pieces.at(i).pos);
            pieces.clear();
            spawnMines(gameInfo.mines, pos);
        }
        calcValuesAndPieces();

        if (ow)
            for (auto &i : pieces)
                for (auto j : flags)
                    if (i.pos == j)
                        i.flag = true;
        bInit = true;
    }
}

void pInterface::destroy() {
    bInit = false;
    pieces.clear();
}

pInterface::pInterface() {
    init();
}

pInterface::~pInterface() {

}

void pInterface::calcValuesAndPieces() {
    auto mines = pieces;

    for (int i = 0; i < screen.size.first / gameInfo.pieceSize.first; ++i) {
        for (int j = 0; j < screen.size.second / gameInfo.pieceSize.second; ++j) {
            bool prm = false;
            for (auto k : mines)
                if (k.pos == std::make_pair(i * gameInfo.pieceSize.first, j * gameInfo.pieceSize.second)) {
                    prm = true;
                    break;
                }
            if (!prm) spawnPiece(std::make_pair(i * gameInfo.pieceSize.first, j * gameInfo.pieceSize.second), "NULL");
        }
    }
    for (auto k : pieces) {
        if (k.value == "MINE") {
            std::vector<std::pair<int, int>> dir = {
                { k.pos.first - gameInfo.pieceSize.first, k.pos.second - gameInfo.pieceSize.second },
                { k.pos.first, k.pos.second - gameInfo.pieceSize.second },
                { k.pos.first + gameInfo.pieceSize.first, k.pos.second - gameInfo.pieceSize.second },
                { k.pos.first - gameInfo.pieceSize.first, k.pos.second },
                { k.pos.first + gameInfo.pieceSize.first, k.pos.second },
                { k.pos.first - gameInfo.pieceSize.first, k.pos.second + gameInfo.pieceSize.second },
                { k.pos.first, k.pos.second + gameInfo.pieceSize.second },
                { k.pos.first + gameInfo.pieceSize.first, k.pos.second + gameInfo.pieceSize.second }
            };
            for (auto x : dir) {
                if (x.first >= 0 && x.first < screen.size.first && x.second >= 0 && x.second < screen.size.second) {
                    for (auto &o : pieces) {
                        if (k.pos != o.pos && x == o.pos && o.value != "MINE") {
                            if (o.value == "NULL")
                                o.value = '1';
                            else if (std::isdigit(o.value.at(0)))
                                o.value = std::to_string(std::stoi(o.value) + 1);
                        }
                    }
                }
            }
        }
    }
}

void pInterface::drawPiece(pPiece piece) {
    if (piece.value.at(piece.value.size() - 1) != 'D') {
        graphics.drawRectPoints(
        piece.pos,
        { piece.pos.first, piece.pos.second + gameInfo.pieceSize.first / 8 },
        { piece.pos.first + (7  * gameInfo.pieceSize.first) / 8, piece.pos.second + gameInfo.pieceSize.second / 8 },
        { piece.pos.first + gameInfo.pieceSize.first, piece.pos.second },
        gameInfo.upLeftColor);
        graphics.drawRectPoints(
            { piece.pos.first, piece.pos.second + gameInfo.pieceSize.second / 8 },
            { piece.pos.first, piece.pos.second + gameInfo.pieceSize.second },
            { piece.pos.first + gameInfo.pieceSize.first / 8, piece.pos.second + (7 * gameInfo.pieceSize.second) / 8 },
            { piece.pos.first + gameInfo.pieceSize.first / 8, piece.pos.second + gameInfo.pieceSize.second / 8 },
            gameInfo.upLeftColor);

        graphics.drawRectPoints(
            { piece.pos.first + gameInfo.pieceSize.first, piece.pos.second },
            { piece.pos.first + gameInfo.pieceSize.first, piece.pos.second + gameInfo.pieceSize.second },
            { piece.pos.first + (7 * gameInfo.pieceSize.first) / 8, piece.pos.second + gameInfo.pieceSize.second },
            { piece.pos.first + (7 * gameInfo.pieceSize.first) / 8, piece.pos.second + gameInfo.pieceSize.second / 8 },
            gameInfo.downRightColor);
        graphics.drawRectPoints(
            { piece.pos.first, piece.pos.second + gameInfo.pieceSize.second },
            { piece.pos.first + gameInfo.pieceSize.first / 8, piece.pos.second + (7 * gameInfo.pieceSize.second) / 8 },
            { piece.pos.first + (7 * gameInfo.pieceSize.first) / 8, piece.pos.second + (7 * gameInfo.pieceSize.second) / 8 },
            { piece.pos.first + (7 * gameInfo.pieceSize.first) / 8, piece.pos.second + gameInfo.pieceSize.second },
            gameInfo.downRightColor);
        //graphics.drawRect({ piece.pos.first + gameInfo.pieceSize.first / 8, piece.pos.second + gameInfo.pieceSize.second / 8 }, { (3 * gameInfo.pieceSize.first) / 4, (3 * gameInfo.pieceSize.second) / 4 }, gameInfo.pieceColor);
        //for debuging
        //if (piece.value == "MINE") 
            //if (piece.show)
             //if (piece.value != "NULL")
             /*graphics.drawText(
                { piece.pos.first + 5, piece.pos.second + gameInfo.pieceSize.second / 2 },
                GLUT_BITMAP_HELVETICA_10,
                piece.value.append(" " + std::to_string(piece.show)).c_str(),
                piece.show ? graphics.red : graphics.black);
        *///end
    }
    else if (piece.value != "NULL_D" && std::isdigit(piece.value.at(0))) {
        int nr = piece.value.at(0) - '0';
        std::string rStr = std::to_string(nr);
        const char* str = rStr.c_str();
        std::pair<int, int> sz = graphics.getTextSize(str, GLUT_BITMAP_TIMES_ROMAN_24);
        sz.second += sz.second / 2;
        graphics.drawText({ piece.pos.first - sz.first / 2 + gameInfo.pieceSize.first / 2, piece.pos.second + sz.second - sz.second / 2 + gameInfo.pieceSize.second / 2 }, GLUT_BITMAP_TIMES_ROMAN_24, str, gameInfo.digitCol[nr - 1]);
    }
    else if (piece.value.at(0) == 'M') {
        graphics.drawFilledCircle({ piece.pos.first + gameInfo.pieceSize.first / 2, piece.pos.second + gameInfo.pieceSize.second / 2 }, gameInfo.pieceSize.first / 2, graphics.black);
    }

    if (piece.flag)
        graphics.drawFilledCircle({ piece.pos.first + gameInfo.pieceSize.first / 2, piece.pos.second + gameInfo.pieceSize.second / 2 }, gameInfo.pieceSize.first / 2 - 10, graphics.red);
}

void pInterface::spawnMines(int mines, std::pair<int, int> noPos) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(0, (screen.size.first / gameInfo.pieceSize.first) - 1);
    std::uniform_int_distribution<> distY(0, (screen.size.second / gameInfo.pieceSize.second) - 1);
    
    for (int i = 0; i < gameInfo.mines; ++i) {
        std::pair<int, int> newMinePos = { 
            distX(gen) * gameInfo.pieceSize.first,
            distY(gen) * gameInfo.pieceSize.second 
        };
        int r = 0;
        while (true) {
            for (auto k : pieces) {
                if (k.pos == newMinePos || newMinePos == noPos) {
                    newMinePos = { 
                    distX(gen) * gameInfo.pieceSize.first,
                    distY(gen) * gameInfo.pieceSize.second 
                    };
                    r = 0;
                    break;
                }
                else ++r;
            }
            if (r == pieces.size()) {
                break;
            }
        }
        spawnPiece(newMinePos, "MINE");
    }
}

void pInterface::drawPieces() {
    for (auto i : pieces)
        drawPiece(i);
}

void pInterface::spawnPiece(std::pair<int, int> pos, std::string value) {
    pPiece nM;
    nM.pos = pos;
    nM.value = value;
    pieces.push_back(nM);
}

pPiece &pInterface::getPieceRel(std::pair<int, int> relPos) {
    for (auto &i : pieces)
        if (graphics.mouseInRegion(relPos, i.pos, gameInfo.pieceSize)
            && i.value.at(0) != 'F')
            return i;
    return pieces.at(0);
}

pPiece &pInterface::getPiece(std::pair<int, int> pos) {
    for (auto &i : pieces)
        if (i.pos == pos && i.value.at(0) != 'F')
            return i;
    return pieces.at(0);
}

void pInterface::handleBulkClick() {
    if (!getPieceRel(screen.mousePointer).show && getPieceRel(screen.mousePointer).value.at(0) == 'N') {
        pPiece *pc = &getPieceRel(screen.mousePointer);
        pc->show = true;
        std::queue<pPiece> q;
        q.push(*pc);
        pc->show = true;
        if (pc->value.at(pc->value.size() - 1) != 'D') pc->value += "_D";
        while (!q.empty()) {
            std::vector<std::pair<int, int>> dir = {
                { q.front().pos.first, q.front().pos.second - gameInfo.pieceSize.second },
                { q.front().pos.first - gameInfo.pieceSize.first, q.front().pos.second },
                { q.front().pos.first, q.front().pos.second + gameInfo.pieceSize.second },
                { q.front().pos.first + gameInfo.pieceSize.first, q.front().pos.second }
            };

            for (auto i : dir) {
                if (i.first >= 0 && i.first < screen.size.first && i.second >= 0 && i.second < screen.size.second) {
                    pc = &getPiece(i);
                    if (!pc->show && pc->value == "NULL" && !pc->flag) {
                        pc->show = true;
                        pc->value += "_D";
                        q.push(*pc);
                    }
                    else if (std::isdigit(pc->value.at(0)) && !pc->flag) {
                        pc->show = true;
                        pc->value += "_D";
                    }
                }
            }
            q.pop();
        }
    }
}

void pInterface::handleMineClick() {
    pPiece pc = getPieceRel(screen.mousePointer);
    if (pc.value.at(0) == 'M')
        for (auto &i : pieces)
            if (i.value.at(0) == 'M' && !i.flag && !i.show)
                i.show = true, i.value += "_D", gameInfo.picatLemnu = true;
    pRender();
}

void pInterface::handleDigitClick() {
    pPiece *pc = &getPieceRel(screen.mousePointer);
    if (std::isdigit(pc->value.at(0)) && !pc->show && !pc->flag) {
        pc->show = true;
        pc->value += "_D";
        pRender();
    }
}

void pInterface::handleFlagPlacementClick() {
    std::pair<int, int> pos = {
        (screen.mousePointer.first / gameInfo.pieceSize.first) * gameInfo.pieceSize.first,
        (screen.mousePointer.second / gameInfo.pieceSize.second) * gameInfo.pieceSize.second
    };
    for (auto &i : pieces)
        if (i.pos == pos)
            i.flag = !i.flag;
    pRender();
}

bool pInterface::isFlagPlaced(std::pair<int, int> pos) {
    pos = {
        (pos.first / gameInfo.pieceSize.first) * gameInfo.pieceSize.first,
        (pos.second / gameInfo.pieceSize.second) * gameInfo.pieceSize.second
    };
    for (auto i : pieces)
        if (i.flag && i.pos == pos)
            return true;
    return false;
}

void pInterface::handleClick(bool rClick) {
    if (!gameInfo.picatLemnu) {
        if (!rClick && !isFlagPlaced(screen.mousePointer)) {
            if (!gameInfo.firstClick) {
                init(true);
                gameInfo.firstClick = true;
            }
            handleBulkClick();
            handleMineClick();
            handleDigitClick();
        }
        if (rClick) handleFlagPlacementClick();
    }
}