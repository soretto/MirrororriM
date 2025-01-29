#pragma once

#include	<d3d11.h>
#include	<DirectXMath.h>
#include	<SimpleMath.h>
#include	<io.h>
#include	<string>
#include	<vector>
#include"MirrorRenderTexture.h"

//�O�����C�u����
#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"d3d11.lib")

// �R�c���_�f�[�^
struct VERTEX_3D
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 normal;
	DirectX::SimpleMath::Color color;
	DirectX::SimpleMath::Vector2 uv;
};

// �u�����h�X�e�[�g
enum EBlendState {
	BS_NONE = 0,							// ��������������
	BS_ALPHABLEND,							// ����������
	BS_ADDITIVE,							// ���Z����
	BS_SUBTRACTION,							// ���Z����
	MAX_BLENDSTATE
};

//���s����
struct LIGHT
{
	BOOL Enable;//�L�������̃t���O
	BOOL Dummy[3];//�A���C�������g�̓s���Ń_�~�[
	DirectX::SimpleMath::Vector4 Direction;//���̕���
	DirectX::SimpleMath::Color   Diffuse;//�����ƐF
	DirectX::SimpleMath::Color   Ambient;//�����̋����ƐF
};

//���b�V��
struct SUBSET
{
	std::string MtrlName;//�}�e���A����
	unsigned int IndexNum = 0;//�C���f�b�N�X��
	unsigned int VertexNum = 0;//���_��
	unsigned int IndexBase = 0;//�J�n�C���f�b�N�X
	unsigned int VertexBase = 0;//�J�n���_
	unsigned int MaterialIdx = 0;//�}�e���A���C���f�b�N�X

};


//�}�e���A��
struct MATERIAL
{
	DirectX::SimpleMath::Color Ambient;//�����̋����ƐF
	DirectX::SimpleMath::Color Diffuse;//�g�U���̋����ƐF
	DirectX::SimpleMath::Color Specular;//���ʌ��̋����ƐF
	DirectX::SimpleMath::Color Emission;//����

	float Shiness;//����x
	BOOL TextureEnable;//�e�N�X�`���̗L��
	BOOL Dummy[2];//�A���C�������g�̓s���Ń_�~�[
};

//-----------------------------------------------------------------------------
//Renderer�N���X
//-----------------------------------------------------------------------------
class Renderer
{
private:

	static D3D_FEATURE_LEVEL       m_FeatureLevel;//Direct3D�̋@�\���x��

	static ID3D11Device* m_Device;//Direct3D�f�o�C�X
	static ID3D11DeviceContext* m_DeviceContext;//DeviceContext
	static IDXGISwapChain* m_SwapChain;//�X���b�v�`�F�[��
	static ID3D11RenderTargetView* m_RenderTargetView;//�����_�[�^�[�Q�b�g�r���[

	static ID3D11DepthStencilView* m_DepthStencilView;//�[�x�X�e���V���r���[

	static ID3D11Buffer* m_WorldBuffer;//���[���h�s��
	static ID3D11Buffer* m_ViewBuffer;//�r���[�s��
	static ID3D11Buffer* m_ProjectionBuffer;//�v���W�F�N�V�����s��

	static ID3D11Buffer* m_LightBuffer;//���C�g���
	static ID3D11Buffer* m_MaterialBuffer;

	static ID3D11DepthStencilState* m_DepthStateEnable;//�[�x�X�e���V���X�e�[�g
	static ID3D11DepthStencilState* m_DepthStateDisable;//�[�x�X�e���V���X�e�[�g

	static ID3D11BlendState* m_BlendState[MAX_BLENDSTATE]; // �u�����h �X�e�[�g;
	static ID3D11BlendState* m_BlendStateATC;

public:

	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);

	static void SetATCEnable(bool Enable);

	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(DirectX::SimpleMath::Matrix* WorldMatrix);
	static void SetViewMatrix(DirectX::SimpleMath::Matrix* ViewMatrix);
	static void SetProjectionMatrix(DirectX::SimpleMath::Matrix* ProjectionMatrix);

	static ID3D11Device* GetDevice(void) { return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext(void) { return m_DeviceContext; }
	static ID3D11RenderTargetView* GetRenderTargetView(void);
	static ID3D11DepthStencilView* GetDepthStencilView(void) { return m_DepthStencilView; }

	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);


	static void SetLight(LIGHT Light);
	static void SetMaterial(MATERIAL Material);
	//=============================================================================
	// �u�����h �X�e�[�g�ݒ�
	//=============================================================================
	static void SetBlendState(int nBlendState)
	{
		if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE) {
			float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			m_DeviceContext->OMSetBlendState(m_BlendState[nBlendState], blendFactor, 0xffffffff);
		}
	}
};