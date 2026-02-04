// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoadScreenSaveGame.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class ULootTiers;
class USaveGame;
class UMVVM_LoadSlot;
class UAbilityInfo;
class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
	
	UPROPERTY(EditDefaultsOnly, Category="AbilityInfo")
	TObjectPtr<UAbilityInfo> AbilityInfo;
	
	UPROPERTY(EditDefaultsOnly, Category="LootTier")
	TObjectPtr<ULootTiers> LootTiers;

	void SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex); 
	
	ULoadScreenSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const;
	
	static void DeleteSlot(const FString& SlotName, int32 SlotIndex);
	
	ULoadScreenSaveGame* RetrieveInGameSaveData();
	
	void SaveInGameProgressData(ULoadScreenSaveGame* SaveObject);
	
	void SaveWorldState(UWorld* World, const FString& DestinationMapAssetName = FString("")) const;
	
	void LoadWorldState(UWorld* World) const;
	
	void TravelToMap(UMVVM_LoadSlot* LoadSlot);
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> LoadScreenSaveGameClass;
	
	UPROPERTY(EditDefaultsOnly)
	FString DefaultMapName;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DefaultMap;
	
	UPROPERTY(EditDefaultsOnly)
	FName DefaultPlayerStartTag;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;
	
	FString GetMapNameFromWorldAssetName(const FString& WorldAssetName) const;
	
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
	void PlayerDied(ACharacter* DeadCharacter);
	
protected:
	virtual void BeginPlay() override;
};
