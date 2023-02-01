#pragma once

#include "Engine/DeveloperSettings.h"
#include "FuEditorSettings.generated.h"

UCLASS(Config = "EditorPerProjectUserSettings")
class FABULOUSEDITOR_API UFuEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Editor", Config)
	bool bApplyEditorScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Editor", Config,
		Meta = (ClampMin = 0.5, ClampMax = 2, EditCondition = "bApplyEditorScale", ForceUnits = "x"))
	float EditorScale{1.0f};

public:
	UFuEditorSettings();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual FText GetSectionText() const override;
#endif
};
