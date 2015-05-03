#include "GameController.h"
#include "StdCommon.h"

GameController *GameController::getInstance()
{
    static GameController instance;    // �B��̃C���X�^���X
    return &instance;
}

// FPS�v���֐�
void GameController::calcFps()
{
    fps_[gCount_ % MetricTimes] = waitTime_;               // �P���̎��Ԃ��i�[
    if ( (gCount_ % MetricTimes) == (MetricTimes - 1) )    // �v���񐔂ɒB������
    {
        fpsAverage_ = 0;
        for ( int i = 0; i < MetricTimes; i++ )
        {
            fpsAverage_ += fps_[i];
        }
        fpsAverage_ /= MetricTimes;
    }
}

// FPS�\��
void GameController::graphFps()
{
    if ( fpsAverage_ != 0 )    // 0����֎~�ɂ��AFPS���ς�0����Ȃ�������FPS�\��
    {
        DxLib::DrawFormatString(0, 0, DxLib::GetColor(255, 255, 255),
            "FPS %.1f", 1000.0 / (double)(fpsAverage_) );
    }
}

// FPS����
void GameController::controlFps()
{
    waitTime_ = DxLib::GetNowCount() - prevTime_;    //�P���̏����ɂ����������Ԃ��v�Z
    if ( prevTime_ == 0 )
    {                                            // t == 0 �܂��ԍŏ��ɏ������s��ꂽ�Ƃ���16����
        waitTime_ = OneFrameMSec;    
    }
    prevTime_ = DxLib::GetNowCount();            // ���݂̎������i�[
    if ( OneFrameMSec > waitTime_ )              // �P�������������Ԃ�FPS60�܂�P��16ms���������s��ꂽ�Ƃ�
    {
        Sleep(OneFrameMSec - waitTime_);         // FPS60�ɂȂ�悤�ɁA�܂�P��16ms�܂ő҂B
    }
}

char GameController::getKey(int input) const
{
    return key_[input];
}

int GameController::getAllKeyPressed()
{
    return DxLib::GetHitKeyStateAll( key_ );
}

void GameController::increaseGCount()
{
    gCount_++;                                
    if (gCount_ >= GCountMax)
    {
        gCount_ = 0;
    }
}

int GameController::getGCount() const
{
    return gCount_;
}

// �}�b�v��ʂ̈ړ��ȊO�ŁA�ړ����x�������Ȃ肷����̂�h�����߂̋@�\
// ���C�����[�v�̍ŏ��ɕK�������Ȃ���΂Ȃ�Ȃ�
void GameController::adjustKeyState()
{
    for (int i = 0; i < KeyKindNum; i++)
    {
        // �O�ɉ����ĂȂ��āA�������Ă�����
        if (prevKey_[i] == NotPressed && key_[i] == Pressed)
        {
            key_[i] = PressedNow;     // ���̏u�ԉ����ꂽ�Ƃ����Ӗ���2�����B
        }
        prevKey_[i] = key_[i];        // ���̓��͏�Ԃ��ߋ��ɓ��͂��ꂽ�f�[�^�Ƃ��ăR�s�[
    }
}

// �ʏ�̓��C�����[�v�̒��ł��ꂾ�����Ăׂ΂悢
void GameController::control()
{
    controlFps();        // FPS����iFPS��60���炢�ɕۂ��߂̊֐��j
#ifdef _DEBUG
    calcFps();           // ���݂�FPS���v�Z
    graphFps();
#endif
    increaseGCount();    // �����J�E���^��1����
}