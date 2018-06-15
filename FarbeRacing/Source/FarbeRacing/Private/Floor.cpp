// Copyright Conner Linskens 2018

#include "Floor.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInterface.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

#define OUT


// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();

	PlayerCar = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto LocationChange = -DefaultSpeed * GetWorld()->DeltaTimeSeconds;
	auto NewLocation = GetActorLocation().X + LocationChange;
	SetActorRelativeLocation(FVector(NewLocation, GetActorLocation().Y, GetActorLocation().Z));
}

void AFloor::DestroyStaticMesh()
{
	PlayerCar->GetRootComponent()->DestroyComponent(true);
}




