// Tested on UE 4.27.2

#pragma once

#include "Slate/SlateBrushAsset.h"  // Only needed if using DrawBox

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

UCLASS()
class EXAMPLE_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMyUserWidget(const FObjectInitializer& ObjectInitializer);
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

private:
	USlateBrushAsset* MyBrushAsset = nullptr;  // Only needed if using DrawBox
	const int RESOLUTION_WIDTH = 1920;  // Use native resolution for packaged build
	const int RESOLUTION_HEIGHT = 1080;  // Use native resolution for packaged build
};