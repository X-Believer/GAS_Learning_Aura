// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AuraGameModeBase.h"

#include "EngineUtils.h"
#include "Aura/AuraLogChannels.h"
#include "Game/AuraGameInstance.h"
#include "Game/LoadScreenSaveGame.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerStart.h"
#include "Interaction/SaveInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "UI/ViewModel/MVVM_LoadSlot.h"

void AAuraGameModeBase::SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(LoadSlot->GetLoadSlotName(), SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(LoadSlot->GetLoadSlotName(), SlotIndex);
	}
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	ULoadScreenSaveGame* LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject);
	LoadScreenSaveGame->PlayerName = LoadSlot->GetPlayerName();
	LoadScreenSaveGame->SaveSlotStatus = Taken;
	LoadScreenSaveGame->MapName = LoadSlot->GetMapName();
	LoadScreenSaveGame->WorldAssetName = LoadSlot->WorldAssetName;
	LoadScreenSaveGame->PlayerStartTag = LoadSlot->PlayerStartTag;
	
	UGameplayStatics::SaveGameToSlot(LoadScreenSaveGame, LoadSlot->GetLoadSlotName(), SlotIndex);
}

ULoadScreenSaveGame* AAuraGameModeBase::GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const
{
	USaveGame* SaveGameObject = nullptr;
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex);
	}
	else
	{
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	}
	return Cast<ULoadScreenSaveGame>(SaveGameObject);
}

void AAuraGameModeBase::DeleteSlot(const FString& SlotName, int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(SlotName, SlotIndex);
	}
}

ULoadScreenSaveGame* AAuraGameModeBase::RetrieveInGameSaveData()
{
	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
	
	const FString InGameLoadSlotName = AuraGameInstance->LoadSlotName;
	const int32 InGameSlotIndex = AuraGameInstance->LoadSlotIndex;
	
	return GetSaveSlotData(InGameLoadSlotName, InGameSlotIndex);
}

void AAuraGameModeBase::SaveInGameProgressData(ULoadScreenSaveGame* SaveObject)
{
	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
	
	const FString InGameLoadSlotName = AuraGameInstance->LoadSlotName;
	const int32 InGameSlotIndex = AuraGameInstance->LoadSlotIndex;
	AuraGameInstance->PlayerStartTag = SaveObject->PlayerStartTag;
	
	UGameplayStatics::SaveGameToSlot(SaveObject, InGameLoadSlotName, InGameSlotIndex);
}

void AAuraGameModeBase::SaveWorldState(UWorld* World, const FString& DestinationMapAssetName) const
{
	FString WorldName =	World->GetMapName();
	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);
	
	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
	check(AuraGameInstance);
	
	if (ULoadScreenSaveGame* SaveObject = GetSaveSlotData(AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex))
	{
		if (DestinationMapAssetName != FString(""))
		{
			SaveObject->WorldAssetName = DestinationMapAssetName;
			SaveObject->MapName = GetMapNameFromWorldAssetName(DestinationMapAssetName);
		}
		if (!SaveObject->HasMap(WorldName))
		{
			FSavedMap NewSavedMap;
			NewSavedMap.MapAssetName = WorldName;
			SaveObject->SavedMaps.Add(NewSavedMap);
		}
		
		FSavedMap SavedMap = SaveObject->GetSavedMapWithName(WorldName);
		SavedMap.SavedActors.Empty();
		
		for (FActorIterator It(World); It; ++It)
		{
			AActor* Actor = *It;
			
			if (!IsValid(Actor) || !Actor->Implements<USaveInterface>()) continue;
			
			FSavedActor SavedActor;
			SavedActor.ActorName = Actor->GetFName();
			SavedActor.Transform = Actor->GetActorTransform();
			
			FMemoryWriter MemoryWriter(SavedActor.Bytes);
			
			FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, true);
			Archive.ArIsSaveGame = true;
			
			Actor->Serialize(Archive);
			
			SavedMap.SavedActors.AddUnique(SavedActor);
		}
		
		for (FSavedMap& MapToReplace : SaveObject->SavedMaps)
		{
			if (MapToReplace.MapAssetName == WorldName)
			{
				MapToReplace = SavedMap;
			}
		}
		UGameplayStatics::SaveGameToSlot(SaveObject, AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex);
	}
}

void AAuraGameModeBase::LoadWorldState(UWorld* World) const
{
	FString WorldName =	World->GetMapName();
	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);
	
	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
	check(AuraGameInstance);
	
	if (UGameplayStatics::DoesSaveGameExist(AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex))
	{
		ULoadScreenSaveGame* SaveObject = Cast<ULoadScreenSaveGame>(UGameplayStatics::LoadGameFromSlot(AuraGameInstance->LoadSlotName, AuraGameInstance->LoadSlotIndex));
		if (SaveObject ==  nullptr)
		{
			UE_LOG(LogAura, Error, TEXT("Failed to load save game"));
			return;
		}
		
		for (FActorIterator It(World); It; ++It)
		{
			AActor* Actor = *It;
			
			if (!Actor->Implements<USaveInterface>()) continue;
			
			for (FSavedActor SavedActor : SaveObject->GetSavedMapWithName(WorldName).SavedActors)
			{
				if (SavedActor.ActorName == Actor->GetFName())
				{
					if (ISaveInterface::Execute_ShouldLoadTransform(Actor))
					{
						Actor->SetActorTransform(SavedActor.Transform);
					}
					
					FMemoryReader MemoryReader(SavedActor.Bytes);
					
					FObjectAndNameAsStringProxyArchive Archive(MemoryReader, true);
					Archive.ArIsSaveGame = true;
					Actor->Serialize(Archive);
					
					ISaveInterface::Execute_LoadActor(Actor);
				}
			}
		}
	}
}

void AAuraGameModeBase::TravelToMap(UMVVM_LoadSlot* LoadSlot)
{
	const FString& SlotName = LoadSlot->GetLoadSlotName();
	const int32 SlotIndex = LoadSlot->SlotIndex;
	UGameplayStatics::OpenLevelBySoftObjectPtr(LoadSlot, Maps.FindChecked(LoadSlot->GetMapName()));
}

FString AAuraGameModeBase::GetMapNameFromWorldAssetName(const FString& WorldAssetName) const
{
	for (const auto& Map : Maps)
	{
		if (Map.Value.ToSoftObjectPath().GetAssetName() == WorldAssetName)
		{
			return Map.Key;
		}
	}
	return FString();
}

AActor* AAuraGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(GetGameInstance());
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Actors);
	if (Actors.Num() > 0)
	{
		AActor* SelectedActor = Actors[0];
		for (AActor* Actor : Actors)
		{
			if (APlayerStart* PlayerStart = Cast<APlayerStart>(Actor))
			{
				if (PlayerStart->PlayerStartTag == AuraGameInstance->PlayerStartTag)
				{
					SelectedActor = PlayerStart;
					break;
				}
			}
		}
		return SelectedActor;
	}
	return nullptr;
}

void AAuraGameModeBase::PlayerDied(ACharacter* DeadCharacter)
{
	ULoadScreenSaveGame* SaveObject = RetrieveInGameSaveData();
	if (!SaveObject) return;
	
	UGameplayStatics::OpenLevel(DeadCharacter, FName(SaveObject->WorldAssetName));
}

void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Maps.Add(DefaultMapName, DefaultMap);
}
