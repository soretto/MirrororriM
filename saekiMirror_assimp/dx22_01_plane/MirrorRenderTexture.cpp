
#include "MirrorRenderTexture.h"
#include <stdexcept>

// MirrorRenderTexture クラスの static メンバ変数の実体を定義
ID3D11Device* MirrorRenderTexture::MirrorDevice{};
ID3D11Texture2D* MirrorRenderTexture::MirrorRenderTargetTexture{};
ID3D11RenderTargetView* MirrorRenderTexture::MirrorRenderTargetView{};
ID3D11ShaderResourceView* MirrorRenderTexture::MirrorShaderResourceView{};
ID3D11Texture2D* MirrorRenderTexture::MirrorDepthStencilTexture{};
ID3D11DepthStencilView* MirrorRenderTexture::MirrorDepthStencilView{};

MirrorRenderTexture::MirrorRenderTexture() {

	// コンストラクタ
	MirrorDevice = nullptr;
	MirrorRenderTargetTexture = nullptr;
	MirrorRenderTargetView = nullptr;
	MirrorShaderResourceView = nullptr;
	MirrorDepthStencilTexture = nullptr;
	MirrorDepthStencilView = nullptr;
}

void MirrorRenderTexture::Init(ID3D11Device* device) {

	if (!device) {
		throw std::invalid_argument("デバイスあらへんがな");
	}

	// デバイスの設定
	MirrorDevice = device;

	// テクスチャの設定
	D3D11_TEXTURE2D_DESC MirrorTextureDesc = {};
	MirrorTextureDesc.Width = 1024;
	MirrorTextureDesc.Height = 1024;
	MirrorTextureDesc.MipLevels = 1;
	MirrorTextureDesc.ArraySize = 1;
	MirrorTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // RGBA形式
	MirrorTextureDesc.SampleDesc.Count = 1;
	MirrorTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	MirrorTextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	MirrorTextureDesc.CPUAccessFlags = 0;
	MirrorTextureDesc.MiscFlags = 0;

	//シェーダーリソースビューの設定
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = 1;

	HRESULT hr;

	// テクスチャ作成
	hr = MirrorDevice->CreateTexture2D(&MirrorTextureDesc, nullptr, &MirrorRenderTargetTexture);

	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Error CreateTexture2D", "Error", MB_OK);
		return;
	}

	// レンダーターゲットビューを作成
	hr = MirrorDevice->CreateRenderTargetView(MirrorRenderTargetTexture, nullptr, &MirrorRenderTargetView);

	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Error CreateRenderTargetView", "Error", MB_OK);
		return;
	}

	// シェーダーリソースビュー（ピクセルシェーダーでの利用）を作成
	hr = MirrorDevice->CreateShaderResourceView(MirrorRenderTargetTexture, &SRVDesc, &MirrorShaderResourceView);

	if (FAILED(hr))
	{
		MessageBoxA(NULL, "Error CreateShaderResourceView", "Error", MB_OK);
		return;
	}

	// 深度バッファの設定
	D3D11_TEXTURE2D_DESC MirrorDepthDesc = MirrorTextureDesc;
	MirrorDepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // デプスステンシルバッファのフォーマットを設定
	MirrorDepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;//デプスステンシルビューとしてバインド

	MirrorDevice->CreateTexture2D(&MirrorDepthDesc, nullptr, &MirrorDepthStencilTexture);

	// デプスステンシルビューを作成
	if (MirrorDepthStencilTexture != nullptr)MirrorDevice->CreateDepthStencilView(MirrorDepthStencilTexture, nullptr, &MirrorDepthStencilView);

}

//鏡用のレンダリング
void MirrorRenderTexture::MirrorRender(ID3D11DeviceContext* context,
	const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) {

	// レンダーターゲットビューの設定
	context->OMSetRenderTargets(1, &MirrorRenderTargetView, MirrorDepthStencilView);//描画結果をテクスチャにする下準備

	// レンダーターゲットクリア
	float ClearColor[4] = { 0.0f, 0.0f, 0.3f, 1.0f };
	context->ClearRenderTargetView(MirrorRenderTargetView, ClearColor);
	context->ClearDepthStencilView(MirrorDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	Renderer::SetViewMatrix((DirectX::SimpleMath::Matrix*)&view);//ビュー行列をセット

	Renderer::SetProjectionMatrix((DirectX::SimpleMath::Matrix*)&projection);//プロジェクション行列をセット
}



MirrorRenderTexture::~MirrorRenderTexture() {
	// メモリ解放
	if (MirrorRenderTargetTexture) MirrorRenderTargetTexture->Release();
	if (MirrorRenderTargetView) MirrorRenderTargetView->Release();
	if (MirrorShaderResourceView) MirrorShaderResourceView->Release();
}

// レンダーターゲットビューの取得
ID3D11RenderTargetView* MirrorRenderTexture::GetRenderTargetView(void) {
	return MirrorRenderTargetView;
}

// シェーダーリソースビューの取得（ピクセルシェーダー用）
ID3D11ShaderResourceView* MirrorRenderTexture::GetShaderResourceView(void) {
	return MirrorShaderResourceView;
}

//深度バッファの取得
ID3D11DepthStencilView* MirrorRenderTexture::GetMirrorDepthStencilView(void) {
	return MirrorDepthStencilView;
}