#pragma once
#include<SimpleMath.h>

//-----------------------------------------------------------------------------
//Camera�N���X
//-----------------------------------------------------------------------------
class Camera {

protected:
	DirectX::SimpleMath::Vector3	m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3	m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3	m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	DirectX::SimpleMath::Vector3	m_Target{};
	DirectX::SimpleMath::Matrix		m_ViewMatrix{};

	DirectX::SimpleMath::Matrix m_ProjectionMatrix;


public:
	void Init();
	void Update();
	void Draw();
	void Uninit();

	void SetPosition(const DirectX::SimpleMath::Vector3& pos);

	//�|�W�V�����Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition()const;

	 //�����x�N�g���Q�b�^�[
	 DirectX::SimpleMath::Vector3 GetTargetVector()const;
};