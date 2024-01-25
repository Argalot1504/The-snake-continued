// Fill out your copyright notice in the Description page of Project Settings.


#include "Slowingdown.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.h"

// Sets default values
ASlowingdown::ASlowingdown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASlowingdown::BeginPlay()
{
	Super::BeginPlay();
	DecreaseSpeed = 0.9f;
}

// Called every frame
void ASlowingdown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlowingdown::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->BufferTime = 0;
			Snake->SetActorTickInterval(DecreaseSpeed);
			Destroy();


		}
	}
}