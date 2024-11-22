// Copyright Qibo Pang 2022. All Rights Reserved.

#include "Spline/UMGSplineRenderBatch.h"

FUMGSplineRenderBatch::FUMGSplineRenderBatch(TArray<FSlateVertex>* InSourceVertexArray, TArray<SlateIndex>* InSourceIndexArray)
	: SourceVertices(InSourceVertexArray),
	  SourceIndices(InSourceIndexArray)
{
}

void FUMGSplineRenderBatch::ReserveVertices(uint32 Num) const
{
	SourceVertices->Reserve(SourceVertices->Num() + Num);
}

void FUMGSplineRenderBatch::ReserveIndices(uint32 Num) const
{
	SourceIndices->Reserve(SourceIndices->Num() + Num);
}

void FUMGSplineRenderBatch::AddVertex(FSlateVertex&& Vertex) const
{
	SourceVertices->Add(Vertex);
}

void FUMGSplineRenderBatch::AddIndex(SlateIndex Index) const
{
	SourceIndices->Add(Index);
}

void FUMGSplineRenderBatch::AddVertices(const TArray<FSlateVertex>& InVertices) const
{
	SourceVertices->Append(InVertices);
}

void FUMGSplineRenderBatch::AddIndices(const TArray<SlateIndex>& InIndices) const
{
	SourceIndices->Append(InIndices);
}

uint32 FUMGSplineRenderBatch::GetNumVertices() const
{
	return SourceVertices->Num();
}

uint32 FUMGSplineRenderBatch::GetNumIndices() const
{
	return SourceIndices->Num();
}

bool FUMGSplineRenderBatch::IsValidForRendering() const
{
	return (GetNumVertices() > 0 && GetNumIndices() > 0);
}
