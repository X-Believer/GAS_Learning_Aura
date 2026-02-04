// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"


class UGameplayAbility;

UENUM()
enum ESaveSlotStatus
{
	Vacant,
	EnterName,
	Taken
};

USTRUCT()
struct FSavedActor
{
	GENERATED_BODY()
	
	UPROPERTY()
	FName ActorName = FName();
	
	UPROPERTY()
	FTransform Transform = FTransform();
	
	// Serialized Variables from the actor
	UPROPERTY()
	TArray<uint8> Bytes;
};

inline bool operator==(const FSavedActor& Lhs, const FSavedActor& Rhs)
{
	return Lhs.ActorName.IsEqual(Rhs.ActorName);
}

USTRUCT()
struct FSavedMap
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString MapAssetName = FString();
	
	UPROPERTY()
	TArray<FSavedActor> SavedActors;
};

USTRUCT(BlueprintType)
struct FSavedAbility
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ClassDefaults")
	TSubclassOf<UGameplayAbility> GamePlayAbility;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityStatus = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilitySlot = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityType = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AbilityLevel = 1;
};

inline bool operator==(const FSavedAbility& Lhs, const FSavedAbility& Rhs)
{
	return Lhs.AbilityTag.MatchesTagExact(Rhs.AbilityTag);
}
/**
 * 
 */
UCLASS()
class AURA_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	FString SlotName = FString();
	
	UPROPERTY()
	int32 SlotIndex = 0;
	
	UPROPERTY()
	FString PlayerName = FString("Default Name");
	
	UPROPERTY()
	FString MapName = FString("Default Map");
	
	UPROPERTY()
	FString WorldAssetName = FString("Default World Asset Name");
	
	UPROPERTY()
	FName PlayerStartTag;
	
	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = Vacant;
	
	UPROPERTY()
	bool bFirstTimeLoadIn = true;
	
	/* Player */
	
	UPROPERTY()
	int32 PlayerLevel = 1;
	
	UPROPERTY()
	int32 XP = 0;
	
	UPROPERTY()
	int32 AttributePoints = 0;
	
	UPROPERTY()
	int32 SpellPoints = 0;
	
	/* Attributes */
	
	UPROPERTY()
	float Strength = 0.f;
	
	UPROPERTY()
	float Intelligence = 0.f;
	
	UPROPERTY()
	float Resilience = 0.f;
	
	UPROPERTY()
	float Vigor = 0.f;
	
	/* Abilities */
	
	UPROPERTY()
	TArray<FSavedAbility> SavedAbilities;
	
	UPROPERTY()
	TArray<FSavedMap> SavedMaps;
	
	FSavedMap GetSavedMapWithName(const FString& MapAssetName);
	
	bool HasMap(const FString& MapAssetName);
};
