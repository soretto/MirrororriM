#pragma once

#include "VertexBuffer.h"
#include"TestCube.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include"Texture.h"
#include <vector>
#include"MirrorRenderTexture.h"
#include"TestCube.h"

//TestCubeクラスの子オブジェクトの鏡のオブジェクトクラス
class Mirror_Cube : public TestCube
{

public:

	void Init();
	void Update();
	void Draw();
	void Uninit();
	void SetMirrorPosition(DirectX::SimpleMath::Vector3 position);
	DirectX::SimpleMath::Vector3 GetMirrorPosition();
	DirectX::SimpleMath::Vector3 GetMirrorRotation();
	DirectX::SimpleMath::Vector3 GetMirrorScale();
	void RenderMirrorTexture(); // 鏡のカメラからレンダリング

	ID3D11ShaderResourceView* m_srv;

private:

	//ID3D11ShaderResourceView* shaderResourceView;

	// SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	// 描画の為の情報（メッシュに関わる情報)
	IndexBuffer	 m_IndexBuffer; // インデックスバッファ
	VertexBuffer<VERTEX_3D>	m_VertexBuffer; // 頂点バッファ

	// 描画の為の情報（見た目に関わる部分）
	Shader m_Shader; // シェーダー


};
