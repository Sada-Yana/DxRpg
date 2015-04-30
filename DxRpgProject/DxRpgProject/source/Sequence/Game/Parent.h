#pragma once
#include "Sequence/Child.h"
#include "Map/AbstractMapCharacter.h"  // �z�񂪂��邩�炱��Ȃ��ƃ_��
#include "SharedCharacterStatus.h"  // �s���S�N���X�^�ւ̃|�C���^�[���Q�Ƃł��Ȃ������Ȃ̂�

namespace Sequence
{
namespace Game
{

class Child;
class Parent
    : public Sequence::Child
{
public:
    typedef Sequence::Parent GrandParent;
    enum NextSequence{
        NextMapMain,
        NextBattle,
        NextRestart,
        NextNone,
    };
    Parent();
    ~Parent();
    void update(GrandParent* grandParent);
    void moveTo(NextSequence);
    ::Map::AbstractMapCharacter *getCharacter(int index);
    //int getMapStage() const;
    void setMapStage(int mapStage);

private:
    NextSequence nextSequence_;
    Game::Child* child_;
    //Map *map_;
    ::Map::AbstractMapCharacter *amc_[MainCharMax + CompCharMax];
    ::SharedCharacterStatus *scs_;
    int  mapStage_;
    void initializeParameter();
};

}
}
