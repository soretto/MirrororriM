#include	"TestPlane.h"

using namespace DirectX::SimpleMath;

//=======================================
//����������
//=======================================
void TestPlane::Init()
{
	// ���_�f�[�^
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(4);

	vertices[0].position = Vector3(-10,  0,  10);
	vertices[1].position = Vector3( 10,  0,  10);
	vertices[2].position = Vector3(-10,  0, -10);
	vertices[3].position = Vector3( 10,  0, -10);

	vertices[0].color = Color(1, 1, 1, 1);
	vertices[1].color = Color(1, 1, 1, 1);
	vertices[2].color = Color(1, 1, 1, 1);
	vertices[3].color = Color(1, 1, 1, 1);

	vertices[0].uv = Vector2(0, 0);
	vertices[1].uv = Vector2(1, 0);
	vertices[2].uv = Vector2(0, 1);
	vertices[3].uv = Vector2(1, 1);

	// ���_�o�b�t�@����
	m_VertexBuffer.Create(vertices);

	// �C���f�b�N�X�o�b�t�@����
	std::vector<unsigned int> indices;
	indices.resize(4);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// �C���f�b�N�X�o�b�t�@����
	m_IndexBuffer.Create(indices);

	// �V�F�[�_�I�u�W�F�N�g����
	m_Shader.Create("shader/unlitTextureVS.hlsl","shader/unlitTexturePS.hlsl");

	// �e�N�X�`�����[�h
	bool sts= m_Texture.Load("assets/texture/field.jpg");
	assert(sts==true);
	if (sts == false) {
		MessageBox(nullptr, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "�G���[", MB_OK);
	}

}


//=======================================
//�X�V����
//=======================================
void TestPlane::Update()
{
	m_Position.y = -20;
	m_Scale.x = 3;
	m_Scale.z = 3;


}

//=======================================
//�`�揈��
//=======================================
void TestPlane::Draw()
{
	// SRT���쐬
	Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);

	Matrix worldmtx;
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPU�ɃZ�b�g

	// �`��̏���
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();

	// �g�|���W�[���Z�b�g�i�v���~�e�B�u�^�C�v�j
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	m_Texture.SetGPU();

	devicecontext->DrawIndexed(
		4,							// �`�悷��C���f�b�N�X���i�l�p�`�Ȃ�łS�j
		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0);
}

//=======================================
//�I������
//=======================================
void TestPlane::Uninit()
{

}