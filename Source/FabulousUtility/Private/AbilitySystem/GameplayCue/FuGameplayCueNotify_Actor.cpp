#include "AbilitySystem/GameplayCue/FuGameplayCueNotify_Actor.h"

#include "TimerManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FuGameplayCueNotify_Actor)

void AFuGameplayCueNotify_Actor::HandleGameplayCue(AActor* Target, const EGameplayCueEvent::Type EventType,
                                                   const FGameplayCueParameters& Parameters)
{
	// ReSharper disable CppRedundantParentheses
	if ((EventType == EGameplayCueEvent::OnActive && (bAllowMultipleOnActiveEvents || !bHasHandledOnActiveEvent)) ||
	    (EventType == EGameplayCueEvent::WhileActive && (bAllowMultipleWhileActiveEvents || !bHasHandledWhileActiveEvent)))
	// ReSharper restore CppRedundantParentheses
	{
		bHasHandledOnRemoveEvent = false;

		GetWorldTimerManager().ClearTimer(FinishTimerHandle);
	}

	Super::HandleGameplayCue(Target, EventType, Parameters);
}
