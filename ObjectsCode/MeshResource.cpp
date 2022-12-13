#include "MeshResource.h"
#include "AssimpLoader.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "RootSignature.h"
#include "PipelineState.h"
#include "IndexBuffer.h"
#include "DescriptorHeap.h"
#include "Texture2D.h"
#include "App.h"
#include "Camera.h"
#include <filesystem>
#include <iostream>
#include <d3dx12.h>

using namespace DirectX;

// 拡張子を置き換える処理
namespace fs = std::filesystem;
std::wstring ReplaceExtension(const std::wstring& origin, const char* ext)
{
	fs::path p = origin.c_str();
	return p.replace_extension(ext).c_str();
}

MeshResource::MeshResource(const wchar_t* modelFile){
	ImportSettings importSetting = // これ自体は自作の読み込み設定構造体
	{
		modelFile,
		mMeshes,
		false,
		false
	};

	AssimpLoader loader;
	if (!loader.Load(importSetting))
	{
		assert(!"モデルのloadに失敗");
	}


	// メッシュの数だけ頂点バッファを用意する
	mVertexBuffers.reserve(mMeshes.size());
	for (size_t i = 0; i < mMeshes.size(); i++)
	{
		auto size = sizeof(Vertex) * mMeshes[i].Vertices.size();
		auto stride = sizeof(Vertex);
		auto vertices = mMeshes[i].Vertices.data();
		auto pVB = new VertexBuffer(size, stride, vertices);
		if (!pVB->IsValid())
		{
			assert(!"頂点バッファの生成に失敗\n");
		}

		mVertexBuffers.push_back(pVB);
	}

	// メッシュの数だけインデックスバッファを用意する
	mIndexBuffers.reserve(mMeshes.size());
	for (size_t i = 0; i < mMeshes.size(); i++)
	{
		auto size = sizeof(uint32_t) * mMeshes[i].Indices.size();
		auto indices = mMeshes[i].Indices.data();
		auto pIB = new IndexBuffer(size, indices);
		if (!pIB->IsValid())
		{
			assert(!"インデックスバッファの生成に失敗\n");
		}

		mIndexBuffers.push_back(pIB);
	}

	
	mMaterialHandles.clear();
	mDescriptorHeap = new DescriptorHeap();
	for (size_t i = 0; i < mMeshes.size(); i++)
	{
		//auto texPath = ReplaceExtension(mMeshes[i].DiffuseMap, "tga"); // もともとはpsdになっていてちょっとめんどかったので、同梱されているtgaを読み込む
		std::cout << ToUTF8(mMeshes[i].DiffuseMap) << "\na\n";
		auto mainTex = Texture2D::Get(mMeshes[i].DiffuseMap);
		auto handle = mDescriptorHeap->Register(mainTex);
		mMaterialHandles.push_back(handle);
	}

	mRootSignature = new RootSignature();
	if (!mRootSignature->IsValid())
	{
		assert(!"ルートシグネチャの生成に失敗\n");
	}

	if (!SetPipelineState()) {
		assert(!"パイプラインステートの設定");
	}


}

MeshResource::~MeshResource() {
	delete mDescriptorHeap;
	mDescriptorHeap = 0;
	delete mRootSignature;
	mRootSignature = 0;
	delete mPipelineState;
	mPipelineState = 0;
	while(!(mVertexBuffers.empty())) {
		delete mVertexBuffers.back();
	}
	while(!(mIndexBuffers.empty())) {
		delete mIndexBuffers.back();
	}
	while (!(mMaterialHandles.empty())) {
		delete mMaterialHandles.back();
	}
}

//-------------------------------------------------
//    meshの描画
//-------------------------------------------------
void MeshResource::Draw(const ConstantBuffer& transform) {
	//現在のバックバッファ―の取得
	auto currentIndex = Engine::Instance()->CurrentBackBufferIndex();
	auto commandList = Engine::Instance()->CommandList();  //コマンドリストの取得
	auto materialHeap = mDescriptorHeap->GetHeap(); // ディスクリプタヒープ

	//描画
	for (size_t i = 0; i < mMeshes.size(); i++)
	{
		auto vbView = mVertexBuffers[i]->View();
		auto ibView = mIndexBuffers[i]->View();

		commandList->SetGraphicsRootSignature(mRootSignature->Get());
		commandList->SetPipelineState(mPipelineState->Get());
		commandList->SetGraphicsRootConstantBufferView(0, transform.GetAddress());

		commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		commandList->IASetVertexBuffers(0, 1, &vbView);
		commandList->IASetIndexBuffer(&ibView);

		commandList->SetDescriptorHeaps(1, &materialHeap); // 使用するディスクリプタヒープをセット
		commandList->SetGraphicsRootDescriptorTable(1, mMaterialHandles[i]->HandleGPU); // そのメッシュに対応するディスクリプタテーブルをセット

		commandList->DrawIndexedInstanced(mMeshes[i].Indices.size(), 1, 0, 0, 0);
	}
}




//-------------------------------------------------
//    パイプラインステートのセット
//-------------------------------------------------
bool MeshResource::SetPipelineState() {
	mPipelineState = new PipelineState();
	mPipelineState->SetInputLayout(Vertex::InputLayout);
	mPipelineState->SetRootSignature(mRootSignature->Get());
	mPipelineState->SetVS(L"x64/Debug/SimpleVS.cso");
	mPipelineState->SetPS(L"x64/Debug//SimplePS.cso");
	mPipelineState->Create();
	if (!mPipelineState->IsValid())
	{
		return false;
	}
	return true;
}