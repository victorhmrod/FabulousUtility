#pragma once

#include "GameplayEffect.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FuEffectUtility.generated.h"

class UFuAbilitySystemComponent;

UCLASS()
class FABULOUSUTILITY_API UFuEffectUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Effect

	UFUNCTION(BlueprintPure, Category = "Fabulous Utility|Fu Effect Utility")
	static const FGameplayTagContainer& GetEffectOwnedTags(TSubclassOf<UGameplayEffect> EffectClass);

	UFUNCTION(BlueprintPure, Category = "Fabulous Utility|Fu Effect Utility")
	static int32 GetEffectStackCountByClass(const UFuAbilitySystemComponent* AbilitySystem, TSubclassOf<UGameplayEffect> EffectClass);

	UFUNCTION(BlueprintPure, Category = "Fabulous Utility|Fu Effect Utility", Meta = (AutoCreateRefTerm = "EffectQuery"))
	static bool HasActiveEffectByQuery(const UFuAbilitySystemComponent* AbilitySystem, const FGameplayEffectQuery& EffectQuery);

	UFUNCTION(BlueprintPure, Category = "Fabulous Utility|Fu Effect Utility", Meta = (AutoCreateRefTerm = "EffectQuery"))
	static void GetActiveEffectsByQuery(const UFuAbilitySystemComponent* AbilitySystem, const FGameplayEffectQuery& EffectQuery,
	                                    TArray<FActiveGameplayEffect>& ActiveEffects);

	UFUNCTION(BlueprintPure, Category = "Fabulous Utility|Fu Effect Utility", Meta = (AutoCreateRefTerm = "EffectTag"))
	static bool HasActiveEffectWithTag(const UFuAbilitySystemComponent* AbilitySystem, const FGameplayTag& EffectTag,
	                                   bool bIgnoreInhibitedEffects = false);

	UFUNCTION(BlueprintPure, Category = "Fabulous Utility|Fu Effect Utility", Meta = (AutoCreateRefTerm = "EffectTags"))
	static bool HasActiveEffectWithAnyTags(const UFuAbilitySystemComponent* AbilitySystem, const FGameplayTagContainer& EffectTags,
	                                       bool bIgnoreInhibitedEffects = false);

	UFUNCTION(BlueprintPure, Category = "Fabulous Utility|Fu Effect Utility", Meta = (AutoCreateRefTerm = "EffectTag"))
	static int32 GetEffectsCountWithTag(const UFuAbilitySystemComponent* AbilitySystem, const FGameplayTag& EffectTag,
	                                    bool bIgnoreInhibitedEffects = false);

	UFUNCTION(BlueprintPure, Category = "Fabulous Utility|Fu Effect Utility", Meta = (AutoCreateRefTerm = "EffectTags"))
	static int32 GetEffectsCountWithAnyTags(const UFuAbilitySystemComponent* AbilitySystem, const FGameplayTagContainer& EffectTags,
	                                        bool bIgnoreInhibitedEffects = false);

	static const FActiveGameplayEffect* GetActiveEffectTimeRemainingAndDurationByTag(
		const UFuAbilitySystemComponent* AbilitySystem, const FGameplayTag& EffectTag, float& TimeRemaining, float& Duration);

	UFUNCTION(BlueprintCallable, Category = "Fabulous Utility|Fu Effect Utility",
		Meta = (AutoCreateRefTerm = "EffectTag", ExpandBoolAsExecs = "ReturnValue"))
	static bool TryGetEffectTimeRemainingAndDurationByTag(
		const UFuAbilitySystemComponent* AbilitySystem, const FGameplayTag& EffectTag, float& TimeRemaining, float& Duration);

	// Effect Handle

	UFUNCTION(BlueprintPure, Category = "Fabulous Utility|Fu Effect Utility")
	static bool IsEffectActive(FActiveGameplayEffectHandle EffectHandle);

	UFUNCTION(BlueprintCallable, Category = "Fabulous Utility|Fu Effect Utility", Meta = (ExpandBoolAsExecs = "ReturnValue"))
	static bool SwitchIsEffectActive(FActiveGameplayEffectHandle EffectHandle);

	UFUNCTION(BlueprintCallable, Category = "Fabulous Utility|Fu Effect Utility")
	static void RemoveActiveEffect(FActiveGameplayEffectHandle EffectHandle, int32 StacksToRemove = -1);

	UFUNCTION(BlueprintCallable, Category = "Fabulous Utility|Fu Effect Utility")
	static void RemoveActiveEffects(const TArray<FActiveGameplayEffectHandle>& EffectHandles, int32 StacksToRemove = -1);

	UFUNCTION(BlueprintCallable, Category = "Fabulous Utility|Fu Effect Utility")
	static void RecalculateEffectModifiers(FActiveGameplayEffectHandle EffectHandle);

	UFUNCTION(BlueprintCallable, Category = "Fabulous Utility|Fu Effect Utility", Meta = (ExpandBoolAsExecs = "ReturnValue"))
	static bool TryGetEffectTimeRemainingAndDurationByHandle(FActiveGameplayEffectHandle EffectHandle,
	                                                         float& TimeRemaining, float& Duration);

	// This function will also restart the effect timer from the beginning. If you just want to modify the remaining
	// effect time, use UFuEffectUtility::SetEffectTimeRemaining() or UFuEffectUtility::IncreaseEffectTimeRemaining().
	UFUNCTION(BlueprintCallable, Category = "Fabulous Utility|Fu Effect Utility")
	static void SetEffectDuration(FActiveGameplayEffectHandle EffectHandle, float Duration);

	UFUNCTION(BlueprintCallable, Category = "Fabulous Utility|Fu Effect Utility")
	static void SetEffectTimeRemaining(FActiveGameplayEffectHandle EffectHandle, float TimeRemaining);

	UFUNCTION(BlueprintCallable, Category = "Fabulous Utility|Fu Effect Utility")
	static void IncreaseEffectTimeRemaining(FActiveGameplayEffectHandle EffectHandle, float AdditionalTimeRemaining);
};
