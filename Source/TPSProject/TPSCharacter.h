// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSProjectile.h"
#include "TPSCharacter.generated.h"

UCLASS()
class TPSPROJECT_API ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ����ǰ���ͺ��˵����롣
	UFUNCTION()
	void MoveForward(float Value);

	// ���������ƶ������롣
	UFUNCTION()
	void MoveRight(float Value);

	// ���°���ʱ������Ծ��ǡ�
	UFUNCTION(BlueprintCallable, Category = "BPFunc_Jump")
	void StartJump();

	// �ɿ�����ʱ�����Ծ��ǡ�
	UFUNCTION(BlueprintCallable, Category = "BPFunc_Jump")
	void StopJump();

	// ������ĺ�����
	UFUNCTION(BlueprintCallable, Category = "BPFunc_Fire")
	void Fire();

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* TPSCameraComponent;

	// �������λ�õ�ǹ��ƫ�ơ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// ���ɵķ������ࡣ
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATPSProjectile> ProjectileClass;
};
