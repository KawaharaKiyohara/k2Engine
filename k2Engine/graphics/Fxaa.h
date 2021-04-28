#pragma once
/// <summary>
/// FXAA�B
/// </summary>
class Fxaa
{
public:
    /// <summary>
    /// �������B
    /// </summary>
    /// <param name="mainRenderTarget">���C�������_�[�^�[�Q�b�g�B</param>
    void Init(RenderTarget& mainRenderTarget);
    /// <summary>
    /// �`��B
    /// </summary>
    /// <param name="rc">�����_�\�R���e�L�X�g�B</param>
    /// <param name="mainRenderTarget">���C�������_�\�^�[�Q�b�g�B</param>
    void Render(RenderContext& rc, RenderTarget& mainRenderTarget);
private:

    struct ConstantBuffer
    {
        float bufferW;
        float bufferH;
    }; 

    Sprite m_finalSprite;					//�ŏI�����p�̃X�v���C�g
    ConstantBuffer m_cB;
};