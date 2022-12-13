#include "Object2DResource.h"	
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "RootSignature.h"
#include "PipelineState.h"
#include "IndexBuffer.h"
#include "DescriptorHeap.h"
#include "SharedStruct.h"
#include "Texture2D.h"
#include "App.h"
#include "Engine.h"
#include <d3dx12.h>
#include <DirectXmath.h>

using namespace DirectX;

Object2DResource::Object2DResource(const wchar_t* textureFile) {
	Vertex vertices[4] = {};
	vertices[0].Position = XMFLOAT3(-10.0f, 10.0f, 0.0f);
	vertices[0].UV = XMFLOAT2(0.0f, 0.0f);

	vertices[1].Position = XMFLOAT3(10.0f, 10.0f, 0.0f);
	vertices[1].UV = XMFLOAT2(1.0f, 0.0f);

	vertices[2].Position = XMFLOAT3(10.0f, -10.0f, 0.0f);
	vertices[2].UV = XMFLOAT2(1.0f, 1.0f);

	vertices[3].Position = XMFLOAT3(-10.0f, -10.0f, 0.0f);
	vertices[3].UV = XMFLOAT2(0.0f, 1.0f);

	auto vertexSize = sizeof(Vertex) * std::size(vertices);
	auto vertexStride = sizeof(Vertex);
	mVertexBuffer = new VertexBuffer(vertexSize, vertexStride, vertices);
	if (!mVertexBuffer->IsValid())
	{
		assert(!"頂点バッファの生成に失敗\n");
	}

	uint32_t indices[] = { 0, 1, 2, 0, 2, 3 }; // これに書かれている順序で描画する

	// インデックスバッファの生成
	auto size = sizeof(uint32_t) * std::size(indices);
	mIndexBuffer = new IndexBuffer(size, indices);
	if (!mIndexBuffer->IsValid())
	{
		assert(!"インデックスバッファの生成に失敗\n");
	}

	//テクスチャの設定
	mDescriptorHeap = new DescriptorHeap();
	auto mainTex = Texture2D::Get(textureFile);
	auto handle = mDescriptorHeap->Register(mainTex);
	mMaterialHandle = handle;
	

	//ルートシグネチャの生成
	mRootSignature = new RootSignature();
	if (!mRootSignature->IsValid())
	{
		assert(!"ルートシグネチャの生成に失敗\n");
	}

	//パイプラインステートの生成
	mPipelineState = new PipelineState();
	mPipelineState->SetInputLayout(Vertex::InputLayout);
	mPipelineState->SetRootSignature(mRootSignature->Get());
	mPipelineState->SetVS(L"x64/Debug/SimpleVS.cso");
	mPipelineState->SetPS(L"x64/Debug//SimplePS.cso");
	mPipelineState->Create();
	if (!mPipelineState->IsValid())
	{
		assert(!"生成失敗\n");
	}
	
}

Object2DResource::~Object2DResource() {
	delete mVertexBuffer;
	mVertexBuffer = 0;
	delete mIndexBuffer;
	mIndexBuffer = 0;
	delete mDescriptorHeap;
	mDescriptorHeap = 0;
	delete mMaterialHandle;
	mMaterialHandle = 0;
	delete mPipelineState;
	mPipelineState = 0;
	delete mRootSignature;
	mRootSignature = 0;
}

//--------------------------------------------------------------
//    描画処理です
//--------------------------------------------------------------
void Object2DResource::Draw(const ConstantBuffer& transform) {
	//現在のバックバッファ―の取得
	auto currentIndex = Engine::Instance()->CurrentBackBufferIndex();
	auto commandList = Engine::Instance()->CommandList();  //コマンドリストの取得
	auto materialHeap = mDescriptorHeap->GetHeap(); // ディスクリプタヒープ

	//描画
	auto vbView = mVertexBuffer->View();
	auto ibView = mIndexBuffer->View();

	commandList->SetGraphicsRootSignature(mRootSignature->Get());
	commandList->SetPipelineState(mPipelineState->Get());
	commandList->SetGraphicsRootConstantBufferView(0, transform.GetAddress());
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->IASetVertexBuffers(0, 1, &vbView);
	commandList->IASetIndexBuffer(&ibView);

	commandList->SetDescriptorHeaps(1, &materialHeap); // 使用するディスクリプタヒープをセット
	commandList->SetGraphicsRootDescriptorTable(1, mMaterialHandle->HandleGPU); // そのメッシュに対応するディスクリプタテーブルをセット
	commandList->DrawIndexedInstanced(6, 1, 0, 0, 0);
	
}