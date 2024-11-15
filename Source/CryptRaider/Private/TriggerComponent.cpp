// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	
}
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFuntion)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFuntion);
	if(Mover == nullptr) return;
	AActor* OverlappingActor = GetAdmittedActor();
	if (OverlappingActor != nullptr)
	{
		UPrimitiveComponent* Component =  Cast<UPrimitiveComponent>(OverlappingActor->GetRootComponent());
		if(Component != nullptr)
		{
			Component->SetSimulatePhysics(false);
		}
		OverlappingActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else
	{
		if(Mover == nullptr) return;
		Mover->SetShouldMove(false);
	}
}
void UTriggerComponent::SetMover(TScriptInterface<IIMover> ComingMover)
{
	Mover = ComingMover;
}

AActor* UTriggerComponent::GetAdmittedActor() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for(AActor* OverlappingActor : OverlappingActors)
	{
		FString OverlappingActorName = OverlappingActor->GetName();
		bool HasAdmittedTag = OverlappingActor->ActorHasTag(AdmittedTag);
		bool IsGrabbed = OverlappingActor->ActorHasTag("Grabbed");
		if (HasAdmittedTag && !IsGrabbed)
		{
			return OverlappingActor;
		}
	}
	return nullptr;
}

