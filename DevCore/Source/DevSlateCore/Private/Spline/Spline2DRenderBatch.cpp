// Fill out your copyright notice in the Description page of Project Settings.

#include "Spline/Spline2DRenderBatch.h"

#include "Spline/Spline2DBuilder.h"

FSpline2DRenderBatch::FSpline2DRenderBatch(TArray<FSlateVertex>* InSourceVertexArray, TArray<SlateIndex>* InSourceIndexArray)
	: SourceVertices(InSourceVertexArray),
	  SourceIndices(InSourceIndexArray)
{
}

void FSpline2DRenderBatch::ReserveVertices(uint32 Num) const
{
	SourceVertices->Reserve(SourceVertices->Num() + Num);
}

void FSpline2DRenderBatch::ReserveIndices(uint32 Num) const
{
	SourceIndices->Reserve(SourceIndices->Num() + Num);
}

void FSpline2DRenderBatch::AddVertex(FSlateVertex&& Vertex) const
{
	SourceVertices->Add(Vertex);
}

void FSpline2DRenderBatch::AddIndex(SlateIndex Index) const
{
	SourceIndices->Add(Index);
}

void FSpline2DRenderBatch::AddVertices(const TArray<FSlateVertex>& InVertices) const
{
	SourceVertices->Append(InVertices);
}

void FSpline2DRenderBatch::AddIndices(const TArray<SlateIndex>& InIndices) const
{
	SourceIndices->Append(InIndices);
}

uint32 FSpline2DRenderBatch::GetNumVertices() const
{
	return SourceVertices->Num();
}

uint32 FSpline2DRenderBatch::GetNumIndices() const
{
	return SourceIndices->Num();
}

bool FSpline2DRenderBatch::IsValidForRendering() const
{
	return (GetNumVertices() > 0 && GetNumIndices() > 0);
}
