#pragma once
#include "ObjectResource.h"
#include <vector>
#include "Engine.h"
#include "SharedStruct.h"

class MeshResource : public ObjectResource{
public:
	MeshResource(const wchar_t* modelFile);
	~MeshResource()override;

	void Draw(const ConstantBuffer& transform)override;


private:
	bool SetPipelineState();
	class DescriptorHeap* mDescriptorHeap = nullptr;
	std::vector<class DescriptorHandle*> mMaterialHandles; // テクスチャ用のハンドル一覧

	class RootSignature* mRootSignature = nullptr;
	class PipelineState* mPipelineState = nullptr;


	std::vector<Mesh> mMeshes;                       // メッシュの配列
	std::vector<class VertexBuffer*> mVertexBuffers; // メッシュの数分の頂点バッファ
	std::vector<class IndexBuffer*> mIndexBuffers;   // メッシュの数分のインデックスバッファ


};
