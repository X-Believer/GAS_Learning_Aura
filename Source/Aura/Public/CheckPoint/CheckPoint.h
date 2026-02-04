// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Aura/Aura.h"
#include "GameFramework/PlayerStart.h"
#include "Interaction/HighlightInterface.h"
#include "Interaction/SaveInterface.h"
#include "CheckPoint.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class AURA_API ACheckPoint : public APlayerStart, public ISaveInterface, public IHighlightInterface
{
	GENERATED_BODY()
	
public:
	ACheckPoint(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	bool bReached = false;
	
	UPROPERTY(EditAnywhere)
	bool bBindOverlapCallback = true;
	
	/* Save interface */
	virtual bool ShouldLoadTransform_Implementation() override;
	virtual void LoadActor_Implementation() override;
	/* End save interface */	
	
protected:
	
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void BeginPlay() override;
	
	/* Highlight interface */
	virtual void SetMoveToLocation_Implementation(FVector& OutDestination) override;
	virtual void HighlightActor_Implementation() override;
	virtual void UnHighlightActor_Implementation() override;
	/* Unhighlight interface*/
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> MoveToComponent;
	
	UPROPERTY(EditDefaultsOnly)
	int32 CustomDepthStencilOverride = CUSTOM_DEPTH_TAN;
	
	UFUNCTION(BlueprintImplementableEvent)
	void CheckPointReached(UMaterialInstanceDynamic* DynamicMaterialInstance);
	
	UFUNCTION(BlueprintCallable)
	void HandleGlowEffects();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> CheckPointMesh;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
};
