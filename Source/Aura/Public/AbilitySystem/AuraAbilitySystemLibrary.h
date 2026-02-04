// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/SpellMenuWidgetController.h"
#include "AuraAbilitySystemLibrary.generated.h"

class ULootTiers;
class ULoadScreenSaveGame;
class UAttributeMenuWidgetController;
class UAbilitySystemComponent;
class UOverlayWidgetController;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class AURA_API 
UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	/* WidgetController */
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController", meta=(DefaultToSelf = "WorldContextObject"))
	static bool MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AAuraHUD*& OutAuraHUD);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController", meta=(DefaultToSelf = "WorldContextObject"))
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController", meta=(DefaultToSelf = "WorldContextObject"))
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|WidgetController", meta=(DefaultToSelf = "WorldContextObject"))
	static USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WorldContextObject);
	
	/* Class Default*/
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributesFromSaveData(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ULoadScreenSaveGame* SaveGame);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartUpAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static UAbilityInfo* GetAbilityInfo(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults", meta=(DefaultToSelf = "WorldContextObject"))
	static ULootTiers* GetLootTiers(const UObject* WorldContextObject);
	
	/* Effect context Getter */
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static bool IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static float GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static FVector GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static FVector GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static float GetRadialDamageInnerRadius(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static FVector GetRadialDamageOrigin(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static float GetRadialDamageOuterRadius(const FGameplayEffectContextHandle& EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static bool IsRadialDamage(const FGameplayEffectContextHandle& EffectContextHandle);
	
	/* Effect context Setter */
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetIsSuccessfulDebuff(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsSuccessfulDebuff);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDamage);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffDuration);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDebuffFrequency);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetDamageType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InDeathImpulse);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetKnockbackForce(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InKnockbackForce);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetRadialDamageOrigin(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, const FVector& InRadialDamageOrigin);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetRadialDamageInnerRadius(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InRadialDamageInnerRadius);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetRadialDamageOuterRadius(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InRadialDamageOuterRadius);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayEffect")
	static void SetIsRadialDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsRadialDamage);
	
	/* Mechanics */
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayerWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*> ActorsToIgnore, float Radius, const FVector SphereOrigin);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static void GetClosestTarget(int32 MaxTargets, const TArray<AActor*>& Actors, TArray<AActor*>& OutClosestTargets, const FVector& Origin);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static bool IsFriend(AActor* FirstActor, AActor* SecondActor);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static TArray<FRotator> EvenlySpacedRotator(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators);
	
	UFUNCTION(BlueprintPure, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static TArray<FVector> EvenlyRotatedVectors(const FVector& Forward, const FVector& Axis, float Spread, int32 NumVectors);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|GameplayMechanics")
	static int32 GetXPRewardForClassAndLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel);
	
	/*
	 * DamageEffectParams
	 */
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|DamageEffect")
	static void SetIsRadialDamageEffectParam(UPARAM(ref) FDamageEffectParams& DamageEffectParams, bool bIsRadial, float InnerRadius, float OuterRadius, FVector Origin);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|DamageEffect")
	static void SetKnockbackDirection(UPARAM(ref) FDamageEffectParams& DamageEffectParams, FVector KnockbackDirection, float Magnitude = 0.f);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|DamageEffect")
	static void SetDeathImpulseDirection(UPARAM(ref) FDamageEffectParams& DamageEffectParams, FVector DeathImpulseDirection, float Magnitude = 0.f);
	
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|DamageEffect")
	static void SetTargetEffectParamsASC(UPARAM(ref) FDamageEffectParams& DamageEffectParams, UAbilitySystemComponent* InASC);
};
