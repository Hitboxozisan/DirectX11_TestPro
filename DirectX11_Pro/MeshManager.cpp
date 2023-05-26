#include "MeshManager.h"
#include "Singleton.h"

MeshManager::MeshManager()
	:device(Singleton<D11Device>::GetInstance())
{
}

MeshManager::~MeshManager()
{
}

HRESULT MeshManager::LoadMesh(LPSTR fileName)
{
	float x, y, z;
	int v1 = 0, v2 = 0, v3 = 0;
	int vn1 = 0, vn2 = 0, vn3 = 0;
	int vt1 = 0, vt2 = 0, vt3 = 0;
	DWORD dwVCount = 0;//�ǂݍ��݃J�E���^�[
	DWORD dwVTCount = 0;//�ǂݍ��݃J�E���^�[
	DWORD dwVNCount = 0;
	DWORD dwFCount = 0;//�ǂݍ��݃J�E���^�[

	char key[200] = { 0 };
	//OBJ�t�@�C�����J���ē��e��ǂݍ���
	FILE* fp = NULL;
	fopen_s(&fp, fileName, "rt");

	//���O�ɒ��_���A�|���S�����𒲂ׂ�
	while (!feof(fp))
	{
		//�L�[���[�h�ǂݍ���
		fscanf_s(fp, "%s ", key, sizeof(key));
		//���_
		if (strcmp(key, "v") == 0)
		{
			mesh.dwNumVert++;
		}
		// �@��
		if (strcmp(key, "vn") == 0)
		{
			dwVNCount++;
		}
		//�e�N�X�`���[���W
		if (strcmp(key, "vt") == 0)
		{
			dwVTCount++;
		}
		//�t�F�C�X�i�|���S���j
		if (strcmp(key, "f") == 0)
		{
			mesh.dwNumFace++;
		}
	}

	//�ꎞ�I�ȃ������m�ہi���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�j
	ObjVertex* pvVertexBuffer = new ObjVertex[mesh.dwNumFace * 3];
	XMFLOAT3* pvCoord = new XMFLOAT3[mesh.dwNumVert];
	XMFLOAT3* pvNormal = new XMFLOAT3[dwVNCount];
	XMFLOAT2* pvTexture = new XMFLOAT2[dwVTCount];
	int* piFaceBuffer = new int[mesh.dwNumFace * 3];//�R���_�|���S���Ȃ̂ŁA1�t�F�C�X=3���_(3�C���f�b�N�X)

	//�{�ǂݍ���	
	fseek(fp, SEEK_SET, 0);
	dwVCount = 0;
	dwVTCount = 0;
	dwVNCount = 0;
	dwFCount = 0;

	while (!feof(fp))
	{
		//�L�[���[�h �ǂݍ���
		ZeroMemory(key, sizeof(key));
		fscanf_s(fp, "%s ", key, sizeof(key));

		// �}�e���A���ǂݍ���
		if (strcmp(key, "mtllib") == 0)
		{
			fscanf_s(fp, "%s ", key, sizeof(key));
			//LoadMaterial("Data/Material/Geometry+Normal+UV.mtl", &material);
		}
		//���_ �ǂݍ���
		if (strcmp(key, "v") == 0)
		{
			fscanf_s(fp, "%f %f %f", &x, &y, &z);
			pvCoord[dwVCount].x = -x;//OBJ�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
			pvCoord[dwVCount].y = y;
			pvCoord[dwVCount].z = z;
			dwVCount++;
		}
		//�@�� �ǂݍ���
		if (strcmp(key, "vn") == 0)
		{
			fscanf_s(fp, "%f %f %f", &x, &y, &z);
			pvNormal[dwVNCount].x = -x;
			pvNormal[dwVNCount].y = y;//OBJ�t�@�C����Y�������t�Ȃ̂ō��킹��
			pvNormal[dwVNCount].z = z;
			dwVNCount++;
		}
		// �e�N�X�`�����W�ǂݍ���
		if (strcmp(key, "vt") == 0)
		{
			fscanf_s(fp, "%f %f", &x, &y);
			pvTexture[dwVTCount].x = x;
			pvTexture[dwVTCount].y = 1 - y;
			dwVTCount++;
		}
		//�t�F�C�X �ǂݍ��݁����_�C���f�b�N�X��
		if (strcmp(key, "f") == 0)
		{
			fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
			piFaceBuffer[dwFCount * 3] = dwFCount * 3;
			piFaceBuffer[dwFCount * 3 + 1] = dwFCount * 3 + 1;
			piFaceBuffer[dwFCount * 3 + 2] = dwFCount * 3 + 2;
			//���_�\���̂ɑ��
			pvVertexBuffer[dwFCount * 3].pos = pvCoord[v1 - 1];
			pvVertexBuffer[dwFCount * 3].norm = pvNormal[vn1 - 1];
			pvVertexBuffer[dwFCount * 3].tex = pvTexture[vt1 - 1];
			pvVertexBuffer[dwFCount * 3 + 1].pos = pvCoord[v2 - 1];
			pvVertexBuffer[dwFCount * 3 + 1].norm = pvNormal[vn2 - 1];
			pvVertexBuffer[dwFCount * 3 + 1].tex = pvTexture[vt2 - 1];
			pvVertexBuffer[dwFCount * 3 + 2].pos = pvCoord[v3 - 1];
			pvVertexBuffer[dwFCount * 3 + 2].norm = pvNormal[vn3 - 1];
			pvVertexBuffer[dwFCount * 3 + 2].tex = pvTexture[vt3 - 1];
			dwFCount++;
		}
	}

	fclose(fp);

	//�o�[�e�b�N�X�o�b�t�@�[���쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ObjVertex) * mesh.dwNumFace * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pvVertexBuffer;
	if (FAILED(device.dx11->GetDevice()->CreateBuffer(&bd, &InitData, &mesh.pVertexBuffer)))
	{
		return E_FAIL;
	}

	//�C���f�b�N�X�o�b�t�@�[���쐬
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * mesh.dwNumFace * 3;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	InitData.pSysMem = piFaceBuffer;
	if (FAILED(device.dx11->GetDevice()->CreateBuffer(&bd, &InitData, &mesh.pIndexBuffer)))
	{
		return E_FAIL;
	}

	//�ꎞ�I�ȓ��ꕨ�́A���͂�s�v
	delete[] pvCoord;
	delete[] pvTexture;
	delete[] pvNormal;
	delete[] pvVertexBuffer;
	delete[] piFaceBuffer;

	return S_OK;

    return E_NOTIMPL;
}
