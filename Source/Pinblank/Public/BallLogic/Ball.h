// Copyright Alain SHAKOUR 2016 contact@alainshakour.com This software is a computer program whose purpose is entertainment.This software is governed by the CeCILL-C license under French law and abiding by the rules of distribution of free software.  You can  use, modify and/ or redistribute the software under the terms of the CeCILL-C license as circulated by CEA, CNRS and INRIA at the following URL "http://www.cecill.info". As a counterpart to the access to the source code and  rights to copy, modify and redistribute granted by the license, users are provided only with a limited warranty  and the software's author,  the holder of the economic rights,  and the successive licensors  have only  limited liability. In this respect, the user's attention is drawn to the risks associated with loading,  using,  modifying and/or developing or reproducing the software by the user in light of its specific status of free software, that may mean  that it is complicated to manipulate,  and  that  also therefore means  that it is reserved for developers  and  experienced professionals having in-depth computer knowledge. Users are therefore encouraged to load and test the software's suitability as regards their requirements in conditions enabling the security of their systems and/or data to be ensured and,  more generally, to use and operate it in the same conditions as regards security. The fact that you are presently reading this means that you have had knowledge of the CeCILL-C license and that you accept its terms.

#pragma once

#include "GameFramework/Pawn.h"
#include "Ball.generated.h"

UCLASS()
class PINBLANK_API ABall : public APawn
{
	GENERATED_BODY()

	bool bIsInteracted = false;
	const int SPHERE_RADIUS = 32;

	USphereComponent* sphereCollider;
	UStaticMeshComponent* sphereMesh;

	ABall();
	void FlipperStartFirstAction();
	void FlipperStopFirstAction();
	void FlipperStartSecondAction();
	void FlipperStopSecondAction();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void ChangeActionableColor(AActor* Actor, FLinearColor color);

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	const UStaticMeshComponent* GetSphereMeshComponent() const;
	void AddSphereImpulse(AActor* OtherActor, FVector force);

	UPROPERTY(EditAnywhere)
		int maxSpeed = 600;

	UPROPERTY(Category = "Init", EditAnywhere, BlueprintReadOnly)
		bool isPhysicsActivated = true;

	UFUNCTION(BlueprintCallable, Category = "Init")
		void ActivatePhysics();
};
