#include "UI/FuSlateUtility.h"

#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/UserInterfaceSettings.h"
#include "Framework/Application/SlateApplication.h"

void UFuSlateUtility::PlaySound(const FSlateSound& Sound)
{
#if !UE_SERVER
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().PlaySound(Sound);
	}
#endif
}

float UFuSlateUtility::GetDpiScale(FVector2D ViewportSize)
{
	const auto* UserInterfaceSettings{GetDefault<UUserInterfaceSettings>()};

	if (!ViewportSize.IsNearlyZero())
	{
		return UserInterfaceSettings->GetDPIScaleBasedOnSize({
			FMath::RoundToInt32(ViewportSize.X),
			FMath::RoundToInt32(ViewportSize.Y)
		});
	}

	if (IsValid(GEngine))
	{
		const auto* World{GEngine->GetWorld()};
		const auto* Viewport{IsValid(World) ? World->GetGameViewport() : GEngine->GameViewport.Get()};

		if (IsValid(Viewport))
		{
			Viewport->GetViewportSize(ViewportSize);

			const auto ViewportDpiScaleInverse{1.0f / Viewport->GetDPIScale()};

			return UserInterfaceSettings->GetDPIScaleBasedOnSize({
				FMath::RoundToInt32(ViewportSize.X * ViewportDpiScaleInverse),
				FMath::RoundToInt32(ViewportSize.Y * ViewportDpiScaleInverse)
			});
		}
	}

	return UserInterfaceSettings->GetDPIScaleBasedOnSize(FIntPoint::ZeroValue);
}
