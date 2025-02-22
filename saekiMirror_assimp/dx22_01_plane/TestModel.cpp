#include	<SimpleMath.h>
#include	<memory>
#include	"TestModel.h"
#include	"MeshRenderer.h"
#include	"Shader.h"
#include	"Texture.h"
#include	"StaticMesh.h"
#include	"utility.h"

using namespace DirectX::SimpleMath;

void TestModel::Init()
{
	// メッシュ読み込み
	StaticMesh staticmesh;

	//3Dモデルデータ

	//std::u8string modelFile = u8"assets\\model\\cylinder\\cylinder.obj";
	std::u8string modelFile = u8"assets/model/Stages/stage01.obj";

	//テクスチャディレクトリ
	//std::string texDirectory = "assets/model/cylinder";
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

	// マテリアル情報取得
	std::vector<MATERIAL> materials = staticmesh.GetMaterials();

	//マテリアル数分ループ
	for (int i = 0; i < materials.size(); ++i)
	{
		std::unique_ptr<Material>m = std::make_unique<Material>();

		m->Create(materials[i]);

		m_Materiales.push_back(std::move(m));
	}
	//位置
	m_Position.z -= 40.0f;
	m_Position.y -= 20.0f;

	//回転
	m_Rotation.y = 4.9f;

	m_Scale = Vector3(0.1f, 0.1f, 0.1f);
}
void TestModel::Update()
{
	//m_Rotation.y += -0.01f;
	m_Scale.x = 10;
	m_Scale.y = 10;
	m_Scale.z = 10;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		
	}
}


void TestModel::Draw()
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
		//マテリアルセット
		m_Materiales[m_subsets[i].MaterialIdx]->SetGPU();

		if (m_Materiales[m_subsets[i].MaterialIdx]->isTextureEnable())
		{
			//テクスチャセット
			m_Textures[m_subsets[i].MaterialIdx]->SetGPU();
		}


		m_Textures[m_subsets[i].MaterialIdx]->SetGPU();

		m_MeshRenderer.DrawSubset(
			m_subsets[i].IndexNum,    // 描画するインデックス数
			m_subsets[i].IndexBase,   // 最初のインデックスバッファの位置
			m_subsets[i].VertexBase); // 頂点バッファの最初から使用
	}
}

void TestModel::Uninit()
{

}