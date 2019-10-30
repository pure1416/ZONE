
#include "field.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	VALUE_MOVE		(5.0f)							// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)				// 回転量

#define	FIELD_WIDTH		(100.0f)						// 地面の幅(X方向)
#define	FIELD_HEIGHT	(200.0f)						// 地面の幅(X方向)
#define	FIELD_DEPTH		(100.0f)						// 地面の奥行(Z方向)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	// 頂点バッファへのポインタ

D3DXMATRIX				g_mtxWorldField;		// ワールドマトリックス
D3DXVECTOR3				g_posField;				// 地面の位置
D3DXVECTOR3				g_rotField;				// 地面の向き(回転)
D3DXVECTOR3				g_sclField;				// 地面の大きさ(スケール)

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Field_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// 頂点情報の作成
	MakeVertexField(pDevice);

	// 位置・回転・スケールの初期設定
	g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sclField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Field_Finalize(void)
{
	if (g_pVtxBuffField != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Field_Update(void)
{
	if (Keyboard_IsPress(DIK_A))
	{
		if (Keyboard_IsPress(DIK_W))


		{// 左奥移動
			g_posField.x += sinf(-D3DX_PI * 0.75f) * VALUE_MOVE;
			g_posField.z -= cosf(-D3DX_PI * 0.75f) * VALUE_MOVE;
		}
		else if (Keyboard_IsPress(DIK_S))
		{// 左手前移動
			g_posField.x += sinf(-D3DX_PI * 0.25f) * VALUE_MOVE;
			g_posField.z -= cosf(-D3DX_PI * 0.25f) * VALUE_MOVE;
		}
		else
		{// 左移動
			g_posField.x += sinf(-D3DX_PI * 0.50f) * VALUE_MOVE;
			g_posField.z -= cosf(-D3DX_PI * 0.50f) * VALUE_MOVE;
		}
	}
	else if (Keyboard_IsPress(DIK_D))
	{
		if (Keyboard_IsPress(DIK_W))
		{// 右奥移動
			g_posField.x += sinf(D3DX_PI * 0.75f) * VALUE_MOVE;
			g_posField.z -= cosf(D3DX_PI * 0.75f) * VALUE_MOVE;
		}
		else if (Keyboard_IsPress(DIK_S))
		{// 右手前移動
			g_posField.x += sinf(D3DX_PI * 0.25f) * VALUE_MOVE;
			g_posField.z -= cosf(D3DX_PI * 0.25f) * VALUE_MOVE;
		}
		else
		{// 右移動
			g_posField.x += sinf(D3DX_PI * 0.50f) * VALUE_MOVE;
			g_posField.z -= cosf(D3DX_PI * 0.50f) * VALUE_MOVE;
		}
	}
	else if (Keyboard_IsPress(DIK_W))
	{// 奥移動
		g_posField.x += sinf(D3DX_PI * 1.0f) * VALUE_MOVE;
		g_posField.z -= cosf(D3DX_PI * 1.0f) * VALUE_MOVE;
	}
	else if (Keyboard_IsPress(DIK_S))
	{// 手前移動
		g_posField.x += sinf(D3DX_PI * 0.0f) * VALUE_MOVE;
		g_posField.z -= cosf(D3DX_PI * 0.0f) * VALUE_MOVE;
	}

#if 1
	if (Keyboard_IsPress(DIK_Q))
	{// Y軸左回転
		g_rotField.y -= VALUE_ROTATE;
		if (g_rotField.y > D3DX_PI)
		{
			g_rotField.y -= D3DX_PI * 2.0f;
		}
		if (g_rotField.y < -D3DX_PI)
		{
			g_rotField.y += D3DX_PI * 2.0f;
		}
	}
	if (Keyboard_IsPress(DIK_E))
	{// Y軸右回転
		g_rotField.y += VALUE_ROTATE;
		if (g_rotField.y > D3DX_PI)
		{
			g_rotField.y -= D3DX_PI * 2.0f;
		}
		if (g_rotField.y < -D3DX_PI)
		{
			g_rotField.y += D3DX_PI * 2.0f;
		}
	}
#endif

#if 1
	if (Keyboard_IsPress(DIK_UP))
	{// X軸右回転
		g_rotField.x += VALUE_ROTATE;
		if (g_rotField.x > D3DX_PI)
		{
			g_rotField.x -= D3DX_PI * 2.0f;
		}
		if (g_rotField.x < -D3DX_PI)
		{
			g_rotField.x += D3DX_PI * 2.0f;
		}
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{// X軸左回転
		g_rotField.x -= VALUE_ROTATE;
		if (g_rotField.x > D3DX_PI)
		{
			g_rotField.x -= D3DX_PI * 2.0f;
		}
		if (g_rotField.x < -D3DX_PI)
		{
			g_rotField.x += D3DX_PI * 2.0f;
		}
	}
#endif

#if 1
	if (Keyboard_IsPress(DIK_LEFT))
	{// Z軸右回転
		g_rotField.z += VALUE_ROTATE;
		if (g_rotField.z > D3DX_PI)
		{
			g_rotField.z -= D3DX_PI * 2.0f;
		}
		if (g_rotField.z < -D3DX_PI)
		{
			g_rotField.z += D3DX_PI * 2.0f;
		}
	}
	if (Keyboard_IsPress(DIK_RIGHT))
	{// Z軸左回転
		g_rotField.z -= VALUE_ROTATE;
		if (g_rotField.z > D3DX_PI)
		{
			g_rotField.z -= D3DX_PI * 2.0f;
		}
		if (g_rotField.z < -D3DX_PI)
		{
			g_rotField.z += D3DX_PI * 2.0f;
		}
	}
#endif

	if (Keyboard_IsPress(DIK_RETURN))
	{// リセット
		g_posField.x = 0.0f;
		g_posField.y = 0.0f;
		g_posField.z = 0.0f;

		g_rotField.x = 0.0f;
		g_rotField.y = 0.0f;
		g_rotField.z = 0.0f;
	}

	//textを書いて画面上に表示
	DebugProc_Print((char *)"*** ３Ｄポリゴン操作 ***\n");
	DebugProc_Print((char *)"位置 [%f : %f : %f]\n", g_posField.x, g_posField.y, g_posField.z);
	DebugProc_Print((char *)"前移動 : Ｗ\n");
	DebugProc_Print((char *)"後移動 : Ｓ\n");
	DebugProc_Print((char *)"左移動 : Ａ\n");
	DebugProc_Print((char *)"右移動 : Ｄ\n");
	DebugProc_Print((char *)"\n");

	DebugProc_Print((char *)"向き [%f : %f : %f]\n", g_rotField.x, g_rotField.y, g_rotField.z);
	DebugProc_Print((char *)"X軸回転 : ↑ / ↓\n");
	DebugProc_Print((char *)"Y軸回転 : Ｑ / Ｅ\n");
	DebugProc_Print((char *)"Z軸回転 : ← / →\n");
	DebugProc_Print((char *)"\n");

	DebugProc_Print((char *)"位置・向きリセット : ENTER\n");

}

//=============================================================================
// 描画処理
//=============================================================================
void Field_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldField);

	//スケールを反映
	D3DXMatrixScaling(&mtxScl, g_sclField.x, g_sclField.y, g_sclField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxScl);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotField.x, g_rotField.y, g_rotField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

	//移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_posField.x, g_posField.y, g_posField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTranslate);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

	//
	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	//
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_FIELD01));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, NUM_POLYGON);
}


