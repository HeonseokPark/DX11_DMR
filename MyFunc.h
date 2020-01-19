#pragma once
#define PI 3.141592654f
#define TORADIAN 0.017435f  // PI/180.0f
//float �� ����ü
typedef struct tagFRECT
{
	float left;
	float top;
	float right;
	float bottom;
} FRECT, *PFRECT;

typedef struct tagFCIRCLE
{
	float  x;
	float  y;
	float  r;
} FCIRCLE, *PFCIRCLE;

typedef struct TILE_DESC
{
	float		TileSizeX;
	float		TileSizeY;
	int			TileMaxX;
	int			TileMaxY;
	D3DXVECTOR2 ZeroStartPos;

} *PTILE_DESC;





//����
template <typename T>
static void CustomSwap(T &a, T &b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;

}
//����
template <typename T>
static void CustomShuffle(T a[], unsigned int time, unsigned int range)
{
	for (UINT i = 0; i < time; i++)
	{
		unsigned int dest = rand() % range;
		unsigned int sour = rand() % range;
		T temp = a[dest];
		a[dest] = a[sour];
		a[sour] = temp;
	}
}
//�� ������ �Ÿ� ���ϱ�
static float GetDistance(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	return sqrtf(x * x + y * y);
}
//���� ���ϱ�
static float GetRadian(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float distance = GetDistance(x1, y1, x2, y2);
	float angle = acosf(x / distance);
	if (y2 < y1)
	{
		angle = PI + (PI - angle);
		//angle += PI;
	}
	return angle;
}
static float GetDegree(float x1, float y1, float x2, float y2)
{
	float angle = GetRadian(x1, y1, x2, y2);
	angle /= TORADIAN;
	return angle;
}
//���� ������ �Լ�
static void ReverseAngle(float &angle, bool isRadian, bool AxisX, bool AxisY)
{
	float angle180;
	//���׿�����
	(isRadian) ? angle180 = PI : angle180 = 180.0f;
	if (AxisX)angle = angle180 - angle;
	if (AxisY)angle = angle180 + angle180 - angle;
}


//�׸� �����
static FRECT RectMake(const float x, const float y, const float width, const float height)
{
	FRECT rc = { x , y + height , x + width , y };
	return rc;
}
//�����߽� �׸� �����

static FRECT RectMakeCenter(const float x, const float y, const float width, const float height)
{
	float HalfWidth = width / 2.0f;
	float HalfHeight = height / 2.0f;
	FRECT rc = { x - HalfWidth ,y + HalfHeight ,x + HalfWidth ,y - HalfHeight };
	return rc;
}
//�� �����
static FCIRCLE CircleMake(const float x, const float y, const float r)
{
	FCIRCLE cc = { x,y,r };
	return cc;
}

//�簢��,�簢��(AABB)
static bool IntersectRect(FRECT rc1, FRECT rc2)
{
	if (rc1.right >= rc2.left &&
		rc1.left <= rc2.right &&
		rc1.top >= rc2.bottom &&
		rc1.bottom <= rc2.top)
	{
		return true;
	}
	return false;
}
//OBB
static bool IntersectRect(FRECT rc1, FRECT rc2,float radian1, float radian2)
{
	//�� �簢�� ���� �Ÿ� ���� ���ϱ�
	float rc1CenterX = rc1.left + (rc1.right - rc1.left) * 0.5f;
	float rc1CenterY = rc1.bottom + (rc1.top - rc1.bottom) * 0.5f;

	float rc2CenterX = rc2.left + (rc2.right - rc2.left) * 0.5f;
	float rc2CenterY = rc2.bottom + (rc2.top - rc2.bottom) * 0.5f;

	D3DXVECTOR2 distance = D3DXVECTOR2((rc1CenterX- rc2CenterX), (rc1CenterY- rc2CenterY));
	//4���� �� ���⺤��(��������), ���̰� ���Ե� ���� ���ϱ�
	D3DXVECTOR2 rc1DirA = D3DXVECTOR2(cosf(radian1), sinf(radian1));
	D3DXVECTOR2 rc1DirB = D3DXVECTOR2(cosf(radian1 - PI * 0.5f), sinf(radian1 - PI * 0.5f));

	D3DXVECTOR2 rc2DirA = D3DXVECTOR2(cosf(radian2), sinf(radian2));
	D3DXVECTOR2 rc2DirB = D3DXVECTOR2(cosf(radian2 - PI * 0.5f), sinf(radian2 - PI * 0.5f));

	D3DXVECTOR2 rc1LenA = rc1DirA * (rc1.right - rc1.left) * 0.5f;
	D3DXVECTOR2 rc1LenB = rc1DirB * (rc1.top - rc1.bottom) * 0.5f;

	D3DXVECTOR2 rc2LenA = rc2DirA * (rc2.right - rc2.left) * 0.5f;
	D3DXVECTOR2 rc2LenB = rc2DirB * (rc2.top - rc2.bottom) * 0.5f;

	//�λ簢���� 2����(2*2) 4���� �˻�

	//rc1DirA �� �˻�
	
	float lengthA = D3DXVec2Length(&rc1LenA);
	//float lengthA = GetDistance(0,0,rc1LenA.x, rc1LenA.y);
	float lengthB = fabs(D3DXVec2Dot(&rc1DirA, &rc2LenA)) + fabs(D3DXVec2Dot(&rc1DirA, &rc2LenB));

	float length = fabs(D3DXVec2Dot(&rc1DirA, &distance));
	if (length > lengthA + lengthB)
		return false;

	//rc1 dirB�� �˻�
	lengthA = D3DXVec2Length(&rc1LenB);
	lengthB = fabs(D3DXVec2Dot(&rc1DirB, &rc2LenA)) + fabs(D3DXVec2Dot(&rc1DirB, &rc2LenB));
	length = fabs(D3DXVec2Dot(&rc1DirB, &distance));
	if (length > lengthA + lengthB)
		return false;
	//rc2 dirA�� �˻�
	lengthA = D3DXVec2Length(&rc2LenA);
	lengthB = fabs(D3DXVec2Dot(&rc2DirA, &rc1LenA)) + fabs(D3DXVec2Dot(&rc2DirA, &rc1LenB));
	length = fabs(D3DXVec2Dot(&rc2DirA, &distance));
	if (length > lengthA + lengthB)
		return false;

	//rc2 dirB�� �˻�
	lengthA = D3DXVec2Length(&rc2LenB);
	lengthB = fabs(D3DXVec2Dot(&rc2DirB, &rc1LenA)) + fabs(D3DXVec2Dot(&rc2DirB, &rc1LenB));
	length = fabs(D3DXVec2Dot(&rc2DirB, &distance));
	if (length > lengthA + lengthB)
		return false;


	return true;
}


