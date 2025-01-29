#include "Renderer.h"
#include "Camera.h"
#include "Application.h"
#include "input.h"

using namespace DirectX::SimpleMath;

//=======================================
//����������
//=======================================
void Camera::Init()
{
	m_Position = Vector3(-50.0f, 20.0f, -80.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);
}

//=======================================
//�X�V����
//=======================================
void Camera::Update()
{
	////if (Input::GetKeyPress('W'))
	//if (GetAsyncKeyState('W') & 0x8000)
	//{
	//	m_Position.x += 1.0f;
	//	//MirrorMoveFg = true;
	//}
	////if (Input::GetKeyPress('S'))
	//if (GetAsyncKeyState('S') & 0x8000)
	//{
	//	m_Position.x -= 1.0f;
	//	//MirrorMoveFg = true;
	//}
	////if (Input::GetKeyPress('A'))
	//if (GetAsyncKeyState('A') & 0x8000)
	//{
	//	m_Position.z += 1.0f;
	//	//MirrorMoveFg = true;
	//}
	////if (Input::GetKeyPress('D'))
	//if (GetAsyncKeyState('D') & 0x8000)
	//{
	//	m_Position.z -= 1.0f;
	//	//MirrorMoveFg = true;
	//}
	//SetPosition(m_Position);
}

//=======================================
//�`�揈��
//=======================================
void Camera::Draw()
{
	// �r���[�ϊ����쐬
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up); // ����n�ɂ����@20230511 by suzuki.tomoki
	// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
	// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
	// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
	// m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	static const float viewHeight = 130.0f;//����̍���
	static const float viewWidth = viewHeight * static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());//����̕�

	//�v���W�F�N�V�����s��̐���
	constexpr float fieldOfView = DirectX::XMConvertToRadians(100.0f);// ����p

	float aspectRatio = static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());	//�A�X�y�N�g��
	float nearPlane = 1.0f;       // �j�A�N���b�v
	float farPlane = 1000.0f;      // �t�@�[�N���b�v

	//�������e�̏ꍇ(�v���_�N�V�����s����쐬)
	//m_ProjectionMatrix =  DirectX::XMMatrixPerspectiveFovLH( fieldOfView,  aspectRatio,  nearPlane,  farPlane);	//����n�ɂ����@20230511 by suzuki.tomoki

	// ���s���e�̏ꍇ(�v���_�N�V�����s����쐬)
	m_ProjectionMatrix = DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearPlane, farPlane);

	// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
	// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
	// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
	// projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);//�v���W�F�N�V�����s��̐ݒ�
}


//=======================================
//�I������
//=======================================
void Camera::Uninit(){}

//=======================================
//�J�����̈ʒu��ݒ�
//=======================================
void Camera::SetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	m_Position = pos;
}

//=======================================
//�J�����̈ʒu���擾
//=======================================
DirectX::SimpleMath::Vector3 Camera::GetPosition()const
{
	return m_Position;
}

//=======================================
//�����x�N�g�����擾
//=======================================
DirectX::SimpleMath::Vector3 Camera::GetTargetVector()const
{
	//Vector3 viewDirection = m_Target - m_Position;
	//viewDirection.Normalize();
	//return viewDirection;

	Vector3 viewDirection = m_MirrorCube.GetMirrorPosition() - m_Position;
	viewDirection.Normalize();
	return viewDirection;
}