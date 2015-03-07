#include "StdCommon.h"
#include "GameController.h"
#include "ResourceLoader.h"
#include "Sequence/Parent.h"

// ---------------------------------------------------------------
// �G���g���|�C���g
// ---------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); // ���������[�N���o
#endif
    // �^�C�g�����Z�b�g
    DxLib::SetWindowTextA("DX RPG");
    // �E�B���h�E���[�h�ɃZ�b�g���c�w���C�u�����J�n����
    if ( DxLib::ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK
        || DxLib::DxLib_Init() == -1
        || DxLib::SetWindowSizeExtendRate(1.0) == -1 )
    {
        return -1;
    }
    // ����ʕ`��ɂ���
    if ( DxLib::SetDrawScreen(DX_SCREEN_BACK) == -1 )
    {
        return -1;
    }
    // ���[�e�B���e�B�N���X�̃C���X�^���X���擾
    ResourceLoader   *rl = ResourceLoader::getInstance();
    GameController   *gc = GameController::getInstance();
    Sequence::Parent *parent = Sequence::Parent::getInstance();
    // �C���X�^���X
    if ( rl->load() == -1 )            // �摜�Ǎ���
    {
        return -1;
    }
    
    // ���b�Z�[�W���[�v
    while( DxLib::ProcessMessage()    == 0
        && DxLib::ClearDrawScreen() == 0
        && gc->getAllKeyPressed()    == 0
        && gc->getKey(KEY_INPUT_ESCAPE)    == 0 )
    {
        gc->adjustKeyState(); // �L�[�̓��̓X�s�[�h����(Map�ȊO)

        parent->update();

        gc->controlFps();        // FPS����iFPS��60���炢�ɕۂ��߂̊֐��j
#ifdef _DEBUG
        gc->calcFps();           // ���݂�FPS���v�Z
#endif
        gc->increaseGCount();    // �����J�E���^��1����
        gc->graphFps();
        DxLib::ScreenFlip();     // ����ʂ𔽉f
    }
    // �c�w���C�u�����I������
    DxLib::DxLib_End();
    
    return 0;
}