//�簢��,��
static bool PtInRect( FRECT Rect, D3DXVECTOR2 InPt)
{
	if (Rect.left <= InPt.x && InPt.x <= Rect.right &&
		Rect.top >= InPt.y && InPt.y >= Rect.bottom)
	{
		return true;
	}
	return false;
}
static bool PtInRect(FRECT Rect, D3DXVECTOR2 InPt, float radian)
{
	D3DXVECTOR2 pos{ Rect.right - ((Rect.right - Rect.left) / 2.0f), Rect.top - ((Rect.top - Rect.bottom) / 2.0f) };
	D3DXMATRIX R;
	D3DXMatrixRotationZ(&R, -radian);
	FRECT tempRc{ Rect.left - pos.x ,Rect.top - pos.y,Rect.right - pos.x,Rect.bottom - pos.y };
	D3DXVECTOR2 tempPt{ InPt.x - pos.x ,InPt.y - pos.y };
	D3DXVec2TransformCoord(&tempPt, &tempPt, &R);
	return PtInRect(tempRc, tempPt);
}
//��,��
static bool PtInCircle(FCIRCLE cc, D3DXVECTOR2 InPt)
{
	if (cc.r >= GetDistance(cc.x, cc.y, InPt.x, InPt.y))
	{
		return true;
	}
	return false;
}
//��,��
static bool IntersectCircle(FCIRCLE cc1, FCIRCLE cc2)
{
	if (cc1.r + cc2.r >= GetDistance(cc1.x, cc1.y, cc2.x, cc2.y))
	{
		return true;
	}
	return false;
}
//�簢��,��
static bool IntersectRectCircle(FRECT rc, FCIRCLE cc)
{
	//�𼭸� ���� �׸� ���浹
	FRECT temp{ rc.left ,rc.top + cc.r,rc.right,rc.bottom - cc.r };
	if (PtInRect(temp, Vec2(cc.x, cc.y))) return true;
	FRECT temp2{ rc.left - cc.r,rc.top,rc.right + cc.r,rc.bottom };
	if (PtInRect(temp2, Vec2(cc.x, cc.y))) return true;

	//�𼭸� �浹
	if (PtInCircle(cc, Vec2(rc.left, rc.top))) return true;
	if (PtInCircle(cc, Vec2(rc.left, rc.bottom))) return true;
	if (PtInCircle(cc, Vec2(rc.right, rc.top))) return true;
	if (PtInCircle(cc, Vec2(rc.right, rc.bottom))) return true;
	return false;
}

static bool IntersectRectCircle(FRECT rc, FCIRCLE cc, float radian)
{
	Vec2 pos{ rc.right - ((rc.right - rc.left) / 2.0f), rc.top - ((rc.top - rc.bottom) / 2.0f) };
	Mat R;
	D3DXMatrixRotationZ(&R, -radian);
	FRECT tempRc{ rc.left - pos.x ,rc.top - pos.y,rc.right - pos.x,rc.bottom - pos.y };
	Vec2 tempPt{ cc.x - pos.x ,cc.y - pos.y };
	D3DXVec2TransformNormal(&tempPt, &tempPt, &R);
	FCIRCLE tempcc{ tempPt.x,tempPt.y,cc.r };


	return IntersectRectCircle(tempRc, tempcc);
}

