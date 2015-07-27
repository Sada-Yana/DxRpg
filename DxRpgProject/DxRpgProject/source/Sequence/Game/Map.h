#pragma once
#include "StdCommon.h"
#include "Sequence/Game/Child.h"

class ResourceLoader;
namespace Map
{

class CsvMapReader;
class AbstractMapCharacter;

}
// �萔�֘A�̏��
namespace Sequence
{

class Parent;
namespace Game
{

const int   SlidePicVal = 16;            // �L�����c�`��ʒu���炵��
const int   MapNum = 2;
const char  MapFile[MapNum][MAX_PATH + 1] =
{
    "csv/map/20x16/0.txt",
    "csv/map/20x16/1.txt"
};

// ���[���h�}�b�v����̃N���X
class Map : public Sequence::Game::Child
{
public:
    enum NextSequence
    {
        NextMap,
        NextBattle,
    };
    Map(Sequence::Game::Parent *parent, int stage);
    ~Map();
    void update(Sequence::Game::Parent *parent) override;

private:
    Parent *parent_;
    ResourceLoader *rl_;
    ::Map::CsvMapReader  *cmr_;
    int    isPassable_[YBlock * XBlock];    // �ʍs�\���ǂ����̏��(�d�v�I)
    int    mapStage_;
    bool   hasChanged_;
    NextSequence nextSequence_;

    //void    createInstance();
    void    initMapState();
    void    initCharState();
    void    drawMap();
    void    moveCharacter();
    void    changeMap();
    void    drawCharacter();
};

}

}