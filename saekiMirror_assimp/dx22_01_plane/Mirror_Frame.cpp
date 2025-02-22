#include "Mirror_Frame.h"
#include	<memory>
#include	"StaticMesh.h"
#include "input.h"

// デバック用
#include <iostream>



using namespace DirectX::SimpleMath;


//コンストラクタ
//MirrorFrame::MirrorFrame(Camera* cam) : Object(cam)
MirrorFrame::MirrorFrame()
{

}



//デストラクタ
MirrorFrame::~MirrorFrame()
{

}



void MirrorFrame::Init()
{
	// メッシュ読み込み
	StaticMesh staticmesh;

	//3Dモデルデータ
	//std::u8string modelFile = u8"assets/model/MirrorFrame/mirror.obj";
	std::u8string modelFile = u8"assets/model/Stages/stage02.obj";


	//テクスチャディレクトリ
	//std::string texDirectory = "assets/model/MirrorFrame";
	std::string texDirectory = "assets/model/Stages";


	//Meshを読み込む
	std::string tmpStr1(reinterpret_cast<const char*>(modelFile.c_str()), modelFile.size());
	staticmesh.Load(tmpStr1, texDirectory);

	m_MeshRenderer.Init(staticmesh);

	// シェーダオブジェクト生成
	m_Shader.Create("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");

	// サブセット情報取得
	m_subsets = staticmesh.GetSubsets();

	// テクスチャ情報取得
	m_Textures = staticmesh.GetTextures();

	// マテリアル情報
	std::vector<MATERIAL> materials = staticmesh.GetMaterials();

	// マテリアル数分ループ
	for (int i = 0; i < materials.size(); i++)
	{
		// マテリアルオブジェクト生成
		std::unique_ptr<Material> m = std::make_unique<Material>();

		// マテリアル情報をセット
		m->Create(materials[i]);

		// マテリアルオブジェクトを配列に追加
		m_Materiales.push_back(std::move(m));
	}

	//位置
	m_Position.z -= 40.0f;
	m_Position.y -= 20.0f;

	//回転
	m_Rotation.y = 4.9f;

	m_Scale.x = 5.0f;
	m_Scale.y = 5.0f;
	m_Scale.z = 5.0f;

}

void MirrorFrame::Update()
{
	std::stringstream log{};

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		if (move_flg == false)
		{
			move_flg = true;
		}
		else
		{
			move_flg = false;
		}
	}
	if (move_flg == true)
	{
		if (Input::GetKeyPress('W'))
		{
			m_Position.x += 5.0f;
		}
		if (Input::GetKeyPress('S'))
		{
			m_Position.x -= 5.0f;
		}
		if (Input::GetKeyPress('A'))
		{
			m_Position.z += 5.0f;

		}
		if (Input::GetKeyPress('D'))
		{
			m_Position.z -= 5.0f;

		}
	}
	log << "MirrorFrame: " << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << '\n';
	OutputDebugStringA(log.str().c_str());
}


void MirrorFrame::Draw()
{
	
	// SRT情報作成
		Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
		Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
		Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);

		Matrix worldmtx;
		worldmtx = s * r * t;
		Renderer::SetWorldMatrix(&worldmtx); // GPUにセット

		m_Shader.SetGPU();

		// インデックスバッファ・頂点バッファをセット
		m_MeshRenderer.BeforeDraw();

		//マテリアル数分ループ
		for (int i = 0; i < m_subsets.size(); i++)
		{
			// マテリアルをセット（サブセット情報の中にあるマテリアルインデックスを使用）
			m_Materiales[m_subsets[i].MaterialIdx]->SetGPU();

			if (m_Materiales[m_subsets[i].MaterialIdx]->isTextureEnable())
			{
				m_Textures[m_subsets[i].MaterialIdx]->SetGPU();
			}


			m_MeshRenderer.DrawSubset(
				m_subsets[i].IndexNum,    // 描画するインデックス数
				m_subsets[i].IndexBase,   // 最初のインデックスバッファの位置
				m_subsets[i].VertexBase); // 頂点バッファの最初から使用
		}


	

}

void MirrorFrame::Uninit()
{

}

void MirrorFrame::SetPosition(const Vector3& pos)
{
	m_Position.x = pos.x;
	m_Position.y = pos.y;
	m_Position.z = pos.z;
}

Vector3 MirrorFrame::GetPosition() const
{
	return m_Position;
}

Vector3 MirrorFrame::GetRotation() const
{
	return m_Rotation;
}