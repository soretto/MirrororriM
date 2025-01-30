#include "Renderer.h"
#include "Camera.h"
#include "Application.h"
#include "Mirror_Camera.h"
#include "Mirror_Cube.h"
#include"MirrorRenderTexture.h"

#include <DirectXMath.h>
#include <cmath> // 三角関数を使うために必要

using namespace DirectX::SimpleMath;
using namespace DirectX;

DirectX::SimpleMath::Vector3 Mirror_Camera::m_Position;

//=======================================
//初期化処理
//=======================================
//初期位置は鏡面
void Mirror_Camera::Init()
{
	m_Position = m_MirrorCube.GetMirrorPosition();
	m_Target = Vector3(0.0f, 0.0f, 0.0f);

}


//=======================================
//更新処理
//=======================================
void Mirror_Camera::Update()
{

	//メインのカメラのターゲットを取得
	Vector3 MainCameraViewDirection = m_MainCamera.GetTargetVector();

	Vector3 MirrorRotation = m_MirrorCube.GetMirrorRotation();

	//メインカメラのターゲットを鏡の法線に反射させる
	Matrix rotationMatrix = Matrix::CreateFromYawPitchRoll(MirrorRotation.y, MirrorRotation.x, MirrorRotation.z);

	// 現在の鏡の左面の法線を計算
	Vector3 leftFaceNormal = Vector3::TransformNormal(Vector3(-1, 0, 0), rotationMatrix);  // 左面の法線は (-1, 0, 0)

	// 反射ベクトルを計算
	float dotProduct = MainCameraViewDirection.Dot(leftFaceNormal);//メインカメラの視線ベクトルと鏡の法線の内積を計算。
	Vector3 reflection;
	//Vector3 reflection = MainCameraViewDirection + 2.0f * dotProduct * leftFaceNormal;

	//Matrix cameraNormaMatrix = Matrix::CreateLookAt(Vector3::Zero, MainCameraViewDirection, Vector3::Up);
	//Matrix mirrorInvertNormalMatrix = Matrix::CreateLookAt(Vector3::Zero, -leftFaceNormal, Vector3::Up);;
	//Matrix diffMatrix = (mirrorInvertNormalMatrix * cameraNormaMatrix.Invert()).Invert();
	//Vector3 reflection = Vector3::Transform(MainCameraViewDirection, diffMatrix);
	//reflection = Vector3::Transform(reflection, diffMatrix);

	//回転行列を作成
	Matrix mirrorRotationMatrix = Matrix::CreateFromYawPitchRoll(MirrorRotation.y, MirrorRotation.x, MirrorRotation.z);

	//反射ベクトルを計算
	reflection = MainCameraViewDirection;
	reflection = Vector3::Transform(reflection, mirrorRotationMatrix);
	reflection = Vector3::Transform(reflection, mirrorRotationMatrix);
	//reflection *= -1.0f;

	//視点ベクトルを反射ベクトルに変更
	m_Target = reflection + m_Position;

	/**/

	auto mirrorToMainCamera = m_MainCamera.GetPosition() - m_MirrorCube.GetMirrorPosition();//鏡からメインカメラへのベクトル
	auto MirorrToCameraDistance = Vector3::Distance(m_MainCamera.GetPosition(), m_MirrorCube.GetMirrorPosition());//鏡からメインカメラまでの距離
	//auto MirorrToCameraDistance = (m_MainCamera.GetPosition() - m_MirrorCube.GetMirrorPosition()).Length();


	float dot = -MainCameraViewDirection.Dot(leftFaceNormal);//メインカメラの視線ベクトルと鏡の法線の内積を計算。MainCameraViewDirection正規化必要？
	float angleRad = acosf(dot);//内積から角度計算
	float angleDeg = XMConvertToDegrees(angleRad);//ディグリー角度。デバッグ用

	Matrix rotMatrix = Matrix::CreateFromYawPitchRoll(angleRad, 0.0f, 0.0f);//回転行列を作成。マイナス消した
	Vector3 mirrorToReflectionCamera = Vector3::Transform(-leftFaceNormal, -rotMatrix);//鏡用のカメラを設置するベクトルを計算 /*rotMatrixにマイナスつけた*/
	mirrorToReflectionCamera *= MirorrToCameraDistance;//距離を設定

	m_Position = m_MirrorCube.GetMirrorPosition() + mirrorToReflectionCamera;//鏡用のカメラの位置を設定
	m_Position.y = m_MainCamera.GetPosition().y;//高さをメインカメラと同じにする


	//以下デバッグ用

	mirrorToReflectionCameraDistance = Vector3::Distance(m_Position, m_MirrorCube.GetMirrorPosition());//鏡から鏡用のカメラまでの距離
	auto mirrorToReflectionCameraVector = m_Position - m_MirrorCube.GetMirrorPosition();//鏡から鏡用のカメラまでのベクトル




	//Quaternion qt;

	//値取得
	//Vector3 diff = m_MainCamera.GetPosition() - m_MirrorCube.GetMirrorPosition();
	//Vector3 MirrorScale = m_MirrorCube.GetMirrorScale();
	//auto MirorrToCamera = XMVectorGetX(XMVector3Length(XMVectorSubtract(m_MainCamera.GetPosition(), m_MirrorCube.GetMirrorPosition())));
	//Vector3 mainCameraInverseDirection = -MainCameraViewDirection;

	////内積から角度計算

	//float dot = XMVectorGetX(XMVector3Dot(mainCameraInverseDirection, leftFaceNormal));
	//float angleRad = acosf(dot);//ラジアン
	//float angleDeg = XMConvertToDegrees(angleRad);//角度

	//float angleDegMirror = angleDeg * 2;   //3

	//float height = (MirrorScale.z / 2) * tan(angleDeg);//5
	//float hypotenuse = (MirrorScale.z / 2) / cos(angleDeg);//4

	//auto OneMinusFour = MirorrToCamera - hypotenuse;//1-4

	//angle = atan(height / OneMinusFour);//ラジアン

	//angle = XMConvertToDegrees(angle);//角度

	//angle = angle * 2;

}

//=======================================
//描画処理
//=======================================
void Mirror_Camera::Draw() {

	// ビュー変換後列作成
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	//m_Position

	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up); // 左手系にした　20230511 by suzuki.tomoki
	// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
	// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
	// このコードは確認テストのために残す
	// m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);

	static const float viewHeight = 50.0f;//視野の高さ
	static const float viewWidth = viewHeight * static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());//視野の幅

	//プロジェクション行列の生成
	float fieldOfView = DirectX::XMConvertToRadians(60.0f);// 視野角

	float aspectRatio = static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());	//アスペクト比
	float nearPlane = mirrorToReflectionCameraDistance;       // ニアクリップ
	float farPlane = 10000.0f;      // ファークリップ

	// プロジェクション行列の生成
	Matrix MirrorProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);

	// 平行投影の場合(プロダクション行列を作成)
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
//終了処理
//=======================================
void Mirror_Camera::Uninit()
{

}

DirectX::SimpleMath::Vector3 Mirror_Camera::GetMirrorCameraPos()
{
	return m_Position;
}