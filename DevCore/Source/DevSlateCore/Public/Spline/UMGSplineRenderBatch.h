// Copyright Qibo Pang 2022. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"
#include "Layout/Clipping.h"

class DEVSLATECORE_API FUMGSplineRenderBatch
{
public:
	FUMGSplineRenderBatch(TArray<FSlateVertex>* InSourceVertArray, TArray<SlateIndex>* InSourceIndexArray);
	void ReserveVertices(uint32 Num) const;
	void ReserveIndices(uint32 Num) const;
	
	void AddVertex(FSlateVertex&& Vertex) const;
	void AddIndex(SlateIndex Index) const;
	
	void AddVertices(const TArray<FSlateVertex>& InVertices) const;
	void AddIndices(const TArray<SlateIndex>& InIndices) const;

	uint32 GetNumVertices() const;
	uint32 GetNumIndices() const;
	
	bool IsValidForRendering() const;

public:
	TArray<FSlateVertex>* SourceVertices;
	TArray<SlateIndex>* SourceIndices;
};
