#pragma once
#include	<Windows.h>
#include	<directxmath.h>
#include	<d3d11.h>
#include	<wrl/client.h>
#include	"dx11helper.h"
#include	"renderer.h"

class Material {

	struct ConstantBufferMaterial {
		MATERIAL	Material;
	};

	MATERIAL	m_Material{};
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBufferMaterial;

public:
	Material() {}
	Material(MATERIAL mtrl) {
		Create(mtrl);
	}
	~Material() {
		Uninit();
	}

	bool Create(MATERIAL mtrl) {

		ID3D11Device* dev;
		dev = Renderer::GetDevice();

		// �R���X�^���g�o�b�t�@�쐬
		bool sts = CreateConstantBuffer(
			dev,								// �f�o�C�X
			sizeof(ConstantBufferMaterial),		// �T�C�Y
			m_pConstantBufferMaterial.GetAddressOf());		// �R���X�^���g�o�b�t�@�S
		if (!sts) {
			MessageBox(NULL, "CreateBuffer(constant buffer Material) error", "Error", MB_OK);
			return false;
		}

		m_Material.Ambient = mtrl.Ambient;
		m_Material.Diffuse = mtrl.Diffuse;
		m_Material.Specular = mtrl.Specular;
		m_Material.Emission = mtrl.Emission;
		m_Material.Shiness = mtrl.Shiness;
		m_Material.TextureEnable = mtrl.TextureEnable;

		Update();

		return true;
	}

	void Update() {
		ConstantBufferMaterial		cb{};

		cb.Material = m_Material;

		ID3D11DeviceContext* devcontext;
		devcontext = Renderer::GetDeviceContext();

		devcontext->UpdateSubresource(
			m_pConstantBufferMaterial.Get(),
			0,
			nullptr,
			&cb,
			0, 0);

		// �R���X�^���g�o�b�t�@4����4���W�X�^�փZ�b�g�i���_�V�F�[�_�[�p�j
		devcontext->VSSetConstantBuffers(4, 1, m_pConstantBufferMaterial.GetAddressOf());

		// �R���X�^���g�o�b�t�@4����4���W�X�^�փZ�b�g(�s�N�Z���V�F�[�_�[�p)
		devcontext->PSSetConstantBuffers(4, 1, m_pConstantBufferMaterial.GetAddressOf());

	}

	void SetGPU() {

		ID3D11DeviceContext* devcontext;
		devcontext = Renderer::GetDeviceContext();

		// �R���X�^���g�o�b�t�@4����4���W�X�^�փZ�b�g�i���_�V�F�[�_�[�p�j
		devcontext->VSSetConstantBuffers(4, 1, m_pConstantBufferMaterial.GetAddressOf());

		// �R���X�^���g�o�b�t�@4����4���W�X�^�փZ�b�g(�s�N�Z���V�F�[�_�[�p)
		devcontext->PSSetConstantBuffers(4, 1, m_pConstantBufferMaterial.GetAddressOf());
	}

	void SetMaterial(const MATERIAL& mtrl) {
		ConstantBufferMaterial		cb{};

		cb.Material = mtrl;

		ID3D11DeviceContext* devcontext;
		devcontext = Renderer::GetDeviceContext();

		devcontext->UpdateSubresource(
			m_pConstantBufferMaterial.Get(),
			0,
			nullptr,
			&cb,
			0, 0);

		// �R���X�^���g�o�b�t�@4����4���W�X�^�փZ�b�g�i���_�V�F�[�_�[�p�j
		devcontext->VSSetConstantBuffers(4, 1, m_pConstantBufferMaterial.GetAddressOf());

		// �R���X�^���g�o�b�t�@4����4���W�X�^�փZ�b�g(�s�N�Z���V�F�[�_�[�p)
		devcontext->PSSetConstantBuffers(4, 1, m_pConstantBufferMaterial.GetAddressOf());

	}

	void Uninit() {
	}

	void SetDiffuse(DirectX::XMFLOAT4 diffuse) {
		//m_Material.Diffuse = diffuse;
	}

	void SetAmbient(DirectX::XMFLOAT4 ambient) {
		//m_Material.Ambient = ambient;
	}

	void SetSpecular(DirectX::XMFLOAT4 specular) {
		//m_Material.Specular = specular;
	}

	void SetEmission(DirectX::XMFLOAT4 emission) {
		//m_Material.Emission = emission;
	}

	void SetShiness(float shiness) {
		//m_Material.Shiness = shiness;
	}

	bool isTextureEnable() {
		return m_Material.TextureEnable == TRUE;
	}
};