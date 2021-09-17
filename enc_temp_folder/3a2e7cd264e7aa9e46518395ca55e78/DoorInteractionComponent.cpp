// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	//v1
	//DesiredRotation = FRotator(0.0f, 90.0f, 0.0f);
	//DeltaRotation = DesiredRotation - GetOwner()->GetActorRotation();
	//FinalRotation = DesiredRotation + GetOwner()->GetActorRotation();
	////GetOwner()->SetActorRotation(DesiredRotation);

	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
	CurrentRotationTime = 0.0f;
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//v1
	/*FRotator CurrentRotation = GetOwner()->GetActorRotation();
	if (!CurrentRotation.Equals(FinalRotation, 5.0f))
	{
		CurrentRotation += DeltaRotation * DeltaTime;
		GetOwner()->SetActorRotation(CurrentRotation);
	}*/ 

	if (CurrentRotationTime < TimeToRotate)
	{
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstPlayerController())
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
			{
				CurrentRotationTime += DeltaTime;
				const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
			}

			if (PlayerPawn && TriggerBoxBack->IsOverlappingActor(PlayerPawn))
			{
				CurrentRotationTime += DeltaTime;
				const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation*-1, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
			}
		}
	}
}

