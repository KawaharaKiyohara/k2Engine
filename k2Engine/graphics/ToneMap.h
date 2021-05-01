#pragma once
class ToneMap
{
public:
	ToneMap();
	~ToneMap();
	/// <summary>
   /// �`��B
   /// </summary>
   /// <param name="rc">�����_�\�R���e�L�X�g�B</param>
   /// <param name="mainRenderTarget">���C�������_�\�^�[�Q�b�g�B</param>
	void Render(RenderContext& rc, RenderTarget& mainRenderTarget);
	/// <summary>
	/// �������B
	/// </summary>
	void Init(RenderTarget& mainRenderTarget);
private:
	struct TonemapBuffer {
		float scaler = 35.0f;
		float gammaCorrection = 2.2f;
	};

	std::vector<std::unique_ptr<RenderTarget>> m_renderTargetVector;		//���ϋP�x�����߂邽�߂̃����_�\�^�[�Q�b�g�B
	std::vector<std::unique_ptr<Sprite>> m_spriteVector;
	Sprite m_finalSprite;
	TonemapBuffer m_tonemapBuffer;
};

