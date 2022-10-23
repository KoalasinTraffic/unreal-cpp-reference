// Tested on UE 4.27.2

#include "MyUserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

UMyUserWidget::UMyUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Reference path to Slate Brush copied from unreal if using DrawBox
	static ConstructorHelpers::FObjectFinder<USlateBrushAsset> BrushAsset(TEXT("SlateBrushAsset'/Game/Materials/MySlateBrushAsset.MySlateBrushAsset'"));
	if (BrushAsset.Succeeded())
		MyBrushAsset = BrushAsset.Object;
}

// Overriding NativePaint is like overriding OnPaint for blueprints
// These examples will draw lines, shapes, or images to indictate where actors are when outside screen
int32 UMyUserWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (IsInViewport())  // Draw only when in use, not in editor
	{
		FPaintContext Context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

		FVector2D ScreenPosition;
		int32 SizeX, SizeY;

		// Writes to SizeX and SizeY the viewport scaling
		GetOwningPlayer()->GetViewportSize(SizeX, SizeY);

		TArray<AActor*> ActorsToFind;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsToFind);  // Should change AActor to actor type of interest
		for (AActor* MyActor : ActorsToFind)
		{
			// Writes to ScreenPosition the widget location relative to the actor location
			UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), MyActor->GetActorLocation(), ScreenPosition, true);

			// Draw only if actor is out of widget's sight
			// Can be split into multiple conditionals for location dependent indicator drawings
			if (ScreenPosition.X < 0 || ScreenPosition.X > RESOLUTION_WIDTH || ScreenPosition.Y < 0 || ScreenPosition.Y > RESOLUTION_HEIGHT)
			{
				// Convert screen location to viewport location
				// This does NOT always work with play in editor, but works with packaged build
				ScreenPosition.X *= RESOLUTION_WIDTH / SizeX;
				ScreenPosition.Y *= RESOLUTION_HEIGHT / SizeY;

				// Bind position to the edge of screen
				ScreenPosition.X = FMath::Max(FMath::Min(int(ScreenPosition.X), RESOLUTION_WIDTH), 0);
				ScreenPosition.Y = FMath::Max(FMath::Min(int(ScreenPosition.Y), RESOLUTION_HEIGHT), 0);

                                // Multiple examples of drawing on HUD is provided below

				// Example 1: Draw image as an indicator with specified position and size with no tint (white)
				if (MyBrushAsset)
					UWidgetBlueprintLibrary::DrawBox(Context, ScreenPosition, FVector2D(50, 50), MyBrushAsset, FLinearColor::White);

				// Example 2: Draw X with blue lines and thickness of one
				UWidgetBlueprintLibrary::DrawLine(Context, ScreenPosition + FVector2D(-10, -10), ScreenPosition + FVector2D(10, 10), FLinearColor::Blue, true, 1);
				UWidgetBlueprintLibrary::DrawLine(Context, ScreenPosition + FVector2D(-10, 10), ScreenPosition + FVector2D(10, -10), FLinearColor::Blue, true, 1);

				// Example 3: Draw triangle with red lines and thickness of one
				TArray<FVector2D> Points = {
					ScreenPosition + FVector2D(0, -20),
					ScreenPosition + FVector2D(-20, 10),
					ScreenPosition + FVector2D(20, 10),
					ScreenPosition + FVector2D(0, -20),
				};
				UWidgetBlueprintLibrary::DrawLines(Context, Points, FLinearColor::Red, true, 1);
			}
		}
	}

	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}
