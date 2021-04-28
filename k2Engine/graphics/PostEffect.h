#pragma once

#include "Bloom.h"
#include "Dof.h"
#include "Fxaa.h"

/// <summary>
/// �|�X�g�G�t�F�N�g�B
/// </summary>
class PostEffect
{
public:
    /// <summary>
    /// �������B
    /// </summary>
    /// <param name="mainRenderTarget">�����_�^�[�Q�b�g�B</param>
    /// <param name="zprepassRenderTarget">z�v���p�X�����_�\�^�[�Q�b�g�B</param>
    void Init(RenderTarget& mainRenderTarget, RenderTarget& zprepassRenderTarget);
    /// <summary>
    /// �`��B
    /// </summary>
    /// <param name="rc">�����_�\�R���e�L�X�g�B</param>
    /// <param name="mainRenderTarget">���C�������_�\�^�[�Q�b�g�B</param>
    void Render(RenderContext& rc, RenderTarget& mainRenderTarget);
private:
    Bloom m_bloom;	//�u���[��
    Dof m_dof;		//��ʊE�[�x
    Fxaa m_fXaa;    //FXAA;
};

