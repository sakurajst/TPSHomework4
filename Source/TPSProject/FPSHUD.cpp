// Fill out your copyright notice in the Description page of Project Settings.
#include "FPSHUD.h"
#include "TPSProject.h"


void AFPSHUD::DrawHUD()
{
    Super::DrawHUD();

    if (CrosshairTexture)
    {
        // �ҵ��������ġ�
        FVector2D Center(Canvas->ClipX * 0.525f, Canvas->ClipY * 0.4f);

        // ����ά�Ƚ���һ��ƫ�ƣ�ʹ�������ĺͻ������Ķ��롣
        FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

        // �����ĵ����׼�ǡ�
        FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }
}