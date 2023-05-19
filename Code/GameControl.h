#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameControl.generated.h"

UCLASS()
class YOURPROJECT_API UGameControl : public UObject
{
    GENERATED_BODY()

public:
    UGameControl();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Control")
    int32 Score;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Control")
    FString SaveFileName;

    UFUNCTION(BlueprintCallable, Category = "Game Control")
    void SaveGame();

    UFUNCTION(BlueprintCallable, Category = "Game Control")
    void LoadGame();
};
