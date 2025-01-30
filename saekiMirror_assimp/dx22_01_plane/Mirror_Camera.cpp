#include "Renderer.h"
#include "Camera.h"
#include "Application.h"
#include "Mirror_Camera.h"
#include "Mirror_Cube.h"
#include"MirrorRenderTexture.h"

#include <DirectXMath.h>
#include <cmath> // �O�p�֐����g�����߂ɕK�v

using namespace DirectX::SimpleMath;
using namespace DirectX;

DirectX::SimpleMath::Vector3 Mirror_Camera::m_Position;

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
	float dotProduct = MainCameraViewDirection.Dot(leftFaceNormal);//���C���J�����̎����x�N�g���Ƌ��̖@���̓��ς��v�Z�B
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

	/**/

	auto mirrorToMainCamera = m_MainCamera.GetPosition() - m_MirrorCube.GetMirrorPosition();//�����烁�C���J�����ւ̃x�N�g��
	auto MirorrToCameraDistance = Vector3::Distance(m_MainCamera.GetPosition(), m_MirrorCube.GetMirrorPosition());//�����烁�C���J�����܂ł̋���
	//auto MirorrToCameraDistance = (m_MainCamera.GetPosition() - m_MirrorCube.GetMirrorPosition()).Length();


	float dot = -MainCameraViewDirection.Dot(leftFaceNormal);//���C���J�����̎����x�N�g���Ƌ��̖@���̓��ς��v�Z�BMainCameraViewDirection���K���K�v�H
	float angleRad = acosf(dot);//���ς���p�x�v�Z
	float angleDeg = XMConvertToDegrees(angleRad);//�f�B�O���[�p�x�B�f�o�b�O�p

	Matrix rotMatrix = Matrix::CreateFromYawPitchRoll(angleRad, 0.0f, 0.0f);//��]�s����쐬�B�}�C�i�X������
	Vector3 mirrorToReflectionCamera = Vector3::Transform(-leftFaceNormal, -rotMatrix);//���p�̃J������ݒu����x�N�g�����v�Z /*rotMatrix�Ƀ}�C�i�X����*/
	mirrorToReflectionCamera *= MirorrToCameraDistance;//������ݒ�

	m_Position = m_MirrorCube.GetMirrorPosition() + mirrorToReflectionCamera;//���p�̃J�����̈ʒu��ݒ�
	m_Position.y = m_MainCamera.GetPosition().y;//���������C���J�����Ɠ����ɂ���


	//�ȉ��f�o�b�O�p

	mirrorToReflectionCameraDistance = Vector3::Distance(m_Position, m_MirrorCube.GetMirrorPosition());//�����狾�p�̃J�����܂ł̋���
	auto mirrorToReflectionCameraVector = m_Position - m_MirrorCube.GetMirrorPosition();//�����狾�p�̃J�����܂ł̃x�N�g��




	//Quaternion qt;

	//�l�擾
	//Vector3 diff = m_MainCamera.GetPosition() - m_MirrorCube.GetMirrorPosition();
	//Vector3 MirrorScale = m_MirrorCube.GetMirrorScale();
	//auto MirorrToCamera = XMVectorGetX(XMVector3Length(XMVectorSubtract(m_MainCamera.GetPosition(), m_MirrorCube.GetMirrorPosition())));
	//Vector3 mainCameraInverseDirection = -MainCameraViewDirection;

	////���ς���p�x�v�Z

	//float dot = XMVectorGetX(XMVector3Dot(mainCameraInverseDirection, leftFaceNormal));
	//float angleRad = acosf(dot);//���W�A��
	//float angleDeg = XMConvertToDegrees(angleRad);//�p�x

	//float angleDegMirror = angleDeg * 2;   //3

	//float height = (MirrorScale.z / 2) * tan(angleDeg);//5
	//float hypotenuse = (MirrorScale.z / 2) / cos(angleDeg);//4

	//auto OneMinusFour = MirorrToCamera - hypotenuse;//1-4

	//angle = atan(height / OneMinusFour);//���W�A��

	//angle = XMConvertToDegrees(angle);//�p�x

	//angle = angle * 2;

}

//=======================================
//�`�揈��
//=======================================
void Mirror_Camera::Draw() {

	// �r���[�ϊ����쐬
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	//m_Position

	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up); // ����n�ɂ����@20230511 by suzuki.tomoki
	// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
	// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
	// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
	// m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);

	static const float viewHeight = 50.0f;//����̍���
	static const float viewWidth = viewHeight * static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());//����̕�

	//�v���W�F�N�V�����s��̐���
	float fieldOfView = DirectX::XMConvertToRadians(60.0f);// ����p

	float aspectRatio = static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());	//�A�X�y�N�g��
	float nearPlane = mirrorToReflectionCameraDistance;       // �j�A�N���b�v
	float farPlane = 10000.0f;      // �t�@�[�N���b�v

	// �v���W�F�N�V�����s��̐���
	Matrix MirrorProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);

	// ���s���e�̏ꍇ(�v���_�N�V�����s����쐬)
	//Matrix MirrorProjectionMatrix = DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearPlane, farPlane);

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

DirectX::SimpleMath::Vector3 Mirror_Camera::GetMirrorCameraPos()
{
	return m_Position;
}