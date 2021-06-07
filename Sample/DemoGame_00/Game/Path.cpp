#include "stdafx.h"
#include "Path.h"

Path::Path()
{

}

Path::~Path()
{

}

void Path::Load(const wchar_t* filePath)
{

}

const Point* Path::GetNearPoint(const Vector3& position)
{
	Point* point = &m_pointList[0];
	Vector3 diff = m_pointList[0].s_vector - position;
	//���̏ꏊ�����ԋ߂��|�C���g�T��
	for (int i = 1; i < m_pointList.size(); i++) {
		Vector3 diff2 = m_pointList[i].s_vector - position;
		if (diff.LengthSq() > diff2.LengthSq()) {
			diff = diff2;
			point = &m_pointList[i];
		}
	}
	return point;
}

const Point* Path::GetNextPoint(const int number)
{
	//�ԍ����Ō�̃|�C���g��������ŏ��̃|�C���g
	if (number == m_pointList.size()) {
		return &m_pointList[0];
	}
	else {
		return &m_pointList[number];
	}
}