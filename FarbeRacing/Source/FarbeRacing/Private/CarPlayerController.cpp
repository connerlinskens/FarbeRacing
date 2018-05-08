// Fill out your copyright notice in the Description page of Project Settings.

#include "CarPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"


void ACarPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ACarPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsInputKeyDown("Left"))
	{
		ArrowKeyRedHidden();
	}
	else
	{
		ArrowKeyRedVisible();
	}

	if (IsInputKeyDown("Up"))
	{
		ArrowKeyBlueHidden();
	}
	else
	{
		ArrowKeyBlueVisible();
	}

	if (IsInputKeyDown("Right"))
	{
		ArrowKeyYellowHidden();
	}
	else 
	{
		ArrowKeyYellowVisible();
	}
}

void ACarPlayerController::ArrowKeyRedHidden() const
{
	UE_LOG(LogTemp, Warning, TEXT("RED HIDDEN"));
}

void ACarPlayerController::ArrowKeyRedVisible() const
{
	UE_LOG(LogTemp, Warning, TEXT("RED VISIBLE"));
}

void ACarPlayerController::ArrowKeyBlueHidden() const
{
	UE_LOG(LogTemp, Warning, TEXT("BLUE HIDDEN"));
}

void ACarPlayerController::ArrowKeyBlueVisible() const
{
	UE_LOG(LogTemp, Warning, TEXT("BLUE VISIBLE"));
}

void ACarPlayerController::ArrowKeyYellowHidden() const
{
	UE_LOG(LogTemp, Warning, TEXT("YELLOW HIDDEN"));
}

void ACarPlayerController::ArrowKeyYellowVisible() const
{
	UE_LOG(LogTemp, Warning, TEXT("YELLOW VISIBLE"));
}

