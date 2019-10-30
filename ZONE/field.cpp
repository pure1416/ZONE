
#include "field.h"
#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	VALUE_MOVE		(5.0f)							// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)				// ��]��

#define	FIELD_WIDTH		(100.0f)						// �n�ʂ̕�(X����)
#define	FIELD_HEIGHT	(200.0f)						// �n�ʂ̕�(X����)
#define	FIELD_DEPTH		(100.0f)						// �n�ʂ̉��s(Z����)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

D3DXMATRIX				g_mtxWorldField;		// ���[���h�}�g���b�N�X
D3DXVECTOR3				g_posField;				// �n�ʂ̈ʒu
D3DXVECTOR3				g_rotField;				// �n�ʂ̌���(��])
D3DXVECTOR3				g_sclField;				// �n�ʂ̑傫��(�X�P�[��)

//=============================================================================
// ����������
//=============================================================================
HRESULT Field_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// ���_���̍쐬
	MakeVertexField(pDevice);

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sclField = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Field_Finalize(void)
{
	if (g_pVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Field_Update(void)
{
	if (Keyboard_IsPress(DIK_A))
	{
		if (Keyboard_IsPress(DIK_W))


		{// �����ړ�
			g_posField.x += sinf(-D3DX_PI * 0.75f) * VALUE_MOVE;
			g_posField.z -= cosf(-D3DX_PI * 0.75f) * VALUE_MOVE;
		}
		else if (Keyboard_IsPress(DIK_S))
		{// ����O�ړ�
			g_posField.x += sinf(-D3DX_PI * 0.25f) * VALUE_MOVE;
			g_posField.z -= cosf(-D3DX_PI * 0.25f) * VALUE_MOVE;
		}
		else
		{// ���ړ�
			g_posField.x += sinf(-D3DX_PI * 0.50f) * VALUE_MOVE;
			g_posField.z -= cosf(-D3DX_PI * 0.50f) * VALUE_MOVE;
		}
	}
	else if (Keyboard_IsPress(DIK_D))
	{
		if (Keyboard_IsPress(DIK_W))
		{// �E���ړ�
			g_posField.x += sinf(D3DX_PI * 0.75f) * VALUE_MOVE;
			g_posField.z -= cosf(D3DX_PI * 0.75f) * VALUE_MOVE;
		}
		else if (Keyboard_IsPress(DIK_S))
		{// �E��O�ړ�
			g_posField.x += sinf(D3DX_PI * 0.25f) * VALUE_MOVE;
			g_posField.z -= cosf(D3DX_PI * 0.25f) * VALUE_MOVE;
		}
		else
		{// �E�ړ�
			g_posField.x += sinf(D3DX_PI * 0.50f) * VALUE_MOVE;
			g_posField.z -= cosf(D3DX_PI * 0.50f) * VALUE_MOVE;
		}
	}
	else if (Keyboard_IsPress(DIK_W))
	{// ���ړ�
		g_posField.x += sinf(D3DX_PI * 1.0f) * VALUE_MOVE;
		g_posField.z -= cosf(D3DX_PI * 1.0f) * VALUE_MOVE;
	}
	else if (Keyboard_IsPress(DIK_S))
	{// ��O�ړ�
		g_posField.x += sinf(D3DX_PI * 0.0f) * VALUE_MOVE;
		g_posField.z -= cosf(D3DX_PI * 0.0f) * VALUE_MOVE;
	}

#if 1
	if (Keyboard_IsPress(DIK_Q))
	{// Y������]
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
	{// Y���E��]
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
	{// X���E��]
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
	{// X������]
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
	{// Z���E��]
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
	{// Z������]
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
	{// ���Z�b�g
		g_posField.x = 0.0f;
		g_posField.y = 0.0f;
		g_posField.z = 0.0f;

		g_rotField.x = 0.0f;
		g_rotField.y = 0.0f;
		g_rotField.z = 0.0f;
	}

	//text�������ĉ�ʏ�ɕ\��
	DebugProc_Print((char *)"*** �R�c�|���S������ ***\n");
	DebugProc_Print((char *)"�ʒu [%f : %f : %f]\n", g_posField.x, g_posField.y, g_posField.z);
	DebugProc_Print((char *)"�O�ړ� : �v\n");
	DebugProc_Print((char *)"��ړ� : �r\n");
	DebugProc_Print((char *)"���ړ� : �`\n");
	DebugProc_Print((char *)"�E�ړ� : �c\n");
	DebugProc_Print((char *)"\n");

	DebugProc_Print((char *)"���� [%f : %f : %f]\n", g_rotField.x, g_rotField.y, g_rotField.z);
	DebugProc_Print((char *)"X����] : �� / ��\n");
	DebugProc_Print((char *)"Y����] : �p / �d\n");
	DebugProc_Print((char *)"Z����] : �� / ��\n");
	DebugProc_Print((char *)"\n");

	DebugProc_Print((char *)"�ʒu�E�������Z�b�g : ENTER\n");

}

//=============================================================================
// �`�揈��
//=============================================================================
void Field_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldField);

	//�X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_sclField.x, g_sclField.y, g_sclField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxScl);

	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotField.x, g_rotField.y, g_rotField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxRot);

	//�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_posField.x, g_posField.y, g_posField.z);
	D3DXMatrixMultiply(&g_mtxWorldField, &g_mtxWorldField, &mtxTranslate);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldField);

	//
	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	//
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_FIELD01));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, NUM_POLYGON);
}


//=============================================================================
// ���_�̍쐬
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
		//���_�o�b�t�@�̔��𖄂߂�
		VERTEX_3D *pVtx;

		//VRAM��̏��������Ă��邩��A���_���������悤�ɂȂ�
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

		//�e�N�X�`���̈ʒu��ݒ�
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
		//������VRAM�֋A��
		g_pVtxBuffField->Unlock();
	}
	return S_OK;
}
