// Fill out your copyright notice in the Description page of Project Settings.

#include "Track/MovieSceneUMGTrack.h"

#include "Section/MovieSceneUMGSection.h"

bool UMovieSceneUMGTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneUMGSection::StaticClass();
}

UMovieSceneSection* UMovieSceneUMGTrack::CreateNewSection()
{
	return NewObject<UMovieSceneUMGSection>(this, NAME_None, RF_Transactional);
}

bool UMovieSceneUMGTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}

void UMovieSceneUMGTrack::AddSection(UMovieSceneSection& Section)
{
	const UMovieSceneUMGSection* MovieSceneUMGSection = Cast<UMovieSceneUMGSection>(&Section);
	if (IsValid(MovieSceneUMGSection))
	{
		Sections.Add(&Section);
	}
}

void UMovieSceneUMGTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneUMGTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneUMGTrack::IsEmpty() const
{
	return Sections.IsEmpty();
}

const TArray<UMovieSceneSection*>& UMovieSceneUMGTrack::GetAllSections() const
{
	return Sections;
}

bool UMovieSceneUMGTrack::SupportsMultipleRows() const
{
	return true;
}