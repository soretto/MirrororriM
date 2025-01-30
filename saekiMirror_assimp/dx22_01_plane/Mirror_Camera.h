#pragma once

#include "VertexBuffer.h"
#include"Mirror_Cube.h"
#include"Camera.h"


//Cameraクラスの子オブジェクトの鏡のカメラクラス
class Mirror_Camera : public Camera
{

public:

	Mirror_Camera(Mirror_Cube& mirrorcube, Camera& camera) :Camera(mirrorcube), m_MirrorCube(mirrorcube), m_MainCamera(camera) {};//コンストラクタ
		//:m_MirrorCube(mirrorcube), m_MainCamera(camera) {}//コンストラクタ

	void Init();
	void Update();
	void Uninit();
	void Draw();
	// ビュー行列の取得
	DirectX::XMMATRIX GetViewMatrix() const;
	// プロジェクション行列の取得
	DirectX::XMMATRIX GetProjectionMatrix(float aspectRatio) const;

	static DirectX::SimpleMath::Vector3 GetMirrorCameraPos();

	static DirectX::SimpleMath::Vector3	m_Position;



private:

	 Mirror_Cube& m_MirrorCube;

	 Camera& m_MainCamera;

	 float angle;
	 float mirrorToReflectionCameraDistance;
};