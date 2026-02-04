// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraEnemySpawnPoint.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Interaction/SaveInterface.h"
#include "AuraEnemySpawnVolume.generated.h"

UCLASS()
class AURA_API AAuraEnemySpawnVolume : public AActor, public ISaveInterface
{
	GENERATED_BODY()
	
public:	
	AAuraEnemySpawnVolume();
	
	/* SaveInterface*/
	virtual void LoadActor_Implementation() override;
	/* End SaveInterface*/
	
	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool bReached = false;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	TArray<AAuraEnemySpawnPoint*> SpawnPoints;
	
private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> Box;

};
