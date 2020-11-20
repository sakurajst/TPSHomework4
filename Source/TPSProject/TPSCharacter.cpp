// Fill out your copyright notice in the Description page of Project Settings.
#include "TPSCharacter.h"
#include "TPSProject.h"


// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建一个第一人称摄像机组件。
	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	// 将摄像机组件附加到胶囊体组件。
	TPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	// 将摄像机放置在眼睛上方不远处。
	TPSCameraComponent->SetRelativeLocation(FVector(-200.0f, 0.0f, 200.0f + BaseEyeHeight));
	// 用 pawn 控制摄像机旋转。
	TPSCameraComponent->bUsePawnControlRotation = true;


}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		// 显示调试信息五秒。-1"键"值（首个参数）说明我们无需更新或刷新此消息。
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using TPSCharacter."));
	}

}

// Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 设置"移动"绑定。
	PlayerInputComponent->BindAxis("Forward", this, &ATPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Rightward", this, &ATPSCharacter::MoveRight);

	// 设置"查看"绑定。
	PlayerInputComponent->BindAxis("Yaw", this, &ATPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Pitch", this, &ATPSCharacter::AddControllerPitchInput);

	// 设置"动作"绑定。
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATPSCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATPSCharacter::Fire);
}

void ATPSCharacter::MoveForward(float Value)
{
	// 明确哪个方向是"前进"，并记录玩家试图向此方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ATPSCharacter::MoveRight(float Value)
{
	// 明确哪个方向是"向右"，并记录玩家试图向此方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ATPSCharacter::StartJump()
{
	bPressedJump = true;
}

void ATPSCharacter::StopJump()
{
	bPressedJump = false;
}

void ATPSCharacter::Fire()
{
	// 尝试发射物体。
	if (ProjectileClass)
	{
		// 获取摄像机变换。
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// 将 MuzzleOffset 从摄像机空间变换到世界空间。
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset + FVector(50, 50, 0));
		FRotator MuzzleRotation = CameraRotation;
		// 将准星稍微上抬。
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			//SpawnParams.Instigator = this->Instigator;
			// 在枪口处生成发射物。
			ATPSProjectile* Projectile = World->SpawnActor<ATPSProjectile>(ProjectileClass, MuzzleLocation , MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// 设置发射物的初始轨道。
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}