// �簢���� �� �浹 2
static bool IntersectRectCircle(FRECT& rc, FCIRCLE& cc, float radian)
{
	Vec2 Rectpos = Vec2(rc.right - (rc.right - rc.left) * 0.5f,
		rc.top - (rc.top - rc.bottom) * 0.5f);
	Vec2 Ptpos;
	Mat R;
	D3DXMatrixRotationZ(&R, -radian);

	//���� �ϱ����� ���ÿ� ��ġ��Ű��
	Ptpos.x = cc.x - Rectpos.x;
	Ptpos.y = cc.y - Rectpos.y;

	//���Ϳ� ����� �����ִ� �Լ� (w�� 0���� 1���� �� ���� �����Լ��� �ٸ���)
	D3DXVec2TransformCoord(&Ptpos, &Ptpos, &R);

	FCIRCLE tempCc;
	tempCc.x = Ptpos.x;
	tempCc.y = Ptpos.y;
	tempCc.r = cc.r;

	FRECT tempRc{ rc.left - Rectpos.x,
	rc.top - Rectpos.y ,
	rc.right - Rectpos.x ,
	rc.bottom - Rectpos.y };


	return IntersectRectCircle(tempRc, tempCc);
}

//Ÿ�� �浹

static bool PtInTile(int& tileIndexX, int& tileIndexY, TILE_DESC tile, D3DXVECTOR2 pt)
{
	//Ÿ�� ��ü ��Ʈ
	FRECT rc = { tile.ZeroStartPos.x - tile.TileSizeX * 0.5f,
	tile.ZeroStartPos.y + tile.TileSizeY * (tile.TileMaxY - 0.5f),
	tile.ZeroStartPos.x + tile.TileSizeX * (tile.TileMaxX - 0.5f),
	tile.ZeroStartPos.y - tile.TileSizeY * 0.5f,
	};

	bool Return = PtInRect(rc, pt);
	//Ÿ���� ���ÿ� ���̱�(���� �� ��ġ�� �Ű��ֱ�)
	pt.x -= rc.left;
	pt.y -= rc.bottom;

	tileIndexX = static_cast<int>(floor(pt.x / tile.TileSizeX));
	tileIndexY = static_cast<int>(floor(pt.y / tile.TileSizeY));

	return Return;
}

static bool PtInIsoTile(int& tileIndexX, int& tileIndexY, TILE_DESC tile, D3DXVECTOR2 pt)
{
	//������ �� ���ϱ�
	float radius = GetDistance(0, 0, tile.TileSizeX, tile.TileSizeY)*0.5f;
	//�� ���� ���� ���ϱ�
	float radian1 = GetRadian(0, 0, tile.TileSizeX, tile.TileSizeY);
	float radian2 = GetRadian(0, 0, tile.TileSizeX, -tile.TileSizeY);
	float radian3 = GetRadian(0, 0, -tile.TileSizeX, tile.TileSizeY);
	float radian4 = GetRadian(0, 0, -tile.TileSizeX, -tile.TileSizeY);

	for (int i = 0; i < tile.TileMaxX; i++)
	{
		for (int j = 0; j < tile.TileMaxY; j++)
		{
			FCIRCLE cc1 = CircleMake(tile.ZeroStartPos.x + (i * tile.TileSizeX * 0.5f)
				- (j * tile.TileSizeX * 0.5f)- tile.TileSizeX * 0.5f,
				tile.ZeroStartPos.y + (i * tile.TileSizeY * 0.5f)
				+ (j * tile.TileSizeY * 0.5f), radius);
			FCIRCLE cc2 = CircleMake(tile.ZeroStartPos.x + (i * tile.TileSizeX * 0.5f)
				- (j * tile.TileSizeX * 0.5f) + tile.TileSizeX * 0.5f,
				tile.ZeroStartPos.y + (i * tile.TileSizeY * 0.5f)
				+ (j * tile.TileSizeY * 0.5f), radius);
			if (PtInCircle(cc1, pt) &&
				(GetRadian(cc1.x, cc1.y, pt.x, pt.y) < radian1 || GetRadian(cc1.x, cc1.y, pt.x, pt.y) > radian2))
			{
				tileIndexX = i;
				tileIndexY = j;
				return true;
			}
			else if (PtInCircle(cc2, pt) &&
				(GetRadian(cc2.x, cc2.y, pt.x, pt.y) > radian3 && GetRadian(cc2.x, cc2.y, pt.x, pt.y)< radian4))
			{
				tileIndexX = i;
				tileIndexY = j;
				return true;
			}

		}
	}

	return false;



}


//���� �Լ�

//	0 ���� ���� int �� ��������
static int GetInt(int num)
{
	return rand() % num;
}
//	������ ���� int �� ��������
static int GetFromIntTo(int fromNum, int toNum)
{
	return rand() % (toNum - fromNum + 1) + fromNum;
}
//	0 ���� ���� float �� ��������
static float GetFloat(float num)
{
	return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * num;
}
//	������ ���� float �� ��������
static float GetFromFloatTo(float fromNum, float toNum)
{
	float rnd = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return (rnd * (toNum - fromNum) + fromNum);
}