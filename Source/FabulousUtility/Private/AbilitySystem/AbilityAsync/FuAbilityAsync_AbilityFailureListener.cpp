#include "AbilitySystem/AbilityAsync/FuAbilityAsync_AbilityFailureListener.h"

#include "AbilitySystemGlobals.h"
#include "FuMacros.h"
#include "AbilitySystem/FuAbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FuAbilityAsync_AbilityFailureListener)

UFuAbilityAsync_AbilityFailureListener* UFuAbilityAsync_AbilityFailureListener::FuListenForAbilityFailureOnActor(
	const AActor* Actor, const FGameplayTag AbilityTag, const FGameplayTagContainer FailureTags)
{
	return FuListenForAbilityFailure(
		Cast<UFuAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor)),
		AbilityTag, FailureTags);
}

UFuAbilityAsync_AbilityFailureListener* UFuAbilityAsync_AbilityFailureListener::FuListenForAbilitiesFailureOnActor(
	const AActor* Actor, const FGameplayTagContainer AbilityTags, const FGameplayTagContainer FailureTags)
{
	return FuListenForAbilitiesFailure(
		Cast<UFuAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor)),
		AbilityTags, FailureTags);
}

UFuAbilityAsync_AbilityFailureListener* UFuAbilityAsync_AbilityFailureListener::FuListenForAbilityFailure(
	UFuAbilitySystemComponent* AbilitySystem, const FGameplayTag AbilityTag, const FGameplayTagContainer FailureTags)
{
	auto* Task{NewObject<ThisClass>()};

	Task->SetAbilitySystemComponent(AbilitySystem);

	if (AbilityTag.IsValid())
	{
		Task->AbilityTags1.AddTag(AbilityTag);
	}

	for (const auto& Tag : FailureTags)
	{
		if (FU_ENSURE(Tag.IsValid()))
		{
			Task->FailureTags1.AddTag(Tag);
		}
	}

	return Task;
}

UFuAbilityAsync_AbilityFailureListener* UFuAbilityAsync_AbilityFailureListener::FuListenForAbilitiesFailure(
	UFuAbilitySystemComponent* AbilitySystem, const FGameplayTagContainer AbilityTags, const FGameplayTagContainer FailureTags)
{
	auto* Task{NewObject<ThisClass>()};

	Task->SetAbilitySystemComponent(AbilitySystem);

	for (const auto& Tag : AbilityTags)
	{
		if (FU_ENSURE(Tag.IsValid()))
		{
			Task->AbilityTags1.AddTag(Tag);
		}
	}

	for (const auto& Tag : FailureTags)
	{
		if (FU_ENSURE(Tag.IsValid()))
		{
			Task->FailureTags1.AddTag(Tag);
		}
	}

	return Task;
}

void UFuAbilityAsync_AbilityFailureListener::Activate()
{
	Super::Activate();

	auto* AbilitySystem{Cast<UFuAbilitySystemComponent>(GetAbilitySystemComponent())};

	if (!IsValid(GetAbilitySystemComponent()) || !FU_ENSURE(IsValid(AbilitySystem)))
	{
		EndAction();
		return;
	}

	AbilitySystem->OnAbilityFailed.AddUObject(this, &ThisClass::AbilitySystem_OnAbilityFailed);
}

void UFuAbilityAsync_AbilityFailureListener::EndAction()
{
	auto* AbilitySystem{Cast<UFuAbilitySystemComponent>(GetAbilitySystemComponent())};
	if (IsValid(AbilitySystem))
	{
		AbilitySystem->OnAbilityFailed.RemoveAll(this);
	}

	Super::EndAction();
}

void UFuAbilityAsync_AbilityFailureListener::AbilitySystem_OnAbilityFailed(const FGameplayAbilitySpecHandle AbilityHandle,
                                                                           // ReSharper disable once CppParameterMayBeConstPtrOrRef
                                                                           UGameplayAbility* Ability,
                                                                           const FGameplayTagContainer& FailureTags) const
{
	const auto* AbilitySpecification{GetAbilitySystemComponent()->FindAbilitySpecFromHandle(AbilityHandle)};

	if (FailureTags.HasAny(FailureTags1) &&
	    (Ability->AbilityTags.HasAny(AbilityTags1) ||
	     // ReSharper disable once CppRedundantParentheses
	     (AbilitySpecification != nullptr && AbilitySpecification->DynamicAbilityTags.HasAny(AbilityTags1))))
	{
		OnAbilityFailed.Broadcast(AbilityHandle, FailureTags);
	}
}
