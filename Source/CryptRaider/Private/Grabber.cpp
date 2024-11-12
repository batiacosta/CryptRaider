// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr) return;

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Releasing grabber"));
}
void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr) return;
	
	FVector StartLine = GetComponentLocation();
	FVector EndLine = StartLine + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), StartLine, EndLine, FColor::Red, false);
	DrawDebugSphere(GetWorld(), EndLine, 10, 10, FColor::Blue, false, 5);
	FCollisionShape SphereCollision = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		StartLine, EndLine,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		SphereCollision
		);
	if(HasHit)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No actor hit"));
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	}
	return Result;
}




