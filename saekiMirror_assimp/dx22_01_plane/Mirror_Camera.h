#pragma once

#include "VertexBuffer.h"
#include"Mirror_Cube.h"
#include"Camera.h"


//Camera�N���X�̎q�I�u�W�F�N�g�̋��̃J�����N���X
class Mirror_Camera : public Camera
{

public:

	Mirror_Camera(Mirror_Cube& mirrorcube, Camera& camera) :Camera(mirrorcube), m_MirrorCube(mirrorcube), m_MainCamera(camera) {};//�R���X�g���N�^
		//:m_MirrorCube(mirrorcube), m_MainCamera(camera) {}//�R���X�g���N�^

	void Init();
	void Update();
	void Uninit();
	void Draw();
	// �r���[�s��̎擾
	DirectX::XMMATRIX GetViewMatrix() const;
	// �v���W�F�N�V�����s��̎擾
	DirectX::XMMATRIX GetProjectionMatrix(float aspectRatio) const;

	static DirectX::SimpleMath::Vector3 GetMirrorCameraPos();

	static DirectX::SimpleMath::Vector3	m_Position;



private:

	 Mirror_Cube& m_MirrorCube;

	 Camera& m_MainCamera;

	 float angle;
	 float mirrorToReflectionCameraDistance;
};