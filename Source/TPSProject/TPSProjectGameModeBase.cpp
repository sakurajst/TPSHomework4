// Copyright Epic Games, Inc. All Rights Reserved.
#include "TPSProjectGameModeBase.h"
#include "TPSProject.h"


void ATPSProjectGameModeBase::StartPlay()
{
    Super::StartPlay();

    if (GEngine)
    {
        // ��ʾ������Ϣ���롣 
        // -1"��"ֵ���׸�������˵������������»�ˢ�´���Ϣ��
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
    }
}