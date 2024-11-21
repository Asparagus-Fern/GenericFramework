#pragma once

#include "MovieSceneUMGTrack.h"
#include "PropertyTrackEditor.h"

/**
 * 
 */
class SEQUENCEUMGEDSYSTEM_API FUMGTraceEditor : public FPropertyTrackEditor<UMovieSceneUMGTrack>
{
public:
	FUMGTraceEditor(TSharedRef<ISequencer> InSequencer);
	static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);
	static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes();

protected:
	virtual void GenerateKeysFromPropertyChanged(const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys) override;
};
