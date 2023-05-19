#include "GameControl.h"
#include "Kismet/GameplayStatics.h"

UGameControl::UGameControl()
{
    Score = 0;
    SaveFileName = "GameSave";
}

void UGameControl::SaveGame()
{
    UGameplayStatics::SaveGameToSlot(this, SaveFileName, 0);
}

void UGameControl::LoadGame()
{
    UGameplayStatics::LoadGameFromSlot(SaveFileName, 0);
}
