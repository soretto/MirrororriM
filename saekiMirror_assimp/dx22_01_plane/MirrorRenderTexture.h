#pragma once
#include <d3d11.h>
#include	<DirectXMath.h>
#include	<SimpleMath.h>
#include	<io.h>
#include"Renderer.h"

//�O�����C�u����
#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"d3d11.lib")

// ���̃����_�[�e�N�X�`�����Ǘ�����N���X
class MirrorRenderTexture {
public:
    // �R���X�g���N�^�F�e�N�X�`���쐬
    MirrorRenderTexture();
    ~MirrorRenderTexture();

    static void Init(ID3D11Device* device);

    static void MirrorRender(ID3D11DeviceContext* context, 
        const DirectX::SimpleMath::Matrix& view,const DirectX::SimpleMath::Matrix& projection);

    // �����_�[�^�[�Q�b�g�r���[�̎擾
    static ID3D11RenderTargetView* GetRenderTargetView(void);

    // �V�F�[�_�[���\�[�X�r���[�̎擾�i�s�N�Z���V�F�[�_�[�p�j
    static ID3D11ShaderResourceView* GetShaderResourceView(void);

    //�[�x�o�b�t�@�̎擾
    static ID3D11DepthStencilView* GetMirrorDepthStencilView(void);

private:

    static ID3D11Device* MirrorDevice;//Direct3D�f�o�C�X
    static ID3D11Texture2D* MirrorRenderTargetTexture;//�����_�[�e�N�X�`��
    static ID3D11RenderTargetView* MirrorRenderTargetView;
    static ID3D11ShaderResourceView* MirrorShaderResourceView;
    static ID3D11Texture2D* MirrorDepthStencilTexture;//�[�x�X�e���V���o�b�t�@
    static ID3D11DepthStencilView* MirrorDepthStencilView; // �f�v�X�X�e���V���r���[
};
