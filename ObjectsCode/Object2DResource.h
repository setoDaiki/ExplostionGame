#pragma once
#include "ObjectResource.h"

class Object2DResource : public ObjectResource {
public:
	Object2DResource(const wchar_t* textureFile );
	~Object2DResource();

	void Draw(const ConstantBuffer& transform)override;

private:
	class VertexBuffer* mVertexBuffer = nullptr;
	class IndexBuffer* mIndexBuffer = nullptr;
	class RootSignature* mRootSignature = nullptr;
	class PipelineState* mPipelineState = nullptr;
	class DescriptorHandle* mMaterialHandle = nullptr;
	class DescriptorHeap* mDescriptorHeap = nullptr;
};