//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL)))
	{
		return E_FAIL;
	}
	{
		//頂点バッファの髪を埋める
		VERTEX_3D *pVtx;

		//VRAM上の情報を持ってくるから、頂点をいじれるようになる
		g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].pos = D3DXVECTOR3(-FIELD_WIDTH, 0, FIELD_DEPTH);
		pVtx[1].pos = D3DXVECTOR3(FIELD_WIDTH, 0, FIELD_DEPTH);
		pVtx[2].pos = D3DXVECTOR3(-FIELD_WIDTH, 0, -FIELD_DEPTH);
		pVtx[3].pos = D3DXVECTOR3 (-FIELD_WIDTH, 0, -FIELD_DEPTH);
		pVtx[4].pos =  D3DXVECTOR3(FIELD_WIDTH, 0, FIELD_DEPTH);
		pVtx[5].pos = D3DXVECTOR3(FIELD_WIDTH, 0, -FIELD_DEPTH);

		pVtx[6].pos = D3DXVECTOR3(-FIELD_WIDTH, 0, FIELD_DEPTH);
		pVtx[7].pos = D3DXVECTOR3(-FIELD_WIDTH, 0, -FIELD_DEPTH);
		pVtx[8].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_HEIGHT, -FIELD_DEPTH);
		pVtx[9].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_HEIGHT, -FIELD_DEPTH);
		pVtx[10].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_HEIGHT, FIELD_DEPTH);
		pVtx[11].pos = D3DXVECTOR3(-FIELD_WIDTH, 0, FIELD_DEPTH);

		pVtx[12].pos = D3DXVECTOR3(FIELD_WIDTH, 0, -FIELD_DEPTH);
		pVtx[13].pos = D3DXVECTOR3(FIELD_WIDTH, 0, FIELD_DEPTH);
		pVtx[14].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_HEIGHT, FIELD_DEPTH);
		pVtx[15].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_HEIGHT, FIELD_DEPTH);
		pVtx[16].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_HEIGHT, -FIELD_DEPTH);
		pVtx[17].pos = D3DXVECTOR3(FIELD_WIDTH, 0, -FIELD_DEPTH);

		pVtx[18].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_HEIGHT, FIELD_DEPTH);
		pVtx[19].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_HEIGHT, FIELD_DEPTH);
		pVtx[20].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_HEIGHT, -FIELD_DEPTH);
		pVtx[21].pos = D3DXVECTOR3(-FIELD_WIDTH, FIELD_HEIGHT, -FIELD_DEPTH);
		pVtx[22].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_HEIGHT, FIELD_DEPTH);
		pVtx[23].pos = D3DXVECTOR3(FIELD_WIDTH, FIELD_HEIGHT, -FIELD_DEPTH);


		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[6].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		pVtx[8].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		pVtx[9].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		pVtx[10].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		pVtx[11].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

		pVtx[12].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[13].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[14].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[15].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[16].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[17].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

		pVtx[18].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[19].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[20].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[21].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[22].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		pVtx[23].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);


		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[20].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[21].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[22].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[23].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャの位置を設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[18].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[19].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[20].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[21].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[22].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[23].tex = D3DXVECTOR2(1.0f, 0.0f);
		//ここでVRAMへ帰す
		g_pVtxBuffField->Unlock();
	}
	return S_OK;
}

