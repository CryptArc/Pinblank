// Copyright Alain SHAKOUR 2016 contact@alainshakour.com This software is a computer program whose purpose is entertainment.This software is governed by the CeCILL-C license under French law and abiding by the rules of distribution of free software.  You can  use, modify and/ or redistribute the software under the terms of the CeCILL-C license as circulated by CEA, CNRS and INRIA at the following URL "http://www.cecill.info". As a counterpart to the access to the source code and  rights to copy, modify and redistribute granted by the license, users are provided only with a limited warranty  and the software's author,  the holder of the economic rights,  and the successive licensors  have only  limited liability. In this respect, the user's attention is drawn to the risks associated with loading,  using,  modifying and/or developing or reproducing the software by the user in light of its specific status of free software, that may mean  that it is complicated to manipulate,  and  that  also therefore means  that it is reserved for developers  and  experienced professionals having in-depth computer knowledge. Users are therefore encouraged to load and test the software's suitability as regards their requirements in conditions enabling the security of their systems and/or data to be ensured and,  more generally, to use and operate it in the same conditions as regards security. The fact that you are presently reading this means that you have had knowledge of the CeCILL-C license and that you accept its terms.

#include "Pinblank.h"
#include "PushCylinder.h"

APushCylinder::APushCylinder()
{
	PrimaryActorTick.bCanEverTick = false;
	// Collider to detect ball position
	UCapsuleComponent* capsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	capsuleCollider->SetCapsuleSize(5, 44);
	RootComponent = capsuleCollider;
	capsuleCollider->SetWorldScale3D(FVector(0.08));
	capsuleCollider->bGenerateOverlapEvents = true;

	// Background plane mesh
	boxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	boxMesh->AttachTo(capsuleCollider);
	boxMesh->bGenerateOverlapEvents = false;
	boxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	boxMesh->SetCollisionProfileName(TEXT("OverlapAll"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> boxVisualAsset(TEXT("/Game/Meshes/Shape_Plane.Shape_Plane"));
	if (boxVisualAsset.Succeeded())
	{
		boxMesh->SetStaticMesh(boxVisualAsset.Object);
		boxMesh->SetRelativeLocation(FVector(2 , 0, 0));
		boxMesh->SetRelativeRotation(FRotator(90, 0, 0));
		boxMesh->SetRelativeScale3D(FVector(1, 0.1, 1));

		static ConstructorHelpers::FObjectFinder<UMaterial> MaterialResource(TEXT("/Game/Materials/M_MasterEnemy.M_MasterEnemy"));
		if (MaterialResource.Succeeded())
		{
			boxMesh->SetMaterial(0, MaterialResource.Object);
		}
	}
}

void APushCylinder::BeginPlay()
{
	Super::BeginPlay();
}

void APushCylinder::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	IColorChangeable::InitializeDynamicMaterialInstance(this);
	ChangeColor(FLinearColor(1, 0, 0));
}

// // Add some impulse on player interact
void APushCylinder::StartFirstInteraction(ABall* ball) {
	ball->AddSphereImpulse(this, FVector(0, -BALL_IMPULSE,0));
}

void APushCylinder::StopFirstInteraction(ABall* ball) {
}

void APushCylinder::StartSecondInteraction(ABall* ball)
{
}

void APushCylinder::StopSecondInteraction(ABall* ball)
{
}

UStaticMeshComponent* APushCylinder::GetColoredMesh()
{
	return boxMesh;
}

const FName APushCylinder::GetMaterialParameterColorName() const
{
	return TEXT("ParamColor");
}
