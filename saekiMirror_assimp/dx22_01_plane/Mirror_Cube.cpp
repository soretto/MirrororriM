#include"Mirror_Cube.h"

using namespace DirectX::SimpleMath;

#define PI 3.14159265358f

Vector3 Mirror_Cube::GetMirrorPosition() 
{
	return m_Position;
}

void Mirror_Cube::RenderMirrorTexture()
{

}

void Mirror_Cube::SetMirrorPosition(Vector3 position) 
{
	m_Position = position;
}

Vector3 Mirror_Cube::GetMirrorRotation()
{
	return m_Rotation;
}

void Mirror_Cube::Init()
{
	// 頂点データ
	std::vector<VERTEX_3D>	vertices;
	vertices.resize(24);

	// 上面 (Y軸正方向)
	vertices[0].position = Vector3(-10, 10, 10);  vertices[0].uv = Vector2(0, 0);
	vertices[1].position = Vector3(10, 10, 10);   vertices[1].uv = Vector2(0.33, 0);
	vertices[2].position = Vector3(-10, 10, -10); vertices[2].uv = Vector2(0, 0.5);
	vertices[3].position = Vector3(10, 10, -10);  vertices[3].uv = Vector2(0.33, 0.5);

	vertices[0].normal = Vector3(0, 1, 0);
	vertices[1].normal = Vector3(0, 1, 0);
	vertices[2].normal = Vector3(0, 1, 0);
	vertices[3].normal = Vector3(0, 1, 0);

	// 下面 (Y軸負方向)
	vertices[4].position = Vector3(-10, -10, 10); vertices[4].uv = Vector2(0.66, 0.5);
	vertices[5].position = Vector3(10, -10, 10);   vertices[5].uv = Vector2(1, 0.5);
	vertices[6].position = Vector3(-10, -10, -10); vertices[6].uv = Vector2(0.66, 1);
	vertices[7].position = Vector3(10, -10, -10);  vertices[7].uv = Vector2(1, 1);

	vertices[4].normal = Vector3(0, -1, 0);
	vertices[5].normal = Vector3(0, -1, 0);
	vertices[6].normal = Vector3(0, -1, 0);
	vertices[7].normal = Vector3(0, -1, 0);

	// 前面 (Z軸正方向)
	vertices[8].position = Vector3(-10, 10, 10); vertices[8].uv = Vector2(0.33, 0);
	vertices[9].position = Vector3(10, 10, 10);    vertices[9].uv = Vector2(0.66, 0);
	vertices[10].position = Vector3(-10, -10, 10); vertices[10].uv = Vector2(0.33, 0.5);
	vertices[11].position = Vector3(10, -10, 10); vertices[11].uv = Vector2(0.66, 0.5);

	vertices[8].normal = Vector3(0, 0, 1);
	vertices[9].normal = Vector3(0, 0, 1);
	vertices[10].normal = Vector3(0, 0, 1);
	vertices[11].normal = Vector3(0, 0, 1);

	// 背面 (Z軸負方向)
	vertices[12].position = Vector3(-10, 10, -10); vertices[12].uv = Vector2(0.33, 0.5);
	vertices[13].position = Vector3(10, 10, -10);  vertices[13].uv = Vector2(0.66, 0.5);
	vertices[14].position = Vector3(-10, -10, -10); vertices[14].uv = Vector2(0.33, 1);
	vertices[15].position = Vector3(10, -10, -10); vertices[15].uv = Vector2(0.66, 1);

	vertices[12].normal = Vector3(0, 0, -1);
	vertices[13].normal = Vector3(0, 0, -1);
	vertices[14].normal = Vector3(0, 0, -1);
	vertices[15].normal = Vector3(0, 0, -1);

	// 左面 (X軸負方向)
	vertices[16].position = Vector3(-10, 10, 10);  vertices[16].normal = Vector3(-1, 0, 0);
	vertices[17].position = Vector3(-10, 10, -10); vertices[17].normal = Vector3(-1, 0, 0);
	vertices[18].position = Vector3(-10, -10, 10); vertices[18].normal = Vector3(-1, 0, 0);
	vertices[19].position = Vector3(-10, -10, -10); vertices[19].normal = Vector3(-1, 0, 0);

	vertices[16].uv = Vector2(1.0f, 0.0f);
	vertices[17].uv = Vector2(0.0f, 0.0f);
	vertices[18].uv = Vector2(1.0f, 1.0f);
	vertices[19].uv = Vector2(0.0f, 1.0f);

	// 右面 (X軸正方向)
	vertices[20].position = Vector3(10, 10, 10);   vertices[20].normal = Vector3(1, 0, 0);
	vertices[21].position = Vector3(10, 10, -10);  vertices[21].normal = Vector3(1, 0, 0);
	vertices[22].position = Vector3(10, -10, 10);  vertices[22].normal = Vector3(1, 0, 0);
	vertices[23].position = Vector3(10, -10, -10); vertices[23].normal = Vector3(1, 0, 0);

	vertices[20].uv = Vector2(0, 0.5);
	vertices[21].uv = Vector2(0.33, 0.5);
	vertices[22].uv = Vector2(0, 1);
	vertices[23].uv = Vector2(0.33, 1);

	//全ての頂点の色を白にする
	for (int i = 0; i < 24; ++i)
	{
		vertices[i].color = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//平たく
	m_Scale = Vector3(0.3f, 5.0f, 3.0f);

	// 頂点バッファ生成
	m_VertexBuffer.Create(vertices);

	// インデックスバッファ生成
	std::vector<unsigned int> indices;
	indices.resize(36);

	indices = {

		// 上面
		0, 1, 2,
		1, 3, 2,
		// 下面
		4, 5, 6,
		5, 7, 6,
		// 前面
		8, 9, 10,
		9, 11, 10,
		// 背面
		12, 14, 13,
		13, 14, 15,
		// 左面
		16, 17, 18,
		17, 19, 18,
		// 右面
		20, 22, 21,
		21, 22, 23

	};

	// インデックスバッファ生成
	m_IndexBuffer.Create(indices);

	// シェーダオブジェクト生成
	m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");

	//少し傾ける
	//m_Rotation = Vector3(0.0f / 180.0f * PI, -30.0f / 180.0f * PI, 0.0f / 180.0f * PI);
	m_Rotation = Vector3(0.0f / 180.0f * PI, 0.0f / 180.0f * PI, 0.0f / 180.0f * PI);

	//ちょっと上に
	m_Position.y = 10.0f;
	
}

void Mirror_Cube::Draw()
{
	// SRT情報作成
	Matrix r = Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);//回転
	Matrix t = Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);//平行移動
	Matrix s = Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);//拡大縮小

	Matrix worldmtx;//ワールド行列
	worldmtx = s * r * t;
	Renderer::SetWorldMatrix(&worldmtx); // GPUにセット

	// 描画の処理
	ID3D11DeviceContext* Mirrordevicecontext = Renderer::GetDeviceContext();

	// トポロジーをセット（プリミティブタイプ）
	Mirrordevicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();

	//シェーダーリソースビュー(ピクセルシェーダがテクスチャを読むためのもの)をセット
	Mirrordevicecontext->PSSetShaderResources(0, 1, &m_srv);

	Mirrordevicecontext->DrawIndexed(
		36,							// 描画するインデックス数（四角形なんで４）
		0,							// 最初のインデックスバッファの位置
		0);							// 頂点バッファの最初の頂点位置
}

void Mirror_Cube::Update() {


	if (GetAsyncKeyState('R') & 0x8000) { m_Rotation.y += 0.01f; }
	if (GetAsyncKeyState('L') & 0x8000) { m_Rotation.y -= 0.01f; }

	//移動
	if (GetAsyncKeyState('W') & 0x8000) { m_Position.z += 1.0f; }
	if (GetAsyncKeyState('S') & 0x8000) { m_Position.z -= 1.0f; }
	if (GetAsyncKeyState('A') & 0x8000) { m_Position.x -= 1.0f; }
	if (GetAsyncKeyState('D') & 0x8000) { m_Position.x += 1.0f; }
	if (GetAsyncKeyState('Q') & 0x8000) { m_Position.y += 1.0f; }
	if (GetAsyncKeyState('E') & 0x8000) { m_Position.y -= 1.0f; }
}

void Mirror_Cube::Uninit()
{
}
