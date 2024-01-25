// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "GameFramework/Actor.h"
#include "Boost.generated.h"

class UStaticMeshComponent;

UCLASS()
class SNAKE_API ABoost : public ABonusBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoost();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float IncreaseSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;
};
