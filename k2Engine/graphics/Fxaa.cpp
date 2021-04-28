#include "k2EnginePreCompile.h"
#include "Fxaa.h"

void Fxaa::Init(RenderTarget& mainRenderTarget)
{
    // �ŏI�����p�̃X�v���C�g������������
    SpriteInitData spriteInitData;
    // �{�P�e�N�X�`����4���w�肷��
    spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
    // �𑜓x��mainRenderTarget�̕��ƍ���
    spriteInitData.m_width = mainRenderTarget.GetWidth();
    spriteInitData.m_height = mainRenderTarget.GetHeight();
    // �ڂ������摜���A�ʏ��2D�Ƃ��ă��C�������_�����O�^�[�Q�b�g�ɕ`�悷��̂ŁA
    // 2D�p�̃V�F�[�_�[���g�p����
    spriteInitData.m_fxFilePath = "Assets/shader/fxaa.fx";
    spriteInitData.m_vsEntryPointFunc = "VSMain";
    spriteInitData.m_psEntryPoinFunc = "PSMain";

    // �������A���Z�����ŕ`�悷��̂ŁA�A���t�@�u�����f�B���O���[�h�����Z�ɂ���
    spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
    spriteInitData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();

    m_finalSprite.Init(spriteInitData);

}

void Fxaa::Render(RenderContext& rc, RenderTarget& mainRenderTarget)
{
    // �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
    rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
    // �����_�����O�^�[�Q�b�g��ݒ�
    rc.SetRenderTargetAndViewport(mainRenderTarget);
    //�`��B
    m_finalSprite.Draw(rc);
    // �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
    rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
}
