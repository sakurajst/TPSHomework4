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

	// 处理前进和后退的输入。
	UFUNCTION()
	void MoveForward(float Value);

	// 处理左右移动的输入。
	UFUNCTION()
	void MoveRight(float Value);

	// 按下按键时设置跳跃标记。
	UFUNCTION(BlueprintCallable, Category = "BPFunc_Jump")
	void StartJump();

	// 松开按键时清除跳跃标记。
	UFUNCTION(BlueprintCallable, Category = "BPFunc_Jump")
	void StopJump();

	// 处理开火的函数。
	UFUNCTION(BlueprintCallable, Category = "BPFunc_Fire")
	void Fire();

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* TPSCameraComponent;

	// 从摄像机位置的枪口偏移。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// 生成的发射物类。
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ATPSProjectile> ProjectileClass;
};
