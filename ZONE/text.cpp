//#include "3d.h"
//
//#include <d3d9.h>
//#include <d3dx9.h>
//#include <dinput.h>
//
//#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}//���S�ɉ������
//
//LPDIRECT3D9             g_pD3D = NULL;//Direct3D9
//LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;//�����_�����O�f�o�C�X
//LPD3DXFONT    g_pFont = NULL;//�t�H���g
//LPD3DXMESH    pMesh = NULL;//���b�V��
//D3DMATERIAL9*   pMaterials = NULL;//�}�e���A��
//LPDIRECT3DTEXTURE9*  pTextures = NULL;//�e�N�X�`��
//
//DWORD dwNumMaterials = 0;
//
////�e�L�X�g�`��
//void TextDraw(LPD3DXFONT pFont, char* text, int X, int Y)
//{
//	RECT rect = { X,Y,0,0 };//�`��ʒu
//	//�X�v���C�g�|�C���^(�����Ă��ǂ�),�`�敶��,������(-1�őS��),�`��͈�,�t�H�[�}�b�g,�F
//	pFont->DrawText(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 0, 0));
//}
//
//
////Direct3D������
//HRESULT InitD3D(HWND hWnd)
//{
//	//Direct3D�𐶐�����
//	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION))) { return E_FAIL; }
//
//	//�f�o�C�X�����p�̃p�����[�^�[
//	D3DPRESENT_PARAMETERS d3dpp;//�p�����[�^�[�\����
//	ZeroMemory(&d3dpp, sizeof(d3dpp));//�[���ŏ�����
//	d3dpp.Windowed = TRUE;//�E�C���h�E���[�h�ŋN��
//	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//�o�b�N�o�b�t�@�̃X���b�v�G�t�F�N�g Direct3D�ɃX���b�v�G�t�F�N�g���܂�����
//	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;//�o�b�N�o�b�t�@�̃t�H�[�}�b�g���\������Ă��郂�j�^�̐ݒ�Ɠ���
//	d3dpp.BackBufferCount = 1;//�o�b�N�o�b�t�@�̐�
//	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;//�}���`�T���v�����O�͍s��Ȃ�
//	d3dpp.MultiSampleQuality = 0;//�}���`�T���v�����O�͍s��Ȃ��̂�0
//	d3dpp.EnableAutoDepthStencil = TRUE;//Direct3D�ɐ[�x�o�b�t�@�̊Ǘ����܂�����
//	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�[�x�o�b�t�@�̃t�H�[�}�b�g�i�ʏ�͂��̒l�Ŗ��Ȃ��j
//	d3dpp.hDeviceWindow = hWnd;//�J�o�[�E�B���h�E���A�v���P�[�V�����̃E�B���h�E
//	d3dpp.Flags = 0;//�t���O�͎g��Ȃ�
//	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//���̃��t���b�V�����[�g�����̂܂܎g��
//	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//���j�^�̐�����A��҂�
//
//	//Direct3D�f�o�C�X�̐��� HAL(�n�[�h�E�F�A�A�N�Z�����[�V����)
//	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice))) {
//		//HAL���ʖڂȂ�HEL(�\�t�g�E�F�A�G�~�����[�V����)
//		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice))) {
//			//�ʖڂȂ�I��
//			return(E_FAIL);
//		}
//	}
//
//	//�t�H���g�̐��� MS�S�V�b�N
//   //�f�o�C�X,��������,������,�t�H���g�X�^�C��,�~�b�v�}�b�v�̃��x��,�Α̂ɂ��邩�ǂ���,�����Z�b�g,�o�͐��x,�o�͕i��,�t�H���g�s�b�`�ƃt�@�~��,�t�H���g��,�t�H���g�|�C���^
//	HRESULT hr = D3DXCreateFont(g_pd3dDevice, 20, 0, FW_HEAVY, 1, false, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
//		ANTIALIASED_QUALITY, FF_DONTCARE, "�l�r �S�V�b�N", &g_pFont);
//	if FAILED(hr) { return(E_FAIL); }
//
//
//	// X�t�@�C�����烁�b�V�������[�h���� 
//	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
//
//	//�t�@�C���ǂݍ���
//	if (FAILED(D3DXLoadMeshFromX("box.x", D3DXMESH_SYSTEMMEM,
//		g_pd3dDevice, NULL, &pD3DXMtrlBuffer, NULL,
//		&dwNumMaterials, &pMesh)))
//	{
//		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
//		return E_FAIL;
//	}
//	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
//	pMaterials = new D3DMATERIAL9[dwNumMaterials];
//	pTextures = new LPDIRECT3DTEXTURE9[dwNumMaterials];
//
//	for (DWORD i = 0; i < dwNumMaterials; i++)
//	{
//		pMaterials[i] = d3dxMaterials[i].MatD3D;
//		pMaterials[i].Ambient = pMaterials[i].Diffuse;
//		pTextures[i] = NULL;
//		if (d3dxMaterials[i].pTextureFilename != NULL &&
//			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
//		{
//			if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice,
//				d3dxMaterials[i].pTextureFilename,
//				&pTextures[i])))
//			{
//				MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
//			}
//		}
//	}
//	pD3DXMtrlBuffer->Release();
//	// Z�o�b�t�@�[������L���ɂ���
//	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
//	// ���C�g��L���ɂ���
//	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	// �A���r�G���g���C�g�i�����j��ݒ肷��
//	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00111111);
//	// �X�y�L�����i���ʔ��ˁj��L���ɂ���
//	g_pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
//	return S_OK;
//}
//
////�I�����������
//void Boxer_Finalize()
//{
//	SAFE_RELEASE(pMesh);
//	SAFE_RELEASE(g_pFont);
//	SAFE_RELEASE(g_pd3dDevice);
//	SAFE_RELEASE(g_pD3D);
//}
//
//void Boxer_Update() {
//
//}
////�����_�����O
//void Boxer_Draw()
//{
//	//�f�o�C�X�������Ȃ�I��
//	if (NULL == g_pd3dDevice) { return; }
//
//	//���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
//	D3DXMATRIXA16 matWorld, matRotation;
//	D3DXMatrixRotationY(&matWorld, 0.0f);
//	D3DXMatrixRotationX(&matRotation, 0.5f);
//	D3DXMatrixMultiply(&matWorld, &matWorld, &matRotation);
//	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
//	// �r���[�g�����X�t�H�[���i���_���W�ϊ��j
//
//	D3DXVECTOR3 vecEyePt(0.0f, 10.0f, -10.5f); //�J�����i���_�j�ʒu
//	D3DXVECTOR3 vecLookatPt(0.0f, 0.0f, 0.0f);//�����ʒu
//	D3DXVECTOR3 vecUpVec(0.0f, 1.0f, 0.0f);//����ʒu
//	D3DXMATRIXA16 matView;
//	D3DXMatrixLookAtLH(&matView, &vecEyePt, &vecLookatPt, &vecUpVec);
//	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);
//
//	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
//	D3DXMATRIXA16 matProj;
//	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45.0f), 1.0f, 10.0f, 1000.0f);
//	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
//	// ���C�g�����Ă� ���F�ŋ��ʔ��˂���ɐݒ�
//	D3DXVECTOR3 vecDirection(1, -1, -1);
//	D3DLIGHT9 light;
//	ZeroMemory(&light, sizeof(D3DLIGHT9));
//	light.Type = D3DLIGHT_DIRECTIONAL;
//	light.Diffuse.r = 1.0f;
//	light.Diffuse.g = 1.0f;
//	light.Diffuse.b = 1.0f;
//	light.Specular.r = 1.0f;
//	light.Specular.g = 1.0f;
//	light.Specular.b = 1.0f;
//	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);
//	light.Range = 200.0f;
//	g_pd3dDevice->SetLight(0, &light);
//	g_pd3dDevice->LightEnable(0, TRUE);
//
//
//	//�o�b�N�o�b�t�@�̃N���A
//	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
//		D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);
//	//�V�[���̊J�n
//	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
//	{
//		//�����ɏ������e������
//
//		for (DWORD i = 0; i < dwNumMaterials; i++)
//		{
//			g_pd3dDevice->SetMaterial(&pMaterials[i]);
//			g_pd3dDevice->SetTexture(0, pTextures[i]);
//			pMesh->DrawSubset(i);
//		}
//		TextDraw(g_pFont, (char *) "X�t�@�C���̓ǂݍ��݂ƕ\��", 0, 0);
//
//		//�V�[���̏I��
//		g_pd3dDevice->EndScene();
//	}
//
//	//�o�b�N�o�b�t�@��\��ʂɔ��f������
//	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
//}