
#include "MirrorRenderTexture.h"
#include <stdexcept>

// MirrorRenderTexture �N���X�� static �����o�ϐ��̎��̂��`
ID3D11Device* MirrorRenderTexture::MirrorDevice{};
ID3D11Texture2D* MirrorRenderTexture::MirrorRenderTargetTexture{};
ID3D11RenderTargetView* MirrorRenderTexture::MirrorRenderTargetView{};
ID3D11ShaderResourceView* MirrorRenderTexture::MirrorShaderResourceView{};
ID3D11Texture2D* MirrorRenderTexture::MirrorDepthStencilTexture{};
ID3D11DepthStencilView* MirrorRenderTexture::MirrorDepthStencilView{};

MirrorRenderTexture::MirrorRenderTexture() {

	// �R���X�g���N�^
	MirrorDevice = nullptr;
	MirrorRenderTargetTexture = nullptr;
	MirrorRenderTargetView = nullptr;
	MirrorShaderResourceView = nullptr;
	MirrorDepthStencilTexture = nullptr;
	MirrorDepthStencilView = nullptr;
}

void MirrorRenderTexture::Init(ID3D11Device* device) {

	if (!device) {
		throw std::invalid_argument("�f�o�C�X����ւ񂪂�");
	}

	// �f�o�C�X�̐ݒ�
	MirrorDevice = device;

	// �e�N�X�`���̐ݒ�
	D3D11_TEXTURE2D_DESC MirrorTextureDesc = {};
	MirrorTextureDesc.Width = 1024;
	MirrorTextureDesc.Height = 1024;
	MirrorTextureDesc.MipLevels = 1;
	MirrorTextureDesc.ArraySize = 1;
	MirrorTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // RGBA�`��
	MirrorTextureDesc.SampleDesc.Count = 1;
	MirrorTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	MirrorTextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	MirrorTextureDesc.CPUAccessFlags = 0;
	MirrorTextureDesc.MiscFlags = 0;

	//�V�F�[�_�[���\�[�X�r���[�̐ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	HRESULT hr;

	// �e�N�X�`���쐬
	hr = MirrorDevice->CreateTexture2D(&MirrorTextureDesc, nullptr, &MirrorRenderTargetTexture);

	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Error CreateTexture2D", "Error", MB_OK);
		return;
	}

	// �����_�[�^�[�Q�b�g�r���[���쐬
	hr = MirrorDevice->CreateRenderTargetView(MirrorRenderTargetTexture, nullptr, &MirrorRenderTargetView);

	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Error CreateRenderTargetView", "Error", MB_OK);
		return;
	}

	// �V�F�[�_�[���\�[�X�r���[�i�s�N�Z���V�F�[�_�[�ł̗��p�j���쐬
	hr = MirrorDevice->CreateShaderResourceView(MirrorRenderTargetTexture, &SRVDesc, &MirrorShaderResourceView);

	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Error CreateShaderResourceView", "Error", MB_OK);
		return;
	}

	// �[�x�o�b�t�@�̐ݒ�
	D3D11_TEXTURE2D_DESC MirrorDepthDesc = MirrorTextureDesc;
	MirrorDepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // �f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g��ݒ�
	MirrorDepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;//�f�v�X�X�e���V���r���[�Ƃ��ăo�C���h

	MirrorDevice->CreateTexture2D(&MirrorDepthDesc, nullptr, &MirrorDepthStencilTexture);

	// �f�v�X�X�e���V���r���[���쐬
	if (MirrorDepthStencilTexture != nullptr)MirrorDevice->CreateDepthStencilView(MirrorDepthStencilTexture, nullptr, &MirrorDepthStencilView);

}

//���p�̃����_�����O
void MirrorRenderTexture::MirrorRender(ID3D11DeviceContext* context,
	const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) {

	// �����_�[�^�[�Q�b�g�r���[�̐ݒ�
	context->OMSetRenderTargets(1, &MirrorRenderTargetView, MirrorDepthStencilView);//�`�挋�ʂ��e�N�X�`���ɂ��鉺����

	// �����_�[�^�[�Q�b�g�N���A
	float ClearColor[4] = { 0.0f, 0.0f, 0.3f, 1.0f };
	context->ClearRenderTargetView(MirrorRenderTargetView, ClearColor);
	context->ClearDepthStencilView(MirrorDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	Renderer::SetViewMatrix((DirectX::SimpleMath::Matrix*)&view);//�r���[�s����Z�b�g

	Renderer::SetProjectionMatrix((DirectX::SimpleMath::Matrix*)&projection);//�v���W�F�N�V�����s����Z�b�g
}



MirrorRenderTexture::~MirrorRenderTexture() {
	// ���������
	if (MirrorRenderTargetTexture) MirrorRenderTargetTexture->Release();
	if (MirrorRenderTargetView) MirrorRenderTargetView->Release();
	if (MirrorShaderResourceView) MirrorShaderResourceView->Release();
}

// �����_�[�^�[�Q�b�g�r���[�̎擾
ID3D11RenderTargetView* MirrorRenderTexture::GetRenderTargetView(void) {
	return MirrorRenderTargetView;
}

// �V�F�[�_�[���\�[�X�r���[�̎擾�i�s�N�Z���V�F�[�_�[�p�j
ID3D11ShaderResourceView* MirrorRenderTexture::GetShaderResourceView(void) {
	return MirrorShaderResourceView;
}

//�[�x�o�b�t�@�̎擾
ID3D11DepthStencilView* MirrorRenderTexture::GetMirrorDepthStencilView(void) {
	return MirrorDepthStencilView;
}