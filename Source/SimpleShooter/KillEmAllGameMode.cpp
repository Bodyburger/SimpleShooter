// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    // For loop over ShooterAI in World:
    for (AShooterAIController* ShooterAIController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!ShooterAIController->IsDead())
        {
            return;
        }
    }

    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);

        // if (bIsPlayerWinner && Controller->IsPlayerController())
        // {
        //     Controller->GameHasEnded(nullptr, true);
        // }

        // else if (!bIsPlayerWinner && !Controller->IsPlayerController())
        // {
        //     Controller->GameHasEnded(Controller->GetParentActor(), true);
        // }

        // else 
        // {
        //     Controller->GameHasEnded(nullptr, false);
        // }
    }
}