// Fill out your copyright notice in the Description page of Project Settings.
#include "TPSCharacter.h"
#include "TPSProject.h"


// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ����һ����һ�˳�����������
	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	// �������������ӵ������������
	TPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	// ��������������۾��Ϸ���Զ����
	TPSCameraComponent->SetRelativeLocation(FVector(-200.0f, 0.0f, 200.0f + BaseEyeHeight));
	// �� pawn �����������ת��
	TPSCameraComponent->bUsePawnControlRotation = true;


}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		// ��ʾ������Ϣ���롣-1"��"ֵ���׸�������˵������������»�ˢ�´���Ϣ��
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

	// ����"�ƶ�"�󶨡�
	PlayerInputComponent->BindAxis("Forward", this, &ATPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Rightward", this, &ATPSCharacter::MoveRight);

	// ����"�鿴"�󶨡�
	PlayerInputComponent->BindAxis("Yaw", this, &ATPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Pitch", this, &ATPSCharacter::AddControllerPitchInput);

	// ����"����"�󶨡�
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATPSCharacter::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATPSCharacter::Fire);
}

void ATPSCharacter::MoveForward(float Value)
{
	// ��ȷ�ĸ�������"ǰ��"������¼�����ͼ��˷����ƶ���
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ATPSCharacter::MoveRight(float Value)
{
	// ��ȷ�ĸ�������"����"������¼�����ͼ��˷����ƶ���
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
	// ���Է������塣
	if (ProjectileClass)
	{
		// ��ȡ������任��
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// �� MuzzleOffset ��������ռ�任������ռ䡣
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset + FVector(50, 50, 0));
		FRotator MuzzleRotation = CameraRotation;
		// ��׼����΢��̧��
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			//SpawnParams.Instigator = this->Instigator;
			// ��ǹ�ڴ����ɷ����
			ATPSProjectile* Projectile = World->SpawnActor<ATPSProjectile>(ProjectileClass, MuzzleLocation , MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// ���÷�����ĳ�ʼ�����
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}