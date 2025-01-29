#pragma once
#include <SimpleMath.h>
#include "MeshRenderer.h"
#include "Shader.h"
#include "Texture.h"
#include "StaticMesh.h"
#include "utility.h"
#include"Material.h"

class TestModel {
private:
	// SRT���i�p�����j
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	MeshRenderer m_MeshRenderer; // ���_�o�b�t�@�E�C���f�b�N�X�o�b�t�@�E�C���f�b�N�X��

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	std::vector<std::unique_ptr<Material>> m_Materiales;
	std::vector<SUBSET> m_subsets;
	Shader m_Shader; // �V�F�[�_�[
	std::vector<std::unique_ptr<Texture>> m_Textures; // �e�N�X�`��

public:
	void Init();
	void Update();
	void Draw();
	void Uninit();
};
