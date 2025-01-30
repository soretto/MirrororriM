#include"Mirror_Cube.h"

using namespace DirectX::SimpleMath;

#define PI 3.14159265358f

Vector3 Mirror_Cube::GetMirrorPosition() 
{
	return m_Position;
}

void Mirror_Cube::RenderMirrorTexture()
{

}

void Mirror_Cube::SetMirrorPosition(Vector3 position) 
{
	m_Position = position;
}

Vector3 Mirror_Cube::GetMirrorRotation()
{
	return m_Rotation;
}

void Mirror_Cube::Init()
{
	// ���_�f�[�^
	std::vector<VERTEX_3D>	vertices;
	vertices.resize(24);

	// ��� (Y��������)
	vertices[0].position = Vector3(-10, 10, 10);  vertices[0].uv = Vector2(0, 0);
	vertices[1].position = Vector3(10, 10, 10);   vertices[1].uv = Vector2(0.33, 0);
	vertices[2].position = Vector3(-10, 10, -10); vertices[2].uv = Vector2(0, 0.5);
	vertices[3].position = Vector3(10, 10, -10);  vertices[3].uv = Vector2(0.33, 0.5);

	vertices[0].normal = Vector3(0, 1, 0);
	vertices[1].normal = Vector3(0, 1, 0);
	vertices[2].normal = Vector3(0, 1, 0);
	vertices[3].normal = Vector3(0, 1, 0);

	// ���� (Y��������)
	vertices[4].position = Vector3(-10, -10, 10); vertices[4].uv = Vector2(0.66, 0.5);
	vertices[5].position = Vector3(10, -10, 10);   vertices[5].uv = Vector2(1, 0.5);
	vertices[6].position = Vector3(-10, -10, -10); vertices[6].uv = Vector2(0.66, 1);
	vertices[7].position = Vector3(10, -10, -10);  vertices[7].uv = Vector2(1, 1);

	vertices[4].normal = Vector3(0, -1, 0);
	vertices[5].normal = Vector3(0, -1, 0);
	vertices[6].normal = Vector3(0, -1, 0);
	vertices[7].normal = Vector3(0, -1, 0);

	// �O�� (Z��������)
	vertices[8].position = Vector3(-10, 10, 10); vertices[8].uv = Vector2(0.33, 0);
	vertices[9].position = Vector3(10, 10, 10);    vertices[9].uv = Vector2(0.66, 0);
	vertices[10].position = Vector3(-10, -10, 10); vertices[10].uv = Vector2(0.33, 0.5);
	vertices[11].position = Vector3(10, -10, 10); vertices[11].uv = Vector2(0.66, 0.5);

	vertices[8].normal = Vector3(0, 0, 1);
	vertices[9].normal = Vector3(0, 0, 1);
	vertices[10].normal = Vector3(0, 0, 1);
	vertices[11].normal = Vector3(0, 0, 1);

	// �w�� (Z��������)
	vertices[12].position = Vector3(-10, 10, -10); vertices[12].uv = Vector2(0.33, 0.5);
	vertices[13].position = Vector3(10, 10, -10);  vertices[13].uv = Vector2(0.66, 0.5);
	vertices[14].position = Vector3(-10, -10, -10); vertices[14].uv = Vector2(0.33, 1);
	vertices[15].position = Vector3(10, -10, -10); vertices[15].uv = Vector2(0.66, 1);

	vertices[12].normal = Vector3(0, 0, -1);
	vertices[13].normal = Vector3(0, 0, -1);
	vertices[14].normal = Vector3(0, 0, -1);
	vertices[15].normal = Vector3(0, 0, -1);

	// ���� (X��������)
	vertices[16].position = Vector3(-10, 10, 10);  vertices[16].normal = Vector3(-1, 0, 0);
	vertices[17].position = Vector3(-10, 10, -10); vertices[17].normal = Vector3(-1, 0, 0);
	vertices[18].position = Vector3(-10, -10, 10); vertices[18].normal = Vector3(-1, 0, 0);
	vertices[19].position = Vector3(-10, -10, -10); vertices[19].normal = Vector3(-1, 0, 0);

	vertices[16].uv = Vector2(1.0f, 0.0f);
	vertices[17].uv = Vector2(0.0f, 0.0f);
	vertices[18].uv = Vector2(1.0f, 1.0f);
	vertices[19].uv = Vector2(0.0f, 1.0f);

	// �E�� (X��������)
	vertices[20].position = Vector3(10, 10, 10);   vertices[20].normal = Vector3(1, 0, 0);
	vertices[21].position = Vector3(10, 10, -10);  vertices[21].normal = Vector3(1, 0, 0);
	vertices[22].position = Vector3(10, -10, 10);  vertices[22].normal = Vector3(1, 0, 0);
	vertices[23].position = Vector3(10, -10, -10); vertices[23].normal = Vector3(1, 0, 0);

	vertices[20].uv = Vector2(0, 0.5);
	vertices[21].uv = Vector2(0.33, 0.5);
	vertices[22].uv = Vector2(0, 1);
	vertices[23].uv = Vector2(0.33, 1);

	//�S�Ă̒��_�̐F�𔒂ɂ���
	for (int i = 0; i < 24; ++i)
	{
		vertices[i].color = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//������
	m_Scale = Vector3(0.3f, 5.0f, 3.0f);

	// ���_�o�b�t�@����
	m_VertexBuffer.Create(vertices);

	// �C���f�b�N�X�o�b�t�@����
	std::vector<unsigned int> indices;
	indices.resize(36);

	indices = {

		// ���
		0, 1, 2,
		1, 3, 2,
		// ����
		4, 5, 6,
		5, 7, 6,
		// �O��
		8, 9, 10,
		9, 11, 10,
		// �w��
		12, 14, 13,
		13, 14, 15,
		// ����
		16, 17, 18,
		17, 19, 18,
		// �E��
		20, 22, 21,
		21, 22, 23

	};

	// �C���f�b�N�X�o�b�t�@����
	m_IndexBuffer.Create(indices);

	// �V�F�[�_�I�u�W�F�N�g����
	m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");

	//�����X����
	//m_Rotation = Vector3(0.0f / 180.0f * PI, -30.0f / 180.0f * PI, 0.0f / 180.0f * PI);
	m_Rotation = Vector3(0.0f / 180.0f * PI, 0.0f / 180.0f * PI, 0.0f / 180.0f * PI);

	//������Ə��
	m_Position.y = 10.0f;
	
}

void Mirror_Cube::Draw()
{
	// SRT���쐬
	Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);//��]
	Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);//���s�ړ�
	Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);//�g��k��

	Matrix worldmtx;//���[���h�s��
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPU�ɃZ�b�g

	// �`��̏���
	ID3D11DeviceContext* Mirrordevicecontext = Renderer::GetDeviceContext();

	// �g�|���W�[���Z�b�g�i�v���~�e�B�u�^�C�v�j
	Mirrordevicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	//�V�F�[�_�[���\�[�X�r���[(�s�N�Z���V�F�[�_���e�N�X�`����ǂނ��߂̂���)���Z�b�g
	Mirrordevicecontext->PSSetShaderResources(0, 1, &m_srv);

	Mirrordevicecontext->DrawIndexed(
		36,							// �`�悷��C���f�b�N�X���i�l�p�`�Ȃ�łS�j
		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0);							// ���_�o�b�t�@�̍ŏ��̒��_�ʒu
}

void Mirror_Cube::Update() {


	if (GetAsyncKeyState('R') & 0x8000) { m_Rotation.y += 0.01f; }
	if (GetAsyncKeyState('L') & 0x8000) { m_Rotation.y -= 0.01f; }

	//�ړ�
	if (GetAsyncKeyState('W') & 0x8000) { m_Position.z += 1.0f; }
	if (GetAsyncKeyState('S') & 0x8000) { m_Position.z -= 1.0f; }
	if (GetAsyncKeyState('A') & 0x8000) { m_Position.x -= 1.0f; }
	if (GetAsyncKeyState('D') & 0x8000) { m_Position.x += 1.0f; }
	if (GetAsyncKeyState('Q') & 0x8000) { m_Position.y += 1.0f; }
	if (GetAsyncKeyState('E') & 0x8000) { m_Position.y -= 1.0f; }
}

void Mirror_Cube::Uninit()
{
}
