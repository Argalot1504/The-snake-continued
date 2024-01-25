// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "GameFramework/Actor.h"
#include "Slowingdown.generated.h"

UCLASS()
class SNAKE_API ASlowingdown : public ABonusBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlowingdown();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float DecreaseSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;
};
