// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/LoadScreenSaveGame.h"

FSavedMap ULoadScreenSaveGame::GetSavedMapWithName(const FString& MapAssetName)
{
	for (const FSavedMap& SavedMap : SavedMaps)
	{
		if (SavedMap.MapAssetName == MapAssetName)
		{
			return SavedMap;
		}
	}
	return FSavedMap();
}

bool ULoadScreenSaveGame::HasMap(const FString& MapAssetName)
{
	for (const FSavedMap& SavedMap : SavedMaps)
	{
		if (SavedMap.MapAssetName == MapAssetName)
		{
			return true;
		}
	}
	return false;
}
