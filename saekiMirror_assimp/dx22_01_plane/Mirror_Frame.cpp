#include "Mirror_Frame.h"
#include	<memory>
#include	"StaticMesh.h"
#include "input.h"

// �f�o�b�N�p
#include <iostream>



using namespace DirectX::SimpleMath;


//�R���X�g���N�^
//MirrorFrame::MirrorFrame(Camera* cam) : Object(cam)
MirrorFrame::MirrorFrame()
{

}



//�f�X�g���N�^
MirrorFrame::~MirrorFrame()
{

}



void MirrorFrame::Init()
{
	// ���b�V���ǂݍ���
	StaticMesh staticmesh;

	//3D���f���f�[�^
	//std::u8string modelFile = u8"assets/model/MirrorFrame/mirror.obj";
	std::u8string modelFile = u8"assets/model/Stages/stage02.obj";


	//�e�N�X�`���f�B���N�g��
	//std::string texDirectory = "assets/model/MirrorFrame";
	std::string texDirectory = "assets/model/Stages";


	//Mesh��ǂݍ���
	std::string tmpStr1(reinterpret_cast<const char*>(modelFile.c_str()), modelFile.size());
	staticmesh.Load(tmpStr1, texDirectory);

	m_MeshRenderer.Init(staticmesh);

	// �V�F�[�_�I�u�W�F�N�g����
	m_Shader.Create("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");

	// �T�u�Z�b�g���擾
	m_subsets = staticmesh.GetSubsets();

	// �e�N�X�`�����擾
	m_Textures = staticmesh.GetTextures();

	// �}�e���A�����
	std::vector<MATERIAL> materials = staticmesh.GetMaterials();

	// �}�e���A���������[�v
	for (int i = 0; i < materials.size(); i++)
	{
		// �}�e���A���I�u�W�F�N�g����
		std::unique_ptr<Material> m = std::make_unique<Material>();

		// �}�e���A�������Z�b�g
		m->Create(materials[i]);

		// �}�e���A���I�u�W�F�N�g��z��ɒǉ�
		m_Materiales.push_back(std::move(m));
	}

	//�ʒu
	m_Position.z -= 40.0f;
	m_Position.y -= 20.0f;

	//��]
	m_Rotation.y = 4.9f;

	m_Scale.x = 5.0f;
	m_Scale.y = 5.0f;
	m_Scale.z = 5.0f;

}

void MirrorFrame::Update()
{
	std::stringstream log{};

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		if (move_flg == false)
		{
			move_flg = true;
		}
		else
		{
			move_flg = false;
		}
	}
	if (move_flg == true)
	{
		if (Input::GetKeyPress('W'))
		{
			m_Position.x += 5.0f;
		}
		if (Input::GetKeyPress('S'))
		{
			m_Position.x -= 5.0f;
		}
		if (Input::GetKeyPress('A'))
		{
			m_Position.z += 5.0f;

		}
		if (Input::GetKeyPress('D'))
		{
			m_Position.z -= 5.0f;

		}
	}
	log << "MirrorFrame: " << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << '\n';
	OutputDebugStringA(log.str().c_str());
}


void MirrorFrame::Draw()
{
	
	// SRT���쐬
		Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
		Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
		Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);

		Matrix worldmtx;
		worldmtx = s * r * t;
		Renderer::SetWorldMatrix(&worldmtx); // GPU�ɃZ�b�g

		m_Shader.SetGPU();

		// �C���f�b�N�X�o�b�t�@�E���_�o�b�t�@���Z�b�g
		m_MeshRenderer.BeforeDraw();

		//�}�e���A���������[�v
		for (int i = 0; i < m_subsets.size(); i++)
		{
			// �}�e���A�����Z�b�g�i�T�u�Z�b�g���̒��ɂ���}�e���A���C���f�b�N�X���g�p�j
			m_Materiales[m_subsets[i].MaterialIdx]->SetGPU();

			if (m_Materiales[m_subsets[i].MaterialIdx]->isTextureEnable())
			{
				m_Textures[m_subsets[i].MaterialIdx]->SetGPU();
			}


			m_MeshRenderer.DrawSubset(
				m_subsets[i].IndexNum,    // �`�悷��C���f�b�N�X��
				m_subsets[i].IndexBase,   // �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
				m_subsets[i].VertexBase); // ���_�o�b�t�@�̍ŏ�����g�p
		}


	

}

void MirrorFrame::Uninit()
{

}

void MirrorFrame::SetPosition(const Vector3& pos)
{
	m_Position.x = pos.x;
	m_Position.y = pos.y;
	m_Position.z = pos.z;
}

Vector3 MirrorFrame::GetPosition() const
{
	return m_Position;
}

Vector3 MirrorFrame::GetRotation() const
{
	return m_Rotation;
}