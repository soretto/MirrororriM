#pragma once

#include <SimpleMath.h>
#include "MeshRenderer.h"
#include "Shader.h"
#include "Texture.h"
#include "StaticMesh.h"
#include "utility.h"
#include "Material.h"

class MirrorFrame
{
private:
	// SRT情報（姿勢情報）
	DirectX::SimpleMath::Vector3 m_Position = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Rotation = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 m_Scale = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);

	// 描画の為の情報（見た目に関わる部分）
	Shader m_Shader; // シェーダー

	// 描画の為の情報（メッシュに関わる情報）
	MeshRenderer m_MeshRenderer; // 頂点バッファ・インデックスバッファ・インデックス数

	// 描画の為の情報（見た目に関わる部分）
	std::vector<std::unique_ptr<Material>> m_Materiales;
	std::vector<SUBSET> m_subsets;
	std::vector<std::unique_ptr<Texture>> m_Textures; // テクスチャ

public:
	
	MirrorFrame(); //コンストラクタ
	~MirrorFrame(); //デストラクタ


	bool move_flg = false;
	void Init();
	void Update();
	void Draw();
	void Uninit();

	//position セッター関数・ゲッター関数
	void SetPosition(const DirectX::SimpleMath::Vector3& pos);
	DirectX::SimpleMath::Vector3 GetPosition() const;
	DirectX::SimpleMath::Vector3 GetRotation() const;
};

