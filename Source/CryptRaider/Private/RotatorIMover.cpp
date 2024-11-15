// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatorIMover.h"

// Sets default values for this component's properties
URotatorIMover::URotatorIMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URotatorIMover::BeginPlay()
{
	Super::BeginPlay();
	if(DoorMesh == nullptr) return;

	OriginalRotation = DoorMesh->GetRelativeRotation();
	
}


// Called every frame
void URotatorIMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(DoorMesh == nullptr) return;
	
	FRotator CurrentRotation = DoorMesh->GetRelativeRotation();
	FRotator TargetRotation = OriginalRotation;
	int direction = IsReverse ? -1 : 1;
	if (ShouldMove)
	{
		TargetRotation = OriginalRotation + (MoveOffset * direction);
	}else
	{
		TargetRotation = OriginalRotation;
	}
	if(abs(TargetRotation.Vector().Length() - CurrentRotation.Vector().Length()) > 0.1 ) return;
	float Speed = MoveOffset.Vector().Length()/ MoveTime;
	FRotator NewRotation = FMath::Lerp(CurrentRotation, TargetRotation, Speed);
	DoorMesh->SetRelativeRotation(NewRotation);
}
void URotatorIMover::SetDoorMesh(UStaticMeshComponent* mesh)
{
	DoorMesh = mesh;
}

void URotatorIMover::SetShouldMove(bool bShouldMove)
{
	ShouldMove = bShouldMove;
}


