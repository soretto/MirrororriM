#pragma once
#include <d3d11.h>
#include	<DirectXMath.h>
#include	<SimpleMath.h>
#include	<io.h>
#include"Renderer.h"

//外部ライブラリ
#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"d3d11.lib")

// 鏡のレンダーテクスチャを管理するクラス
class MirrorRenderTexture {
public:
    // コンストラクタ：テクスチャ作成
    MirrorRenderTexture();
    ~MirrorRenderTexture();

    static void Init(ID3D11Device* device);

    static void MirrorRender(ID3D11DeviceContext* context, 
        const DirectX::SimpleMath::Matrix& view,const DirectX::SimpleMath::Matrix& projection);

    // レンダーターゲットビューの取得
    static ID3D11RenderTargetView* GetRenderTargetView(void);

    // シェーダーリソースビューの取得（ピクセルシェーダー用）
    static ID3D11ShaderResourceView* GetShaderResourceView(void);

    //深度バッファの取得
    static ID3D11DepthStencilView* GetMirrorDepthStencilView(void);

private:

    static ID3D11Device* MirrorDevice;//Direct3Dデバイス
    static ID3D11Texture2D* MirrorRenderTargetTexture;//レンダーテクスチャ
    static ID3D11RenderTargetView* MirrorRenderTargetView;
    static ID3D11ShaderResourceView* MirrorShaderResourceView;
    static ID3D11Texture2D* MirrorDepthStencilTexture;//深度ステンシルバッファ
    static ID3D11DepthStencilView* MirrorDepthStencilView; // デプスステンシルビュー
};
