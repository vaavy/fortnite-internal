#include "Defines.h"
#include "Client.h"

void CheatLoop()
{
	GWorld* WorldIndex = *(GWorld**)(Client::ImageBase + 0x102f69d8);
	UGameInstance* GameInstanceIndex = WorldIndex->OwningGameInstance();
	ULocalPlayers* LocalPlayersIndex = GameInstanceIndex->LocalPlayers();
	ULocalPlayer* LocalPlayerIndex = LocalPlayersIndex->LocalPlayer();
	APlayerController* PlayerControllerIndex = LocalPlayerIndex->PlayerController();
	APlayerCameraManager* PlayerCameraManagerIndex = PlayerControllerIndex->PlayerCameraManager();
	AFortPawn* AcknowledgedPawnIndex = PlayerControllerIndex->LocalPawn();

	auto LevelsIndex = WorldIndex->Levels();

	if (!LevelsIndex.Num())
		return;

	for (int levelIndex = 0; levelIndex != LevelsIndex.Num(); levelIndex++)
	{
		auto level = LevelsIndex[levelIndex];
		if (!level)
			return;

	}
}