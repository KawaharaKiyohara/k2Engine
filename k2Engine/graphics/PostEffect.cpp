#include "k2EnginePreCompile.h"
#include "PostEffect.h"

#include "effect/EffectEngine.h"

void PostEffect::Init(RenderTarget& mainRenderTarget, RenderTarget& zprepassRenderTarget)
{
    m_bloom.Init(mainRenderTarget);
    m_dof.Init(mainRenderTarget, zprepassRenderTarget);
    m_fXaa.Init(mainRenderTarget);
    m_tonemap.Init(mainRenderTarget);
}
void PostEffect::Render(RenderContext& rc, RenderTarget& mainRenderTarget)
{   
    m_tonemap.Render(rc, mainRenderTarget);

    //�����ŃG�t�F�N�g�h���[�����B
    EffectEngine::GetInstance()->Draw();

    m_bloom.Render(rc, mainRenderTarget);
    m_dof.Render(rc, mainRenderTarget);
   
    m_fXaa.Render(rc, mainRenderTarget);
}