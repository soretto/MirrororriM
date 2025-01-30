#pragma once

#include "VertexBuffer.h"
#include"TestCube.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include"Texture.h"
#include <vector>
#include"MirrorRenderTexture.h"
#include"TestCube.h"

//TestCube�N���X�̎q�I�u�W�F�N�g�̋��̃I�u�W�F�N�g�N���X
class Mirror_Cube : public TestCube
{

public:

	void Init();
	void Update();
	void Draw();
	void Uninit();
	void SetMirrorPosition(DirectX::SimpleMath::Vector3 position);
	DirectX::SimpleMath::Vector3 GetMirrorPosition();
	DirectX::SimpleMath::Vector3 GetMirrorRotation();
	DirectX::SimpleMath::Vector3 GetMirrorScale();
	void RenderMirrorTexture(); // ���̃J�������烌���_�����O

	ID3D11ShaderResourceView* m_srv;

private:

	//ID3D11ShaderResourceView* shaderResourceView;

	// SRT���i�p�����j
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	// �`��ׂ̈̏��i���b�V���Ɋւ����)
	IndexBuffer	 m_IndexBuffer; // �C���f�b�N�X�o�b�t�@
	VertexBuffer<VERTEX_3D>	m_VertexBuffer; // ���_�o�b�t�@

	// �`��ׂ̈̏��i�����ڂɊւ�镔���j
	Shader m_Shader; // �V�F�[�_�[


};
