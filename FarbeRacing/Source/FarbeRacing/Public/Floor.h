// Copyright Conner Linskens 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Floor.generated.h"

class ACar;

UCLASS()
class FARBERACING_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DestroyStaticMesh();

	UFUNCTION(BlueprintCallable)
	bool CheckForCar(AActor* ActorToCheck) const;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<ACar> carblueprint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	ACar* PlayerCar = nullptr;

};
