#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Mesh.h"

class MeshRenderer {
protected:
	VertexBuffer<VERTEX_3D>	m_VertexBuffer;		// ���_�o�b�t�@
	IndexBuffer				m_IndexBuffer;		// �C���f�b�N�X�o�b�t�@
	int						m_IndexNum = 0;		// �C���f�b�N�X��
public:
	virtual void Init(Mesh& mesh) 
	{
		m_VertexBuffer.Create(mesh.GetVertices());
		m_IndexBuffer.Create(mesh.GetIndices());
		m_IndexNum = static_cast<int>(mesh.GetIndices().size());
	}

	// �`��O����
	virtual void BeforeDraw()
	{
		ID3D11DeviceContext* devicecontext = Renderer::GetDeviceContext();

		// �g�|���W�[���Z�b�g�i���v���~�e�B�u�^�C�v�j
		devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_VertexBuffer.SetGPU();			// ���_�o�b�t�@���Z�b�g
		m_IndexBuffer.SetGPU();				// �C���f�b�N�X�o�b�t�@���Z�b�g
	}

	// �T�u�Z�b�g�`��
	virtual void DrawSubset(unsigned int indexnum,unsigned int baseindex,unsigned int basevertexindex ) 
	{
		Renderer::GetDeviceContext()->DrawIndexed(
			indexnum,								// �`�悷��C���f�b�N�X���i�ʐ��~�R�j
			baseindex,								// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
			basevertexindex);						// ���_�o�b�t�@�̍ŏ�����g��
	}

	// �`��
	virtual void Draw() 
	{
		BeforeDraw();								// �`��O����

		Renderer::GetDeviceContext()->DrawIndexed(
			m_IndexNum,								// �`�悷��C���f�b�N�X���i�ʐ��~�R�j
			0,										// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
			0);										// ���_�o�b�t�@�̍ŏ�����g��
	}
};
