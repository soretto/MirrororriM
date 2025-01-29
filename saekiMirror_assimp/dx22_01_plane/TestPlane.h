#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include"Texture.h"

//-----------------------------------------------------------------------------
//TestPlane�N���X
//-----------------------------------------------------------------------------
class TestPlane {
	// SRT���i�p�����j
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	// �`��ׂ̈̏��i���b�V���Ɋւ����j
	IndexBuffer	 m_IndexBuffer; // �C���f�b�N�X�o�b�t�@
	VertexBuffer<VERTEX_3D>	m_VertexBuffer; // ���_�o�b�t�@

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	Shader m_Shader; // �V�F�[�_�[

	Texture m_Texture;//�e�N�X�`��

public:
	void Init();
	void Draw();
	void Update();
	void Uninit();
};