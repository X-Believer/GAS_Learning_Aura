// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"


class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();
	
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite)
	FRotator CalculatedRotation;
	
	UPROPERTY(BlueprintReadWrite)
	FVector CalculatedLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickUp Movement")
	bool bRotate = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickUp Movement")
	float RotationRate = 45.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickUp Movement")
	bool bSinusoidalMovement = false;
	
	UFUNCTION(BlueprintCallable)
	void StartSinusoidalMovement();
	
	UFUNCTION(BlueprintCallable)
	void StartRotation();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickUp Movement")
	float SineAmplitude = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickUp Movement")
	float SinePeriodConstant = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickUp Movement")
	FVector InitialLocation;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	bool bDestroyOnEffectApplication = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	bool bApplyEffectToEnemies = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Applied Effects")
	float ActorLevel = 1.f;
	
private:
	
	float RunningTime = 0.f;
	
	void ItemMovement(float DeltaTime);
};