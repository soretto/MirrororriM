#include "Renderer.h"
#include "Camera.h"
#include "Application.h"
#include "input.h"

using namespace DirectX::SimpleMath;

//=======================================
//初期化処理
//=======================================
void Camera::Init()
{
	m_Position = Vector3(-50.0f, 20.0f, -80.0f);
	m_Target = Vector3(0.0f, 0.0f, 0.0f);
}

//=======================================
//更新処理
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
//描画処理
//=======================================
void Camera::Draw()
{
	// ビュー変換後列作成
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_Position, m_Target, up); // 左手系にした　20230511 by suzuki.tomoki
	// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
	// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
	// このコードは確認テストのために残す
	// m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	static const float viewHeight = 130.0f;//視野の高さ
	static const float viewWidth = viewHeight * static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());//視野の幅

	//プロジェクション行列の生成
	constexpr float fieldOfView = DirectX::XMConvertToRadians(100.0f);// 視野角

	float aspectRatio = static_cast<float>(Application::GetWidth()) / static_cast<float>(Application::GetHeight());	//アスペクト比
	float nearPlane = 1.0f;       // ニアクリップ
	float farPlane = 1000.0f;      // ファークリップ

	//透視投影の場合(プロダクション行列を作成)
	//m_ProjectionMatrix =  DirectX::XMMatrixPerspectiveFovLH( fieldOfView,  aspectRatio,  nearPlane,  farPlane);	//左手系にした　20230511 by suzuki.tomoki

	// 平行投影の場合(プロダクション行列を作成)
	m_ProjectionMatrix = DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearPlane, farPlane);

	// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
	// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
	// このコードは確認テストのために残す
	// projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);//プロジェクション行列の設定
}


//=======================================
//終了処理
//=======================================
void Camera::Uninit(){}

//=======================================
//カメラの位置を設定
//=======================================
void Camera::SetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	m_Position = pos;
}

//=======================================
//カメラの位置を取得
//=======================================
DirectX::SimpleMath::Vector3 Camera::GetPosition()const
{
	return m_Position;
}

//=======================================
//視線ベクトルを取得
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