// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/Image.h" 
#include "Components/Widget.h" 
#include "UObject/NoExportTypes.h"
#include "CarPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FARBERACING_API ACarPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private: 
	void ArrowKeyRedHidden() const;
	void ArrowKeyRedVisible() const;
	void ArrowKeyBlueHidden() const;
	void ArrowKeyBlueVisible() const;
	void ArrowKeyYellowHidden() const;
	void ArrowKeyYellowVisible() const;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
