#include "Renderer.h"
#include "Camera.h"
#include "Application.h"
#include "Mirror_Camera.h"
#include "Mirror_Cube.h"
#include"MirrorRenderTexture.h"

#include <DirectXMath.h>

using namespace DirectX::SimpleMath;
using namespace DirectX;


//=======================================
//����������
//=======================================
//�����ʒu�͋���
void Mirror_Camera::Init()
{
	m_Position = m_MirrorCube.GetMirrorPosition();
	m_Target = Vector3(0.0f, 0.0f, 0.0f);
}


//=======================================
//�X�V����
//=======================================
void Mirror_Camera::Update()
{

	//���C���̃J�����̃^�[�Q�b�g���擾
	Vector3 MainCameraViewDirection = m_MainCamera.GetTargetVector();

	Vector3 MirrorRotation = m_MirrorCube.GetMirrorRotation();

	//���C���J�����̃^�[�Q�b�g�����̖@���ɔ��˂�����
	Matrix rotationMatrix = Matrix::CreateFromYawPitchRoll(MirrorRotation.y, MirrorRotation.x, MirrorRotation.z);

	// ���݂̋��̍��ʂ̖@�����v�Z
	Vector3 leftFaceNormal = Vector3::TransformNormal(Vector3(-1, 0, 0), rotationMatrix);  // ���ʂ̖@���� (-1, 0, 0)

	// ���˃x�N�g�����v�Z
	float dotProduct = MainCameraViewDirection.Dot(leftFaceNormal);//���C���J�����̎����x�N�g���Ƌ��̖@���̓��ς��v�Z�B���ρ�
	Vector3 reflection;
	//Vector3 reflection = MainCameraViewDirection + 2.0f * dotProduct * leftFaceNormal;

	//Matrix cameraNormaMatrix = Matrix::CreateLookAt(Vector3::Zero, MainCameraViewDirection, Vector3::Up);
	//Matrix mirrorInvertNormalMatrix = Matrix::CreateLookAt(Vector3::Zero, -leftFaceNormal, Vector3::Up);;
	//Matrix diffMatrix = (mirrorInvertNormalMatrix * cameraNormaMatrix.Invert()).Invert();
	//Vector3 reflection = Vector3::Transform(MainCameraViewDirection, diffMatrix);
	//reflection = Vector3::Transform(reflection, diffMatrix);

	//��]�s����쐬
	Matrix mirrorRotationMatrix = Matrix::CreateFromYawPitchRoll(MirrorRotation.y, MirrorRotation.x, MirrorRotation.z);

	//���˃x�N�g�����v�Z
	reflection = MainCameraViewDirection;
	reflection = Vector3::Transform(reflection, mirrorRotationMatrix);
	reflection = Vector3::Transform(reflection, mirrorRotationMatrix);
	//reflection *= -1.0f;

	//���_�x�N�g���𔽎˃x�N�g���ɕύX
	m_Target = reflection + m_Position;


	////���C���̃J�����̈ʒu���擾
	//Vector3 MainCameraPos = m_MainCamera.GetPosition();

	////���̈ʒu�擾�Ɩ@���x�N�g��
	//Vector3 MirrorPos = m_.GetMirrorPosition();
	//Vector3 MirrorNormal = Vector3(-1.0f, 0.0f, 0.0f);//���˖ʂ�ς���ꍇ�͂�����ύX

	////���C���J�����̈ʒu�Ƌ��̈ʒu�̃x�N�g��
	//Vector3 CameraToMirror = MirrorPos - MainCameraPos;

	////CameraToMirror�𐳋K��
	//CameraToMirror.Normalize();

	////���˃x�N�g�����v�Z
	//Vector3 ReflectedVector = XMVector3Reflect(CameraToMirror, MirrorNormal);

	////�^�[�Q�b�g���X�V
	//m_Target = MirrorPos + ReflectedVector;

}

//=======================================
//�`�揈��
//=======================================
void Mirror_Camera::Draw() {

	// �r���[�ϊ����쐬
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up); // ����n�ɂ����@20230511 by suzuki.tomoki
	// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
	// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
	// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
	// m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);

	static const float viewHeight = 50.0f;//����̍���
	static const float viewWidth = viewHeight * static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());//����̕�

	//�v���W�F�N�V�����s��̐���
	constexpr float fieldOfView = DirectX::XMConvertToRadians(100.0f);// ����p

	float aspectRatio = static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());	//�A�X�y�N�g��
	float nearPlane = 0.01f;       // �j�A�N���b�v
	float farPlane = 1000.0f;      // �t�@�[�N���b�v

	// �v���W�F�N�V�����s��̐���
	//Matrix MirrorProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);

	// ���s���e�̏ꍇ(�v���_�N�V�����s����쐬)
	Matrix MirrorProjectionMatrix = DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearPlane, farPlane);

	MirrorRenderTexture::MirrorRender(Renderer::GetDeviceContext(), m_ViewMatrix, MirrorProjectionMatrix);

}

DirectX::XMMATRIX Mirror_Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

DirectX::XMMATRIX Mirror_Camera::GetProjectionMatrix(float aspectRatio) const
{
	return m_ProjectionMatrix;
}

//=======================================
//�I������
//=======================================
void Mirror_Camera::Uninit()
{

}